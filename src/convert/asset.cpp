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
#include <cinttypes>
#include <tth/convert/asset.hpp>
#include <tth/core/log.hpp>
#include <tth/meta/crc64/crc64.hpp>

namespace TTH
{

enum GFXPlatformVertexAttribute
{
    eGFXPlatformAttribute_Position,
    eGFXPlatformAttribute_Normal,
    eGFXPlatformAttribute_Tangent,
    eGFXPlatformAttribute_BlendWeight,
    eGFXPlatformAttribute_BlendIndex,
    eGFXPlatformAttribute_Color,
    eGFXPlatformAttribute_TexCoord,
    eGFXPlatformAttribute_Count,
    eGFXPlatformAttribute_None = -1
};

enum GFXPlatformFormat
{
    eGFXPlatformFormat_None,
    eGFXPlatformFormat_F32,
    eGFXPlatformFormat_F32x2,
    eGFXPlatformFormat_F32x3,
    eGFXPlatformFormat_F32x4,
    eGFXPlatformFormat_F16x2,
    eGFXPlatformFormat_F16x4,
    eGFXPlatformFormat_S32,
    eGFXPlatformFormat_U32,
    eGFXPlatformFormat_S32x2,
    eGFXPlatformFormat_U32x2,
    eGFXPlatformFormat_S32x3,
    eGFXPlatformFormat_U32x3,
    eGFXPlatformFormat_S32x4,
    eGFXPlatformFormat_U32x4,
    eGFXPlatformFormat_S16,
    eGFXPlatformFormat_U16,
    eGFXPlatformFormat_S16x2,
    eGFXPlatformFormat_U16x2,
    eGFXPlatformFormat_S16x4,
    eGFXPlatformFormat_U16x4,
    eGFXPlatformFormat_SN16,
    eGFXPlatformFormat_UN16,
    eGFXPlatformFormat_SN16x2,
    eGFXPlatformFormat_UN16x2,
    eGFXPlatformFormat_SN16x4,
    eGFXPlatformFormat_UN16x4,
    eGFXPlatformFormat_S8,
    eGFXPlatformFormat_U8,
    eGFXPlatformFormat_S8x2,
    eGFXPlatformFormat_U8x2,
    eGFXPlatformFormat_S8x4,
    eGFXPlatformFormat_U8x4,
    eGFXPlatformFormat_SN8,
    eGFXPlatformFormat_UN8,
    eGFXPlatformFormat_SN8x2,
    eGFXPlatformFormat_UN8x2,
    eGFXPlatformFormat_SN8x4,
    eGFXPlatformFormat_UN8x4,
    eGFXPlatformFormat_SN10_SN11_SN11,
    eGFXPlatformFormat_SN10x3_SN2,
    eGFXPlatformFormat_UN10x3_UN2,
    eGFXPlatformFormat_D3DCOLOR,
    eGFXPlatformFormat_Count
};

enum eGFXPlatformBufferUsage
{
    eGFXPlatformBuffer_None = 0x0,
    eGFXPlatformBuffer_Vertex = 0x1,
    eGFXPlatformBuffer_Index = 0x2,
    eGFXPlatformBuffer_Uniform = 0x4,
    eGFXPlatformBuffer_ShaderRead = 0x8,
    eGFXPlatformBuffer_ShaderWrite = 0x10,
    eGFXPlatformBuffer_ShaderReadWrite = 0x18,
    eGFXPlatformBuffer_ShaderRawAccess = 0x20,
    eGFXPlatformBuffer_ShaderReadRaw = 0x28,
    eGFXPlatformBuffer_ShaderWriteRaw = 0x30,
    eGFXPlatformBuffer_ShaderReadWriteRaw = 0x38,
    eGFXPlatformBuffer_DrawIndirectArgs = 0x40,
    eGFXPlatformBuffer_SingleValue = 0x80
};

errno_t ConvertSkeleton(const Skeleton &skeleton, aiNode &sceneNode)
{
    for (auto const &bone : skeleton.mEntries)
    {
        char name[32];
        snprintf(name, sizeof(name), "%016" PRIX64, bone.mJointName.mCrc64);
        aiNode *node = new aiNode(name);
        node->mTransformation =
            aiMatrix4x4(aiVector3D(1.0f), aiQuaternion(bone.mLocalQuat.w, bone.mLocalQuat.x, bone.mLocalQuat.y, bone.mLocalQuat.z), aiVector3D(bone.mLocalPos.x, bone.mLocalPos.y, bone.mLocalPos.z));

        if (bone.mParentIndex >= 0)
        {
            snprintf(name, sizeof(name), "%016" PRIX64, bone.mParentName.mCrc64);
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
    assimpAnimation.mName.length = snprintf(assimpAnimation.mName.data, sizeof(assimpAnimation.mName.data), "%016" PRIX64, animation.mName.mCrc64);
    assimpAnimation.mDuration = animation.mLength;
    assimpAnimation.mTicksPerSecond = 0.1 / 4.0;

    size_t maxFrameCount = 256; // Bad solution. Perhaps there is way of knowing beforehand what the maximum number of frames.

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
            snprintf(assimpAnimation.mChannels[i]->mNodeName.data, sizeof(assimpAnimation.mChannels[i]->mNodeName.data), "%016" PRIX64, ((uint64_t *)(cspkBuf + header.mSampleDataSize))[i]);
    }

    for (const uint32_t *headerData = (uint32_t *)(cspkBuf + header.mSampleDataSize + header.mBoneCount * sizeof(uint64_t)); headerData < (uint32_t *)(cspk->mpData + cspk->mDataSize); ++headerData)
    {
        if ((*headerData & 0x40000000) == 0) // Vector
        {
            assert(assimpAnimation.mChannels[(*headerData >> 0x10) & 0xfff]->mNumPositionKeys < maxFrameCount);

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
            assert(assimpAnimation.mChannels[(*headerData >> 0x10) & 0xfff]->mNumRotationKeys <= maxFrameCount);
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

static errno_t GetGlobalMatrix(aiMatrix4x4 &result, const aiNode &node)
{
    if (node.mParent != nullptr)
    {
        aiMatrix4x4 parentGlobalTransform;
        GetGlobalMatrix(parentGlobalTransform, *node.mParent);
        result *= parentGlobalTransform;
    }
    result *= node.mTransformation;
    return 0;
}

#define TRIANGLE_INDEX_COUNT 3 // A triangle has three corners.

errno_t ConvertD3DMesh(const D3DMesh &d3dmesh, aiMesh &mesh, const aiScene &scene)
{
    mesh.mAABB.mMin.x = d3dmesh.mMeshData.mBoundingBox.mMin.x;
    mesh.mAABB.mMin.y = d3dmesh.mMeshData.mBoundingBox.mMin.y;
    mesh.mAABB.mMin.z = d3dmesh.mMeshData.mBoundingBox.mMin.z;
    mesh.mAABB.mMax.x = d3dmesh.mMeshData.mBoundingBox.mMax.x;
    mesh.mAABB.mMax.y = d3dmesh.mMeshData.mBoundingBox.mMax.y;
    mesh.mAABB.mMax.z = d3dmesh.mMeshData.mBoundingBox.mMax.z;

    mesh.mNumBones = d3dmesh.mMeshData.mBones.size();
    mesh.mNumFaces = d3dmesh.mMeshData.mLODs[0].mNumPrimitives;
    mesh.mPrimitiveTypes = aiPrimitiveType_TRIANGLE;
    mesh.mNumVertices = d3dmesh.mMeshData.mLODs[0].mVertexCount;

    const uint8_t *d3dmeshData = d3dmesh.async;

    for (uint32_t index = 0; index < d3dmesh.mMeshData.mVertexStates[0].mIndexBufferCount; ++index)
    {
        assert(d3dmesh.mMeshData.mVertexStates[0].mpIndexBuffer[index].mBufferFormat == GFXPlatformFormat::eGFXPlatformFormat_U16);

        if (d3dmesh.mMeshData.mVertexStates[0].mpIndexBuffer[index].mBufferUsage != eGFXPlatformBufferUsage::eGFXPlatformBuffer_Index)
        {
            d3dmeshData += d3dmesh.mMeshData.mVertexStates[0].mpIndexBuffer[index].mStride * d3dmesh.mMeshData.mVertexStates[0].mpIndexBuffer[index].mCount;

            continue;
        }

        mesh.mNumFaces = d3dmesh.mMeshData.mVertexStates[0].mpIndexBuffer[index].mCount / TRIANGLE_INDEX_COUNT;
        mesh.mFaces = new aiFace[mesh.mNumFaces];
        for (unsigned int i = 0; i < mesh.mNumFaces; ++i)
        {
            mesh.mFaces[i].mNumIndices = TRIANGLE_INDEX_COUNT;
            mesh.mFaces[i].mIndices = new unsigned int[mesh.mFaces[i].mNumIndices];
            mesh.mFaces[i].mIndices[0] = *((uint16_t *)d3dmeshData);
            d3dmeshData += sizeof(uint16_t);
            mesh.mFaces[i].mIndices[1] = *((uint16_t *)d3dmeshData);
            d3dmeshData += sizeof(uint16_t);
            mesh.mFaces[i].mIndices[2] = *((uint16_t *)d3dmeshData);
            d3dmeshData += sizeof(uint16_t);
        }
    }

    const uint8_t *blendIndices = nullptr;
    const uint8_t *blendWeights = nullptr;
    // const GFXPlatformAttributeParams *blendIndicesAttribute = nullptr;
    // const GFXPlatformAttributeParams *blendWeightsAttribute = nullptr;
    const T3GFXBuffer *blendIndicesBuffer = nullptr;
    const T3GFXBuffer *blendWeightsBuffer = nullptr;

    for (uint32_t index = 0; index < d3dmesh.mMeshData.mVertexStates[0].mVertexBufferCount; ++index)
    {

        if (d3dmesh.mMeshData.mVertexStates[0].mAttributes[index].mAttribute == GFXPlatformVertexAttribute::eGFXPlatformAttribute_Position)
        {
            assert(d3dmesh.mMeshData.mVertexStates[0].mpVertexBuffer[index].mBufferFormat == GFXPlatformFormat::eGFXPlatformFormat_UN16x4);

            d3dmeshData += 4 * sizeof(uint16_t) * d3dmesh.mMeshData.mLODs[0].mVertexStart; // Skip vertices for other LODs
            mesh.mVertices = new aiVector3D[mesh.mNumVertices];
            for (unsigned int i = 0; i < mesh.mNumVertices; ++i)
            {
                mesh.mVertices[i].x = *((uint16_t *)d3dmeshData) / 65535.0f;
                d3dmeshData += sizeof(uint16_t);
                mesh.mVertices[i].y = *((uint16_t *)d3dmeshData) / 65535.0f;
                d3dmeshData += sizeof(uint16_t);
                mesh.mVertices[i].z = *((uint16_t *)d3dmeshData) / 65535.0f;
                d3dmeshData += 2 * sizeof(uint16_t); // Adding two to skip the 4th axis

                mesh.mVertices[i].x = mesh.mVertices[i].x * d3dmesh.mMeshData.mPositionScale.x + d3dmesh.mMeshData.mPositionOffset.x;
                mesh.mVertices[i].y = mesh.mVertices[i].y * d3dmesh.mMeshData.mPositionScale.y + d3dmesh.mMeshData.mPositionOffset.y;
                mesh.mVertices[i].z = mesh.mVertices[i].z * d3dmesh.mMeshData.mPositionScale.z + d3dmesh.mMeshData.mPositionOffset.z;
            }
        }
        else if (d3dmesh.mMeshData.mVertexStates[0].mAttributes[index].mAttribute == GFXPlatformVertexAttribute::eGFXPlatformAttribute_Normal)
        {
            assert(d3dmesh.mMeshData.mVertexStates[0].mAttributes[index].mFormat == GFXPlatformFormat::eGFXPlatformFormat_SN8x4);

            if (mesh.mNormals != nullptr)
            {
                continue;
            }
            mesh.mNormals = new aiVector3D[mesh.mNumVertices];
            for (unsigned int i = 0; i < mesh.mNumVertices; ++i)
            {
                mesh.mNormals[i].x = (*(int8_t *)d3dmeshData) / 127.0f;
                d3dmeshData += sizeof(int8_t);
                mesh.mNormals[i].y = (*(int8_t *)d3dmeshData) / 127.0f;
                d3dmeshData += sizeof(int8_t);
                mesh.mNormals[i].z = (*(int8_t *)d3dmeshData) / 127.0f;
                d3dmeshData += 2 * sizeof(int8_t);
            }
        }
        else if (d3dmesh.mMeshData.mVertexStates[0].mAttributes[index].mAttribute == GFXPlatformVertexAttribute::eGFXPlatformAttribute_Tangent)
        {
            assert(d3dmesh.mMeshData.mVertexStates[0].mAttributes[index].mFormat == GFXPlatformFormat::eGFXPlatformFormat_SN8x4);

            mesh.mTangents = new aiVector3D[mesh.mNumVertices];
            for (unsigned int i = 0; i < mesh.mNumVertices; ++i)
            {
                mesh.mTangents[i].x = (*(int8_t *)d3dmeshData) / 127.0f;
                d3dmeshData += sizeof(int8_t);
                mesh.mTangents[i].y = (*(int8_t *)d3dmeshData) / 127.0f;
                d3dmeshData += sizeof(int8_t);
                mesh.mTangents[i].z = (*(int8_t *)d3dmeshData) / 127.0f;
                d3dmeshData += 2 * sizeof(int8_t);
            }
        }
        else if (d3dmesh.mMeshData.mVertexStates[0].mAttributes[index].mAttribute == GFXPlatformVertexAttribute::eGFXPlatformAttribute_TexCoord)
        {
            d3dmeshData += d3dmesh.mMeshData.mVertexStates[0].mpVertexBuffer[index].mStride * d3dmesh.mMeshData.mVertexStates[0].mpVertexBuffer[index].mCount;
        }
        else if (d3dmesh.mMeshData.mVertexStates[0].mAttributes[index].mAttribute == GFXPlatformVertexAttribute::eGFXPlatformAttribute_Color)
        {
            d3dmeshData += d3dmesh.mMeshData.mVertexStates[0].mpVertexBuffer[index].mStride * d3dmesh.mMeshData.mVertexStates[0].mpVertexBuffer[index].mCount;
        }
        else if (d3dmesh.mMeshData.mVertexStates[0].mAttributes[index].mAttribute == GFXPlatformVertexAttribute::eGFXPlatformAttribute_BlendIndex)
        {
            assert(d3dmesh.mMeshData.mVertexStates[0].mpVertexBuffer[index].mBufferFormat == GFXPlatformFormat::eGFXPlatformFormat_U8x4);

            blendIndices = d3dmeshData;
            // blendIndicesAttribute = &d3dmesh.mMeshData.mVertexStates[0].mAttributes[index];
            blendIndicesBuffer = &d3dmesh.mMeshData.mVertexStates[0].mpVertexBuffer[index];
            d3dmeshData += d3dmesh.mMeshData.mVertexStates[0].mpVertexBuffer[index].mStride * d3dmesh.mMeshData.mVertexStates[0].mpVertexBuffer[index].mCount;
        }
        else if (d3dmesh.mMeshData.mVertexStates[0].mAttributes[index].mAttribute == GFXPlatformVertexAttribute::eGFXPlatformAttribute_BlendWeight)
        {
            assert(d3dmesh.mMeshData.mVertexStates[0].mpVertexBuffer[index].mBufferFormat == GFXPlatformFormat::eGFXPlatformFormat_UN10x3_UN2);

            blendWeights = d3dmeshData;
            // blendWeightsAttribute = &d3dmesh.mMeshData.mVertexStates[0].mAttributes[index];
            blendWeightsBuffer = &d3dmesh.mMeshData.mVertexStates[0].mpVertexBuffer[index];
            d3dmeshData += d3dmesh.mMeshData.mVertexStates[0].mpVertexBuffer[index].mStride * d3dmesh.mMeshData.mVertexStates[0].mpVertexBuffer[index].mCount;
        }
    }

    if (blendIndices != nullptr && blendWeights != nullptr)
    {
        assert(blendIndicesBuffer->mCount == blendWeightsBuffer->mCount);
        std::vector<std::vector<aiVertexWeight>> vectors(mesh.mNumBones);

        for (uint32_t i = 0; i < blendIndicesBuffer->mCount; ++i)
        {
            uint32_t d3dBlendData = *(uint32_t *)(blendWeights);
            if (*blendIndices >= mesh.mNumBones)
            {
                TTH_LOG_ERROR("blend index %d out of bounds!\n", *blendIndices);
            }

            vectors[*(blendIndices++)].emplace_back(i, 1.0f - (float)(d3dBlendData & 0x3ff) / 1023.0f / 8.0f - (float)(d3dBlendData >> 30) / 8.0f -
                                                           (float)(d3dBlendData >> 10 & 0x3ff) / 1023.0f / 3.0f - (float)(d3dBlendData >> 20 & 0x3ff) / 1023.0f / 4.0f);
            vectors[*(blendIndices++)].emplace_back(i, (float)(d3dBlendData & 0x3ff) / 1023.0f / 8.0f + (float)(d3dBlendData >> 30) / 8.0f);
            vectors[*(blendIndices++)].emplace_back(i, (float)(d3dBlendData >> 10 & 0x3ff) / 1023.0f / 3.0f);
            vectors[*(blendIndices++)].emplace_back(i, (float)(d3dBlendData >> 20 & 0x3ff) / 1023.0f / 4.0f);

            blendWeights += sizeof(d3dBlendData);
        }

        mesh.mBones = new aiBone *[mesh.mNumBones];

        for (unsigned int i = 0; i < mesh.mNumBones; ++i)
        {
            mesh.mBones[i] = new aiBone();
            mesh.mBones[i]->mName.length = snprintf(mesh.mBones[i]->mName.data, sizeof(mesh.mBones[i]->mName.data), "%016" PRIX64, d3dmesh.mMeshData.mBones[i].mBoneName.mCrc64);

            mesh.mBones[i]->mNode = scene.mRootNode->FindNode(mesh.mBones[i]->mName);
            GetGlobalMatrix(mesh.mBones[i]->mOffsetMatrix, *mesh.mBones[i]->mNode);
            aiMatrix4Inverse(&mesh.mBones[i]->mOffsetMatrix);

            /* Due to inaccuracy in matrix functions, we need to set the matrix values to an accurate value */
            mesh.mBones[i]->mOffsetMatrix.d1 = 0.0f;
            mesh.mBones[i]->mOffsetMatrix.d2 = 0.0f;
            mesh.mBones[i]->mOffsetMatrix.d3 = 0.0f;
            mesh.mBones[i]->mOffsetMatrix.d4 = 1.0f;

            mesh.mBones[i]->mNumWeights = vectors[i].size();
            mesh.mBones[i]->mWeights = new aiVertexWeight[mesh.mBones[i]->mNumWeights];
            for (unsigned int j = 0; j < mesh.mBones[i]->mNumWeights; ++j)
            {
                mesh.mBones[i]->mWeights[j] = vectors[i][j];
            }
        }
    }

    return 0;
}

static void LogCallback(const char *msg, char *userData) { TTH_LOG_INFO("%s\n", msg); }

errno_t ExportAsset(const char *resultPath, const Skeleton &skeleton, const Animation *animations, const D3DMesh *meshes, size_t animationCount, size_t meshCount)
{
    aiLogStream stream;
    stream.callback = LogCallback;
    aiAttachLogStream(&stream);

    errno_t err = 0;

    aiScene scene = aiScene();
    scene.mName = "TelltaleHydra";
    scene.mRootNode = new aiNode("Scene Node");

    err = ConvertSkeleton(skeleton, *scene.mRootNode);
    if (err)
    {
        return err;
    }

    scene.mNumAnimations = animationCount;
    scene.mAnimations = new aiAnimation *[scene.mNumAnimations];

    for (size_t i = 0; i < scene.mNumAnimations; ++i)
    {
        scene.mAnimations[i] = new aiAnimation();

        err = ConvertAnimation(animations[i], *scene.mAnimations[i]);
        if (err)
        {
            return err;
        }

        for (unsigned int j = 0; j < scene.mAnimations[i]->mNumChannels; ++j) // TODO: Find a better way
        {
            scene.mAnimations[i]->mChannels[j]->mNumScalingKeys = scene.mAnimations[i]->mChannels[j]->mNumPositionKeys;
            scene.mAnimations[i]->mChannels[j]->mScalingKeys = new aiVectorKey[scene.mAnimations[i]->mChannels[j]->mNumScalingKeys];
            for (unsigned int k = 0; k < scene.mAnimations[i]->mChannels[j]->mNumPositionKeys; ++k)
            {
                aiQuaternion quat;
                aiVector3D vec;
                scene.mRootNode->FindNode(scene.mAnimations[i]->mChannels[j]->mNodeName)->mTransformation.DecomposeNoScaling(quat, vec);
                scene.mAnimations[i]->mChannels[j]->mPositionKeys[k].mValue *= vec.Length();

                scene.mAnimations[i]->mChannels[j]->mScalingKeys[k] = aiVectorKey(scene.mAnimations[i]->mChannels[j]->mPositionKeys[k].mTime, aiVector3D(1.0f));
            }
        }
    }

    scene.mNumMeshes = meshCount;
    scene.mMeshes = new aiMesh *[meshCount];
    scene.mRootNode->mMeshes = new unsigned int[scene.mNumMeshes];
    scene.mRootNode->mNumMeshes = scene.mNumMeshes;

    scene.mNumMaterials = 1;
    scene.mMaterials = new aiMaterial *[1];
    scene.mMaterials[0] = new aiMaterial();

    for (unsigned int i = 0; i < scene.mNumMeshes; ++i)
    {
        scene.mMeshes[i] = new aiMesh();
        scene.mMeshes[i]->mMaterialIndex = 0;

        scene.mRootNode->mMeshes[i] = i;

        err = ConvertD3DMesh(meshes[i], *scene.mMeshes[i], scene);
        if (err)
        {
            return err;
        }
    }

    Assimp::Exporter exporter;

    err = exporter.Export(&scene, "fbx", resultPath, aiProcess_ValidateDataStructure | aiProcess_LimitBoneWeights);
    if (err)
    {
        TTH_LOG_ERROR("Error: %s\n", exporter.GetErrorString());
        return err;
    }

    aiDetachAllLogStreams();

    return 0;
}
} // namespace TTH