#include <assimp/Exporter.hpp>
#include <assimp/Importer.hpp>
#include <assimp/LogAux.h>
#include <assimp/Logger.hpp>
#include <assimp/anim.h>
#include <assimp/cimport.h>
#include <assimp/mesh.h>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <cassert>
#include <tth/core/log.hpp>
#include <tth/meta/animation/animation.hpp>
#include <tth/meta/crc64/crc64.hpp>
#include <tth/meta/skeleton/skeleton.hpp>

errno_t ConvertSkeleton(const Skeleton &skeleton, aiNode &sceneNode)
{
    for (auto const &bone : skeleton.mEntries)
    {
        char name[32];
        snprintf(name, sizeof(name), "%016lX", bone.mJointName.mCrc64);
        aiNode *node = new aiNode(name);
        node->mTransformation =
            aiMatrix4x4(aiVector3D(1.0f), aiQuaternion(bone.mLocalQuat.w, bone.mLocalQuat.x, bone.mLocalQuat.y, bone.mLocalQuat.z), aiVector3D(bone.mLocalPos.x, bone.mLocalPos.y, bone.mLocalPos.z));

        if (bone.mParentIndex >= 0)
        {
            snprintf(name, sizeof(name), "%016lX", bone.mParentName.mCrc64);
            node->mParent = sceneNode.FindNode(name);
            node->mParent->addChildren(1, &node);
        }
        else // Root node
        {
            node->mParent = &sceneNode;
            sceneNode.addChildren(1, &node);
        }
    }

    return 0;
}

