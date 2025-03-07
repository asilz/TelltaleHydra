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
#include <tth/d3dmesh/d3dmesh.hpp>
#include <tth/skeleton/skeleton.hpp>
#include <vector>

namespace TTH
{
static void LogCallback(const char *msg, char *userData) { TTH_LOG_INFO("%s\n", msg); }

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

errno_t ExportAsset(const char *resultPath, Skeleton skeleton, const Animation *animation, const D3DMesh *meshes, size_t animationCount, size_t meshCount)
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
            printf("Assimp translation %lX [%f, %f, %f]\n", boneNames[i].mCRC64, scene.mAnimations[animationIndex]->mChannels[i]->mPositionKeys[0].mValue.x,
                   scene.mAnimations[animationIndex]->mChannels[i]->mPositionKeys[0].mValue.y, scene.mAnimations[animationIndex]->mChannels[i]->mPositionKeys[0].mValue.z);
        }

        delete[] translations;
        delete[] rotations;
    }

    scene.mNumMaterials = 1;
    scene.mMaterials = new aiMaterial *[1];
    scene.mMaterials[0] = new aiMaterial();

    scene.mNumMeshes = meshCount;
    scene.mMeshes = new aiMesh *[scene.mNumMeshes];
    scene.mRootNode->mNumMeshes = scene.mNumMeshes;
    scene.mRootNode->mMeshes = new unsigned int[scene.mRootNode->mNumMeshes];

    for (unsigned int meshIndex = 0; meshIndex < scene.mNumMeshes; ++meshIndex)
    {
        scene.mRootNode->mMeshes[meshIndex] = meshIndex;
        scene.mMeshes[meshIndex] = new aiMesh;
        scene.mMeshes[meshIndex]->mPrimitiveTypes = aiPrimitiveType_TRIANGLE;
        scene.mMeshes[meshIndex]->mMaterialIndex = 0;
        scene.mMeshes[meshIndex]->mNumFaces = meshes[meshIndex].GetIndexCount() / 3;
        scene.mMeshes[meshIndex]->mFaces = new aiFace[scene.mMeshes[meshIndex]->mNumFaces];
        D3DMesh::GFXPlatformFormat format;
        const uint8_t *indices = static_cast<const uint8_t *>(meshes[meshIndex].GetIndices(format, 0, 0));
        for (unsigned int i = 0; i < scene.mMeshes[meshIndex]->mNumFaces; ++i)
        {
            scene.mMeshes[meshIndex]->mFaces[i].mNumIndices = 3;
            scene.mMeshes[meshIndex]->mFaces[i].mIndices = new unsigned int[scene.mMeshes[meshIndex]->mFaces[i].mNumIndices]();

            memcpy(&scene.mMeshes[meshIndex]->mFaces[i].mIndices[0], indices, D3DMesh::GetFormatStride(format));
            indices += D3DMesh::GetFormatStride(format);
            memcpy(&scene.mMeshes[meshIndex]->mFaces[i].mIndices[1], indices, D3DMesh::GetFormatStride(format));
            indices += D3DMesh::GetFormatStride(format);
            memcpy(&scene.mMeshes[meshIndex]->mFaces[i].mIndices[2], indices, D3DMesh::GetFormatStride(format));
            indices += D3DMesh::GetFormatStride(format);
        }

        scene.mMeshes[meshIndex]->mNumVertices = meshes[meshIndex].GetVertexCount();
        scene.mMeshes[meshIndex]->mNumBones = meshes[meshIndex].GetBoneCount(0);

        const void *vertexBuffers[32];
        D3DMesh::AttributeDescription descriptions[32][32];

        scene.mMeshes[meshIndex]->mVertices = new aiVector3D[scene.mMeshes[meshIndex]->mNumVertices];
        scene.mMeshes[meshIndex]->mNormals = new aiVector3D[scene.mMeshes[meshIndex]->mNumVertices];
        scene.mMeshes[meshIndex]->mTangents = new aiVector3D[scene.mMeshes[meshIndex]->mNumVertices];

        std::vector<std::vector<aiVertexWeight>> vertexWeights(scene.mMeshes[meshIndex]->mNumBones); // TODO: This causes cache misses, is there a way to fix it?

        float *blendWeights = new float[scene.mMeshes[meshIndex]->mNumVertices * 4];
        uint8_t *blendIndices = new uint8_t[scene.mMeshes[meshIndex]->mNumVertices * 4];

        for (size_t bufferIndex = 0; bufferIndex < meshes[meshIndex].GetVertexBufferCount(); ++bufferIndex)
        {
            vertexBuffers[bufferIndex] = meshes[meshIndex].GetVertexBuffer(bufferIndex, 0, 0, descriptions[bufferIndex]);
            for (unsigned int vertexIndex = 0; vertexIndex < scene.mMeshes[meshIndex]->mNumVertices; ++vertexIndex)
            {
                for (size_t attributeIndex = 0; attributeIndex < meshes[meshIndex].GetVertexBufferAttributeCount(bufferIndex); ++attributeIndex)
                {

                    if (descriptions[bufferIndex][attributeIndex].attribute == D3DMesh::GFXPlatformVertexAttribute::eGFXPlatformAttribute_Position)
                    {

                        if (descriptions[bufferIndex][attributeIndex].format == D3DMesh::GFXPlatformFormat::eGFXPlatformFormat_UN16x4)
                        {
                            scene.mMeshes[meshIndex]->mVertices[vertexIndex].x = *(static_cast<const uint16_t *>(vertexBuffers[bufferIndex])) / 65535.0f;
                            vertexBuffers[bufferIndex] = static_cast<const void *>(static_cast<const uint16_t *>(vertexBuffers[bufferIndex]) + 1);
                            scene.mMeshes[meshIndex]->mVertices[vertexIndex].y = *(static_cast<const uint16_t *>(vertexBuffers[bufferIndex])) / 65535.0f;
                            vertexBuffers[bufferIndex] = static_cast<const void *>(static_cast<const uint16_t *>(vertexBuffers[bufferIndex]) + 1);
                            scene.mMeshes[meshIndex]->mVertices[vertexIndex].z = *(static_cast<const uint16_t *>(vertexBuffers[bufferIndex])) / 65535.0f;
                            vertexBuffers[bufferIndex] = static_cast<const void *>(static_cast<const uint16_t *>(vertexBuffers[bufferIndex]) + 2);
                        }
                        else if (descriptions[bufferIndex][attributeIndex].format == D3DMesh::GFXPlatformFormat::eGFXPlatformFormat_F32x3)
                        {
                            scene.mMeshes[meshIndex]->mVertices[vertexIndex].x = *static_cast<const float *>(vertexBuffers[bufferIndex]);
                            vertexBuffers[bufferIndex] = static_cast<const void *>(static_cast<const float *>(vertexBuffers[bufferIndex]) + 1);
                            scene.mMeshes[meshIndex]->mVertices[vertexIndex].y = *static_cast<const float *>(vertexBuffers[bufferIndex]);
                            vertexBuffers[bufferIndex] = static_cast<const void *>(static_cast<const float *>(vertexBuffers[bufferIndex]) + 1);
                            scene.mMeshes[meshIndex]->mVertices[vertexIndex].z = *static_cast<const float *>(vertexBuffers[bufferIndex]);
                            vertexBuffers[bufferIndex] = static_cast<const void *>(static_cast<const float *>(vertexBuffers[bufferIndex]) + 1);
                        }
                        else
                        {
                            assert(0);
                        }

                        const Vector3 *offset = meshes[meshIndex].GetPositionOffset();
                        const Vector3 *scale = meshes[meshIndex].GetPositionScale();
                        scene.mMeshes[meshIndex]->mVertices[vertexIndex].x = scene.mMeshes[meshIndex]->mVertices[vertexIndex].x * scale->x + offset->x;
                        scene.mMeshes[meshIndex]->mVertices[vertexIndex].y = scene.mMeshes[meshIndex]->mVertices[vertexIndex].y * scale->y + offset->y;
                        scene.mMeshes[meshIndex]->mVertices[vertexIndex].z = scene.mMeshes[meshIndex]->mVertices[vertexIndex].z * scale->z + offset->z;
                    }

                    if (descriptions[bufferIndex][attributeIndex].attribute == D3DMesh::GFXPlatformVertexAttribute::eGFXPlatformAttribute_Normal)
                    {
                        assert(descriptions[bufferIndex][attributeIndex].format == D3DMesh::GFXPlatformFormat::eGFXPlatformFormat_SN8x4);
                        scene.mMeshes[meshIndex]->mNormals[vertexIndex].x = *(static_cast<const int8_t *>(vertexBuffers[bufferIndex])) / 127.0f;
                        vertexBuffers[bufferIndex] = static_cast<const void *>(static_cast<const int8_t *>(vertexBuffers[bufferIndex]) + 1);
                        scene.mMeshes[meshIndex]->mNormals[vertexIndex].y = *(static_cast<const int8_t *>(vertexBuffers[bufferIndex])) / 127.0f;
                        vertexBuffers[bufferIndex] = static_cast<const void *>(static_cast<const int8_t *>(vertexBuffers[bufferIndex]) + 1);
                        scene.mMeshes[meshIndex]->mNormals[vertexIndex].z = *(static_cast<const int8_t *>(vertexBuffers[bufferIndex])) / 127.0f;
                        vertexBuffers[bufferIndex] = static_cast<const void *>(static_cast<const int8_t *>(vertexBuffers[bufferIndex]) + 2);
                    }

                    if (descriptions[bufferIndex][attributeIndex].attribute == D3DMesh::GFXPlatformVertexAttribute::eGFXPlatformAttribute_Tangent)
                    {
                        assert(descriptions[bufferIndex][attributeIndex].format == D3DMesh::GFXPlatformFormat::eGFXPlatformFormat_SN8x4);
                        scene.mMeshes[meshIndex]->mTangents[vertexIndex].x = *(static_cast<const int8_t *>(vertexBuffers[bufferIndex])) / 127.0f;
                        vertexBuffers[bufferIndex] = static_cast<const void *>(static_cast<const int8_t *>(vertexBuffers[bufferIndex]) + 1);
                        scene.mMeshes[meshIndex]->mTangents[vertexIndex].y = *(static_cast<const int8_t *>(vertexBuffers[bufferIndex])) / 127.0f;
                        vertexBuffers[bufferIndex] = static_cast<const void *>(static_cast<const int8_t *>(vertexBuffers[bufferIndex]) + 1);
                        scene.mMeshes[meshIndex]->mTangents[vertexIndex].z = *(static_cast<const int8_t *>(vertexBuffers[bufferIndex])) / 127.0f;
                        vertexBuffers[bufferIndex] = static_cast<const void *>(static_cast<const int8_t *>(vertexBuffers[bufferIndex]) + 2);
                    }

                    if (descriptions[bufferIndex][attributeIndex].attribute == D3DMesh::GFXPlatformVertexAttribute::eGFXPlatformAttribute_BlendIndex)
                    {
                        assert(descriptions[bufferIndex][attributeIndex].format == D3DMesh::GFXPlatformFormat::eGFXPlatformFormat_U8x4);
                        memcpy(blendIndices + vertexIndex * 4, vertexBuffers[bufferIndex], 4 * sizeof(*blendIndices));
                        vertexBuffers[bufferIndex] = static_cast<const void *>(static_cast<const uint8_t *>(vertexBuffers[bufferIndex]) + 4);
                    }

                    if (descriptions[bufferIndex][attributeIndex].attribute == D3DMesh::GFXPlatformVertexAttribute::eGFXPlatformAttribute_BlendWeight)
                    {
                        if (descriptions[bufferIndex][attributeIndex].format == D3DMesh::GFXPlatformFormat::eGFXPlatformFormat_UN16x4)
                        {
                            blendWeights[0 + vertexIndex * 4] = *(static_cast<const uint16_t *>(vertexBuffers[bufferIndex])) / 65535.0f;
                            vertexBuffers[bufferIndex] = static_cast<const void *>(static_cast<const uint16_t *>(vertexBuffers[bufferIndex]) + 1);
                            blendWeights[1 + vertexIndex * 4] = *(static_cast<const uint16_t *>(vertexBuffers[bufferIndex])) / 65535.0f;
                            vertexBuffers[bufferIndex] = static_cast<const void *>(static_cast<const uint16_t *>(vertexBuffers[bufferIndex]) + 1);
                            blendWeights[2 + vertexIndex * 4] = *(static_cast<const uint16_t *>(vertexBuffers[bufferIndex])) / 65535.0f;
                            vertexBuffers[bufferIndex] = static_cast<const void *>(static_cast<const uint16_t *>(vertexBuffers[bufferIndex]) + 1);
                            blendWeights[3 + vertexIndex * 4] = *(static_cast<const uint16_t *>(vertexBuffers[bufferIndex])) / 65535.0f;
                            vertexBuffers[bufferIndex] = static_cast<const void *>(static_cast<const uint16_t *>(vertexBuffers[bufferIndex]) + 1);
                        }
                        else if (descriptions[bufferIndex][attributeIndex].format == D3DMesh::GFXPlatformFormat::eGFXPlatformFormat_UN10x3_UN2)
                        {
                            const uint32_t *weight = static_cast<const uint32_t *>(vertexBuffers[bufferIndex]);
                            blendWeights[1 + vertexIndex * 4] = (float)(*weight & 0x3ff) / 1023.0f / 8.0f + (float)(*weight >> 30) / 8.0f;
                            blendWeights[2 + vertexIndex * 4] = (float)(*weight >> 10 & 0x3ff) / 1023.0f / 3.0f;
                            blendWeights[3 + vertexIndex * 4] = (float)(*weight >> 20 & 0x3ff) / 1023.0f / 4.0f;
                            blendWeights[0 + vertexIndex * 4] = 1.0f - blendWeights[1] - blendWeights[2] - blendWeights[3];
                            vertexBuffers[bufferIndex] = static_cast<const void *>(static_cast<const uint32_t *>(vertexBuffers[bufferIndex]) + 1);
                        }
                        else
                        {
                            assert(0);
                        }
                    }
                }
            }
        }

        for (unsigned int i = 0; i < scene.mMeshes[meshIndex]->mNumVertices; ++i)
        {
            vertexWeights[blendIndices[0 + i * 4]].emplace_back(i, blendWeights[0 + i * 4]);
            vertexWeights[blendIndices[1 + i * 4]].emplace_back(i, blendWeights[1 + i * 4]);
            vertexWeights[blendIndices[2 + i * 4]].emplace_back(i, blendWeights[2 + i * 4]);
            vertexWeights[blendIndices[3 + i * 4]].emplace_back(i, blendWeights[3 + i * 4]);
        }

        delete[] blendIndices;
        delete[] blendWeights;

        scene.mMeshes[meshIndex]->mBones = new aiBone *[scene.mMeshes[meshIndex]->mNumBones];
        for (unsigned int i = 0; i < scene.mMeshes[meshIndex]->mNumBones; ++i)
        {
            scene.mMeshes[meshIndex]->mBones[i] = new aiBone();
            scene.mMeshes[meshIndex]->mBones[i]->mName.length =
                snprintf(scene.mMeshes[meshIndex]->mBones[i]->mName.data, sizeof(scene.mMeshes[meshIndex]->mName.data), "%016" PRIX64, meshes[meshIndex].GetBoneName(0, i));

            scene.mMeshes[meshIndex]->mBones[i]->mNode = scene.mRootNode->FindNode(scene.mMeshes[meshIndex]->mBones[i]->mName);
            GetGlobalMatrix(scene.mMeshes[meshIndex]->mBones[i]->mOffsetMatrix, *scene.mMeshes[meshIndex]->mBones[i]->mNode);

            printf("---------- \nAssimp offset matrix %lX\n%f,%f,%f,%f\n%f,%f,%f,%f\n%f,%f,%f,%f\n%f,%f,%f,%f\n", meshes[meshIndex].GetBoneName(0, i),
                   scene.mMeshes[meshIndex]->mBones[i]->mOffsetMatrix[0][0], scene.mMeshes[meshIndex]->mBones[i]->mOffsetMatrix[0][1], scene.mMeshes[meshIndex]->mBones[i]->mOffsetMatrix[0][2],
                   scene.mMeshes[meshIndex]->mBones[i]->mOffsetMatrix[0][3], scene.mMeshes[meshIndex]->mBones[i]->mOffsetMatrix[1][0], scene.mMeshes[meshIndex]->mBones[i]->mOffsetMatrix[1][1],
                   scene.mMeshes[meshIndex]->mBones[i]->mOffsetMatrix[1][2], scene.mMeshes[meshIndex]->mBones[i]->mOffsetMatrix[1][3], scene.mMeshes[meshIndex]->mBones[i]->mOffsetMatrix[2][0],
                   scene.mMeshes[meshIndex]->mBones[i]->mOffsetMatrix[2][1], scene.mMeshes[meshIndex]->mBones[i]->mOffsetMatrix[2][2], scene.mMeshes[meshIndex]->mBones[i]->mOffsetMatrix[2][3],
                   scene.mMeshes[meshIndex]->mBones[i]->mOffsetMatrix[3][0], scene.mMeshes[meshIndex]->mBones[i]->mOffsetMatrix[3][1], scene.mMeshes[meshIndex]->mBones[i]->mOffsetMatrix[3][2],
                   scene.mMeshes[meshIndex]->mBones[i]->mOffsetMatrix[3][3]);
            aiMatrix4Inverse(&scene.mMeshes[meshIndex]->mBones[i]->mOffsetMatrix);

            /* Due to inaccuracy in matrix functions, we need to set the matrix values to an accurate value */
            scene.mMeshes[meshIndex]->mBones[i]->mOffsetMatrix.d1 = 0.0f;
            scene.mMeshes[meshIndex]->mBones[i]->mOffsetMatrix.d2 = 0.0f;
            scene.mMeshes[meshIndex]->mBones[i]->mOffsetMatrix.d3 = 0.0f;
            scene.mMeshes[meshIndex]->mBones[i]->mOffsetMatrix.d4 = 1.0f;

            scene.mMeshes[meshIndex]->mBones[i]->mNumWeights = vertexWeights[i].size();
            scene.mMeshes[meshIndex]->mBones[i]->mWeights = new aiVertexWeight[scene.mMeshes[meshIndex]->mBones[i]->mNumWeights];
            for (unsigned int j = 0; j < scene.mMeshes[meshIndex]->mBones[i]->mNumWeights; ++j)
            {
                scene.mMeshes[meshIndex]->mBones[i]->mWeights[j] = vertexWeights[i][j];
            }
        }
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