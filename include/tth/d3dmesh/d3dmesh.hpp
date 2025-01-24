#pragma once

#include <tth/crypto/crc64.hpp>
#include <tth/linalg/transform.hpp>
#include <tth/stream/stream.hpp>

class Any;

namespace TTH
{
class D3DMesh
{
  private:
    class Impl;
    Impl *impl;

  public:
    int32_t Read(Stream &stream);
    int32_t Write(Stream &stream) const;

    /**
     * @brief Retrieves the number of LODs in the mesh
     *
     * @return LOD count
     */
    size_t GetLODCount() const;

    /**
     * @brief Retrieves the number of mesh batches in an LOD
     *
     * @param LODIndex LOD index
     * @return Batch count
     */
    size_t GetBatchCount(size_t LODIndex) const;

    /**
     * @brief Retrieves the number of vertices in the entire d3dmesh
     *
     * @return Vertex count
     */
    size_t GetVertexCount() const;

    /**
     * @brief Retrieves the number of vertices in the mesh LOD batch
     *
     * @param LODIndex index of the LOD
     * @param batchIndex index of the batch inside the LOD
     * @return Vertex count
     */
    size_t GetVertexCount(size_t LODIndex, size_t batchIndex) const;

    /**
     * @brief Retrieves the vertex positions in an LOD batch and stores them in @p positions
     *
     * @param positions buffer to store the positions
     * @param LODIndex index of the LOD
     * @param batchIndex index of the batch inside the LOD
     * @return error code
     */
    errno_t GetVertexPositions(uint16_t *positions, size_t LODIndex, size_t batchIndex) const;

    /**
     * @brief Retrieves the vertex normals in an LOD batch and stores them in @p normals
     *
     * @param normals buffer to store the normals
     * @param LODIndex index of the LOD
     * @param batchIndex index of the batch inside the LOD
     * @return error code
     */
    errno_t GetVertexNormals(int8_t *normals, size_t LODIndex, size_t batchIndex) const;

    /**
     * @brief Retrieves the vertex tangents in an LOD batch and stores them in @p tangents
     *
     * @param tangents buffer to store the tangents
     * @param LODIndex index of the LOD
     * @param batchIndex index of the batch inside the LOD
     * @return error code
     */
    errno_t GetVertexTangents(int8_t *tangents, size_t LODIndex, size_t batchIndex) const;

    /**
     * @brief Retrieves the vertex blend indices in an LOD batch and stores them in @p blendIndices
     *
     * @param blendIndices buffer to store the blend indices
     * @param LODIndex index of the LOD
     * @param batchIndex index of the batch inside the LOD
     * @return error code
     */
    errno_t GetVertexBlendIndices(uint8_t *blendIndices, size_t LODIndex, size_t batchIndex) const;

    /**
     * @brief Retrieves the vertex blend weights in an LOD batch and stores them in @p blendWeights
     *
     * @param blendWeights buffer to store the blend weights, the buffer must have enough capacity to store 4 floats per vertex
     * @param LODIndex index of the LOD
     * @param batchIndex index of the batch inside the LOD
     * @return error code
     */
    errno_t GetVertexBlendWeights(float *blendWeights, size_t LODIndex, size_t batchIndex) const;

    /**
     * @brief Retrieves the number of vertex indices in the mesh LOD batch
     *
     * @param LODIndex index of the LOD
     * @param batchIndex index of the batch inside the LOD
     * @return Index count
     */
    size_t GetVertexIndexCount(size_t LODIndex, size_t batchIndex) const;

    /**
     * @brief Retrieves the vertex indices for an LOD batch and stores them in @p blendWeights
     *
     * @param blendWeights buffer to store the vertex indices
     * @param LODIndex index of the LOD
     * @param batchIndex index of the batch inside the LOD
     * @return error code
     */
    errno_t GetVertexIndices(uint16_t *indices, size_t LODIndex, size_t batchIndex) const;

    /**
     * @brief Retrieves the position scale of the entire d3dmesh
     *
     * @return pointer to scale vector, nullptr if it does not exist
     */
    const Vector3 *GetPositionScale() const;

    /**
     * @brief Retrieves the position offset of the entire d3dmesh
     *
     * @return pointer to offset vector, nullptr if it does not exist
     */
    const Vector3 *GetPositionOffset() const;

    /**
     * @brief Retrives an async resource
     *
     * @param name Name symbol of the async resource to retrieve
     * @return pointer to any, nullptr if it does not exist
     */
    const Any *GetAsyncResource(Symbol name) const;

    /**
     * @brief Retrieves the type CRC64 of this datatype
     *
     * @return CRC64
     */
    static constexpr uint64_t GetTypeCRC64() { return CRC64_CaseInsensitive("D3DMesh"); }

    static constexpr bool IS_BLOCKED = true;

    errno_t Create();
    void Destroy();
};
}; // namespace TTH