errno_t ConvertAnimation(const Animation &animation, aiAnimation &assimpAnimation)
{
    assimpAnimation.mName = aiString("HydraAnimation");
    assimpAnimation.mDuration = animation.mLength;
    assimpAnimation.mTicksPerSecond = 1.0;

    size_t maxFrameCount = 0; // I don't know if this is reliable
    for (int32_t i = 0; i < animation.mInterfaceCount; ++i)
    {
        KeyframedValue<Transform> *keyframedValue = animation.mValues[i].GetTypePtr<KeyframedValue<Transform>>();
        if (keyframedValue != nullptr && animation.mInterfaceSymbols[i].mCrc64 == CRC64_CaseInsensitive(0, "root"))
        {
            maxFrameCount = keyframedValue->mSamples.size();
        }
    }
    if (maxFrameCount == 0)
    {
        return -TTH_TYPE_NOT_FOUND;
    }

    const CompressedSkeletonPoseKeys2 *cspk = nullptr;
    for (int32_t i = 0; i < animation.mInterfaceCount && cspk == nullptr; ++i)
    {
        cspk = animation.mValues[i].GetTypePtr<CompressedSkeletonPoseKeys2>();
    }
    if (cspk == nullptr)
    {
        return -TTH_TYPE_NOT_FOUND;
    }

    CompressedSkeletonPoseKeys2::Header header = *(CompressedSkeletonPoseKeys2::Header *)(cspk->mpData); // TODO: undefined behaviour? Should probably fix
    const uint8_t *cspkBuf = cspk->mpData + sizeof(header) + sizeof(int64_t);

    header.mRangeVector.x *= 9.536752e-07f;
    header.mRangeVector.y *= 2.384186e-07f;
    header.mRangeVector.z *= 2.384186e-07f;

    header.mRangeDeltaV.x *= 0.0009775171f;
    header.mRangeDeltaV.y *= 0.0004885198f;
    header.mRangeDeltaV.z *= 0.0004885198f;

    header.mRangeDeltaQ.x *= 0.0009775171f;
    header.mRangeDeltaQ.y *= 0.0004885198f;
    header.mRangeDeltaQ.z *= 0.0004885198f;

    size_t stagedDelQ = 4;
    size_t stagedAbsQ = 4;
    size_t stagedDelV = 4;
    size_t stagedAbsV = 4;
    aiQuaternion delQ[4];
    aiQuaternion absQ[4];
    aiVector3D delV[4];
    aiVector3D absV[4];

    assimpAnimation.mNumChannels = header.mBoneCount;
    assimpAnimation.mChannels = new aiNodeAnim *[assimpAnimation.mNumChannels];
    for (unsigned int i = 0; i < assimpAnimation.mNumChannels; ++i)
    {
        assimpAnimation.mChannels[i] = new aiNodeAnim();
        assimpAnimation.mChannels[i]->mPositionKeys = new aiVectorKey[maxFrameCount];
        assimpAnimation.mChannels[i]->mRotationKeys = new aiQuatKey[maxFrameCount];

        assimpAnimation.mChannels[i]->mNodeName.length =
            snprintf(assimpAnimation.mChannels[i]->mNodeName.data, sizeof(assimpAnimation.mChannels[i]->mNodeName.data), "%016lX", ((uint64_t *)(cspkBuf + header.mSampleDataSize))[i]);
    }

    for (const uint32_t *headerData = (uint32_t *)(cspkBuf + header.mSampleDataSize + header.mBoneCount * sizeof(uint64_t)); headerData < (uint32_t *)(cspk->mpData + cspk->mDataSize); ++headerData)
    {
        if ((*headerData & 0x40000000) == 0) // Vector
        {
            assimpAnimation.mChannels[(*headerData >> 0x10) & 0xfff]->mPositionKeys[++assimpAnimation.mChannels[(*headerData >> 0x10) & 0xfff]->mNumPositionKeys - 1].mTime =
                (float)(*headerData & 0xffff) * 1.525902e-05 * header.mRangeTime;
            if ((int32_t)*headerData < 0)
            {
                if (stagedDelV > 3)
                {
                    for (uint32_t i = 0; i < 4; ++i)
                    {
                        delV[i].x = (float)(((uint32_t *)cspkBuf)[i] & 0x3ff) * header.mRangeDeltaV.x + header.mMinDeltaV.x;
                        delV[i].y = (float)(((uint32_t *)cspkBuf)[i] >> 10 & 0x7ff) * header.mRangeDeltaV.y + header.mMinDeltaV.y;
                        delV[i].z = (float)(((uint32_t *)cspkBuf)[i] >> 21) * header.mRangeDeltaV.z + header.mMinDeltaV.z;
                    }
                    cspkBuf += 4 * sizeof(uint32_t);
                    stagedDelV = 0;
                }
                if (assimpAnimation.mChannels[(*headerData >> 0x10) & 0xfff]->mNumPositionKeys > 1)
                {
                    aiVector3Add(delV + stagedDelV,
                                 &assimpAnimation.mChannels[(*headerData >> 0x10) & 0xfff]->mPositionKeys[assimpAnimation.mChannels[(*headerData >> 0x10) & 0xfff]->mNumPositionKeys - 2].mValue);
                }
                assimpAnimation.mChannels[(*headerData >> 0x10) & 0xfff]->mPositionKeys[assimpAnimation.mChannels[(*headerData >> 0x10) & 0xfff]->mNumPositionKeys - 1].mValue = delV[stagedDelV];
                ++stagedDelV;
            }
            else
            {
                if (stagedAbsV > 3)
                {
                    for (uint32_t i = 0; i < 4; ++i)
                    {
                        absV[i].x = (float)(((((uint32_t *)cspkBuf)[4 + i] & 0x3ff) << 10) | (((uint32_t *)cspkBuf)[i] & 0x3ff)) * header.mRangeVector.x + header.mMinVector.x;
                        absV[i].y = (float)(((((uint32_t *)cspkBuf)[4 + i] >> 10 & 0x7ff) << 11) | (((uint32_t *)cspkBuf)[i] >> 10 & 0x7ff)) * header.mRangeVector.y + header.mMinVector.y;
                        absV[i].z = (float)(((((uint32_t *)cspkBuf)[4 + i] >> 21) << 11) | (((uint32_t *)cspkBuf)[i] >> 21)) * header.mRangeVector.z + header.mMinVector.z;
                    }
                    cspkBuf += 8 * sizeof(uint32_t);
                    stagedAbsV = 0;
                }
                assimpAnimation.mChannels[(*headerData >> 0x10) & 0xfff]->mPositionKeys[assimpAnimation.mChannels[(*headerData >> 0x10) & 0xfff]->mNumPositionKeys - 1].mValue = absV[stagedAbsV];
                ++stagedAbsV;
            }
        }
        else // Quaternion
        {
            assimpAnimation.mChannels[(*headerData >> 0x10) & 0xfff]->mRotationKeys[++assimpAnimation.mChannels[(*headerData >> 0x10) & 0xfff]->mNumRotationKeys - 1].mTime =
                (float)(*headerData & 0xffff) * 1.525902e-05 * header.mRangeTime;
            if ((int32_t)*headerData < 0)
            {
                if (stagedDelQ > 3)
                {
                    for (uint32_t i = 0; i < 4; ++i)
                    {
                        delQ[i].x = (float)(((uint32_t *)cspkBuf)[i] & 0x3ff) * header.mRangeDeltaQ.x + header.mMinDeltaQ.x;
                        delQ[i].y = (float)(((uint32_t *)cspkBuf)[i] >> 10 & 0x7ff) * header.mRangeDeltaQ.y + header.mMinDeltaQ.y;
                        delQ[i].z = (float)(((uint32_t *)cspkBuf)[i] >> 21) * header.mRangeDeltaQ.z + header.mMinDeltaQ.z;
                        delQ[i].w = ((1.0 - delQ[i].x * delQ[i].x) - delQ[i].y * delQ[i].y) - delQ[i].z * delQ[i].z;

                        if (delQ[i].w > 0.0f)
                        {
                            delQ[i].w = sqrtf(delQ[i].w);
                        }
                        else
                        {
                            delQ[i].w = 0.0f;
                        }
                    }
                    cspkBuf += 4 * sizeof(uint32_t);
                    stagedDelQ = 0;
                }
                if (assimpAnimation.mChannels[(*headerData >> 0x10) & 0xfff]->mNumRotationKeys > 1)
                {
                    aiQuaternionMultiply(
                        delQ + stagedDelQ,
                        &assimpAnimation.mChannels[(*headerData >> 0x10) & 0xfff]->mRotationKeys[assimpAnimation.mChannels[(*headerData >> 0x10) & 0xfff]->mNumRotationKeys - 2].mValue);
                }
                assimpAnimation.mChannels[(*headerData >> 0x10) & 0xfff]->mRotationKeys[assimpAnimation.mChannels[(*headerData >> 0x10) & 0xfff]->mNumRotationKeys - 1].mValue = delQ[stagedDelQ];
                ++stagedDelQ;
            }
            else
            {
                if (stagedAbsQ > 3)
                {
                    for (uint32_t i = 0; i < 4; ++i)
                    {
                        absQ[i].x = (float)(((((uint32_t *)cspkBuf)[4 + i] & 0x3ff) << 10) | (((uint32_t *)cspkBuf)[i] & 0x3ff)) * 1.3487e-06 - 0.7071068;
                        absQ[i].y = (float)(((((uint32_t *)cspkBuf)[4 + i] >> 10 & 0x7ff) << 11) | (((uint32_t *)cspkBuf)[i] >> 10 & 0x7ff)) * 3.371749e-07 - 0.7071068;
                        absQ[i].z = (float)(((((uint32_t *)cspkBuf)[4 + i] >> 21) << 11) | (((uint32_t *)cspkBuf)[i] >> 21)) * 3.371749e-07 - 0.7071068;
                        absQ[i].w = ((1.0 - absQ[i].x * absQ[i].x) - absQ[i].y * absQ[i].y) - absQ[i].z * absQ[i].z;
                        if (absQ[i].w > 0.0f)
                        {
                            absQ[i].w = sqrtf(absQ[i].w);
                        }
                        else
                        {
                            absQ[i].w = 0.0f;
                        }
                    }
                    cspkBuf += 8 * sizeof(uint32_t);
                    stagedAbsQ = 0;
                }
                uint32_t axisOrder = *headerData >> 0x1c & 3;
                assimpAnimation.mChannels[(*headerData >> 0x10) & 0xfff]->mRotationKeys[assimpAnimation.mChannels[(*headerData >> 0x10) & 0xfff]->mNumRotationKeys - 1].mValue.x =
                    *(((float *)absQ + (axisOrder ^ 1)) + 4 * stagedAbsQ);
                assimpAnimation.mChannels[(*headerData >> 0x10) & 0xfff]->mRotationKeys[assimpAnimation.mChannels[(*headerData >> 0x10) & 0xfff]->mNumRotationKeys - 1].mValue.y =
                    *(((float *)absQ + (axisOrder ^ 2)) + 4 * stagedAbsQ);
                assimpAnimation.mChannels[(*headerData >> 0x10) & 0xfff]->mRotationKeys[assimpAnimation.mChannels[(*headerData >> 0x10) & 0xfff]->mNumRotationKeys - 1].mValue.z =
                    *(((float *)absQ + (axisOrder ^ 3)) + 4 * stagedAbsQ);
                assimpAnimation.mChannels[(*headerData >> 0x10) & 0xfff]->mRotationKeys[assimpAnimation.mChannels[(*headerData >> 0x10) & 0xfff]->mNumRotationKeys - 1].mValue.w =
                    *(((float *)absQ + (axisOrder)) + 4 * stagedAbsQ);
                ++stagedAbsQ;
            }
        }
    }

    return 0;
}

