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
#include <tth/animation/animation.hpp>
#include <tth/core/log.hpp>
#include <tth/skeleton/skeleton.hpp>

namespace TTH
{
static void LogCallback(const char *msg, char *userData) { TTH_LOG_INFO("%s\n", msg); }

errno_t ExportAsset(const char *resultPath, Skeleton skeleton, Animation *animation, size_t animationCount, size_t meshCount)
{
    aiLogStream stream;
    stream.callback = LogCallback;
    aiAttachLogStream(&stream);

    aiScene scene = aiScene();
    scene.mName = "TelltaleHydra";
    scene.mRootNode = new aiNode("Scene Node");

    for (size_t i = 0; i < skeleton.GetBoneCount(); ++i)
    {
        char name[32];
        snprintf(name, sizeof(name), "%016" PRIX64, skeleton.GetBoneCRC64(i).mCRC64);
        aiNode *node = new aiNode(name);

        const Vector3 *localPos = skeleton.GetBoneLocalPosition(i);
        const Quaternion *localRot = skeleton.GetBoneLocalRotation(i);

        node->mTransformation = aiMatrix4x4(aiVector3D(1.0f), aiQuaternion{localRot->w, localRot->x, localRot->y, localRot->z}, aiVector3D{localPos->x, localPos->y, localPos->z});

        if (skeleton.GetBoneParentIndex(i) >= 0)
        {
            snprintf(name, sizeof(name), "%016" PRIX64, skeleton.GetBoneCRC64(skeleton.GetBoneParentIndex(i)).mCRC64);
            node->mParent = scene.mRootNode->FindNode(name);
            node->mParent->addChildren(1, &node);
        }
        else // Root node
        {
            node->mParent = scene.mRootNode;
            scene.mRootNode->addChildren(1, &node);
        }
    }

    scene.mNumAnimations = animationCount;
    scene.mAnimations = new aiAnimation *[scene.mNumAnimations];

    for (size_t animationIndex = 0; animationIndex < animationCount; ++animationIndex)
    {
        scene.mAnimations[animationIndex] = new aiAnimation();

        scene.mAnimations[animationIndex]->mName.length =
            snprintf(scene.mAnimations[animationIndex]->mName.data, sizeof(scene.mAnimations[animationIndex]->mName.data), "%016" PRIX64, (uint64_t)((uintptr_t)scene.mAnimations[animationIndex]));
        scene.mAnimations[animationIndex]->mDuration = animation[animationIndex].GetDuration();
        scene.mAnimations[animationIndex]->mTicksPerSecond = 1.0;

        scene.mAnimations[animationIndex]->mNumChannels = animation[animationIndex].GetBoneCount();

        KeyframedValue<Vector3> *translations = new KeyframedValue<Vector3>[scene.mAnimations[animationIndex]->mNumChannels];
        KeyframedValue<Quaternion> *rotations = new KeyframedValue<Quaternion>[scene.mAnimations[animationIndex]->mNumChannels];
        animation[animationIndex].GetKeyframes(translations, rotations);

        const Symbol *boneNames = animation[animationIndex].GetBonesCRC64();
        scene.mAnimations[animationIndex]->mChannels = new aiNodeAnim *[scene.mAnimations[animationIndex]->mNumChannels];
        for (unsigned int i = 0; i < scene.mAnimations[animationIndex]->mNumChannels; ++i)
        {
            scene.mAnimations[animationIndex]->mChannels[i] = new aiNodeAnim();

            scene.mAnimations[animationIndex]->mChannels[i]->mNumPositionKeys = translations[i].mSamples.size();
            scene.mAnimations[animationIndex]->mChannels[i]->mNumRotationKeys = rotations[i].mSamples.size();
            scene.mAnimations[animationIndex]->mChannels[i]->mNumScalingKeys = translations[i].mSamples.size();

            scene.mAnimations[animationIndex]->mChannels[i]->mPositionKeys = new aiVectorKey[scene.mAnimations[animationIndex]->mChannels[i]->mNumPositionKeys];
            scene.mAnimations[animationIndex]->mChannels[i]->mRotationKeys = new aiQuatKey[scene.mAnimations[animationIndex]->mChannels[i]->mNumRotationKeys];
            scene.mAnimations[animationIndex]->mChannels[i]->mScalingKeys = new aiVectorKey[scene.mAnimations[animationIndex]->mChannels[i]->mNumScalingKeys];

            scene.mAnimations[animationIndex]->mChannels[i]->mNodeName.length =
                snprintf(scene.mAnimations[animationIndex]->mChannels[i]->mNodeName.data, sizeof(scene.mAnimations[animationIndex]->mChannels[i]->mNodeName.data), "%016" PRIX64, boneNames[i].mCRC64);

            for (unsigned int j = 0; j < scene.mAnimations[animationIndex]->mChannels[i]->mNumPositionKeys; ++j)
            {
                aiQuaternion quat;
                aiVector3D vec;
                scene.mRootNode->FindNode(scene.mAnimations[animationIndex]->mChannels[i]->mNodeName)->mTransformation.DecomposeNoScaling(quat, vec);

                scene.mAnimations[animationIndex]->mChannels[i]->mPositionKeys[j].mTime = translations[i].mSamples[j].mTime;
                scene.mAnimations[animationIndex]->mChannels[i]->mPositionKeys[j].mValue.x = translations[i].mSamples[j].mValue.x * vec.Length();
                scene.mAnimations[animationIndex]->mChannels[i]->mPositionKeys[j].mValue.y = translations[i].mSamples[j].mValue.y * vec.Length();
                scene.mAnimations[animationIndex]->mChannels[i]->mPositionKeys[j].mValue.z = translations[i].mSamples[j].mValue.z * vec.Length();

                scene.mAnimations[animationIndex]->mChannels[i]->mScalingKeys[j].mTime = translations[i].mSamples[j].mTime;
                scene.mAnimations[animationIndex]->mChannels[i]->mScalingKeys[j].mValue.x = 1.0f;
                scene.mAnimations[animationIndex]->mChannels[i]->mScalingKeys[j].mValue.y = 1.0f;
                scene.mAnimations[animationIndex]->mChannels[i]->mScalingKeys[j].mValue.z = 1.0f;
            }
            for (unsigned int j = 0; j < scene.mAnimations[animationIndex]->mChannels[i]->mNumRotationKeys; ++j)
            {
                scene.mAnimations[animationIndex]->mChannels[i]->mRotationKeys[j].mTime = rotations[i].mSamples[j].mTime;
                scene.mAnimations[animationIndex]->mChannels[i]->mRotationKeys[j].mValue.x = rotations[i].mSamples[j].mValue.x;
                scene.mAnimations[animationIndex]->mChannels[i]->mRotationKeys[j].mValue.y = rotations[i].mSamples[j].mValue.y;
                scene.mAnimations[animationIndex]->mChannels[i]->mRotationKeys[j].mValue.z = rotations[i].mSamples[j].mValue.z;
                scene.mAnimations[animationIndex]->mChannels[i]->mRotationKeys[j].mValue.w = rotations[i].mSamples[j].mValue.w;
            }
        }

        delete[] translations;
        delete[] rotations;
    }

    Assimp::Exporter exporter;

    errno_t err = exporter.Export(&scene, "glb2", resultPath, aiProcess_ValidateDataStructure);
    if (err)
    {
        TTH_LOG_ERROR("Error: %s\n", exporter.GetErrorString());
        return err;
    }

    aiDetachAllLogStreams();

    return err;
}
}; // namespace TTH