static void LogCallback(const char *msg, char *userData)
{
    TTH_LOG_INFO("%s\n", msg);
    TTH_LOG_INFO("%s\n", userData);
}

errno_t ExportAsset(const Skeleton &skeleton, const Animation &animation)
{
    aiLogStream stream;
    stream.callback = LogCallback;
    aiAttachLogStream(&stream);

    errno_t err;

    aiScene scene = aiScene();
    scene.mName = "TelltaleHydra";
    scene.mRootNode = new aiNode("Scene Node");

    err = ConvertSkeleton(skeleton, *scene.mRootNode);
    if (err)
    {
        return err;
    }

    scene.mNumAnimations = 1;
    scene.mAnimations = new aiAnimation *[1];
    scene.mAnimations[0] = new aiAnimation();

    err = ConvertAnimation(animation, *scene.mAnimations[0]);
    if (err)
    {
        return err;
    }

    for (unsigned int i = 0; i < scene.mAnimations[0]->mNumChannels; ++i) // TODO: Find a better way
    {
        for (unsigned int j = 0; j < scene.mAnimations[0]->mChannels[i]->mNumPositionKeys; ++j)
        {
            aiQuaternion quat;
            aiVector3D vec;
            scene.mRootNode->FindNode(scene.mAnimations[0]->mChannels[i]->mNodeName)->mTransformation.DecomposeNoScaling(quat, vec);
            scene.mAnimations[0]->mChannels[i]->mPositionKeys[j].mValue *= vec.Length();
        }
    }

    Assimp::Exporter exporter;

    err = exporter.Export(&scene, "glb2", "assimpTWD.glb", aiProcess_ValidateDataStructure | aiProcess_LimitBoneWeights);
    if (err)
    {
        TTH_LOG_ERROR("%s\n", exporter.GetErrorString());
        return err;
    }

    aiDetachAllLogStreams();

    return 0;
}