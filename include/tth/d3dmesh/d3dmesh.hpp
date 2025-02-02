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
        eGFXPlatformAttribute_None = 0xffffffff
    };

    int32_t Read(Stream &stream) noexcept;
    int32_t Write(Stream &stream) const noexcept;

    struct AttributeDescription
    {
        GFXPlatformVertexAttribute attribute;
        GFXPlatformFormat format;
        size_t offset;
    };

    /**
     * @brief Retrieves the number of LODs in the mesh
     *
     * @return LOD count
     */
    size_t GetLODCount() const noexcept;

    /**
     * @brief Retrieves the number of mesh batches in an LOD
     *
     * @param LODIndex LOD index
     * @return Batch count
     */
    size_t GetBatchCount(size_t LODIndex) const noexcept;

    /**
     * @brief Retrieves the number of vertices in the entire d3dmesh
     *
     * @return Vertex count
     */
    size_t GetVertexCount() const noexcept;

    /**
     * @brief Retrieves the number of vertices in the mesh LOD batch
     *
     * @param LODIndex index of the LOD
     * @param batchIndex index of the batch inside the LOD
     * @return Vertex count
     */
    size_t GetVertexCount(size_t LODIndex, size_t batchIndex) const noexcept;

    /**
     * @brief Retrieves the number of vertex buffers in the mesh
     *
     * @return Vertex buffer count
     */
    size_t GetVertexBufferCount() const noexcept;

    /**
     * @brief Retrieves the number of attributes in a vertex buffer
     *
     * @param bufferIndex vertex buffer index
     * @return attribute count
     */
    size_t GetVertexBufferAttributeCount(size_t bufferIndex) const noexcept;

    /**
     * @brief Returns a pointer to a vertex buffer located in a LOD batch
     *
     * @param bufferIndex vertex buffer index
     * @param descriptions output that describes the attributes stored in the buffer
     * @return pointer to data, nullptr if data does not exist
     */
    const void *GetVertexBuffer(size_t bufferIndex, size_t LODIndex, size_t batchIndex, AttributeDescription *descriptions) const noexcept;

    /**
     * @brief Retrieves the number of vertex indices in the entire mesh
     *
     * @return Index count
     */
    size_t GetIndexCount() const noexcept;

    /**
     * @brief Retrieves the number of vertex indices in the mesh LOD batch
     *
     * @param LODIndex index of the LOD
     * @param batchIndex index of the batch inside the LOD
     * @return Index count
     */
    size_t GetIndexCount(size_t LODIndex, size_t batchIndex) const noexcept;

    /**
     * @brief Returns a pointer to the index data located in a LOD batch
     *
     * @param format output to indicate the format of the data
     * @param LODIndex index of the LOD
     * @param batchIndex index of the batch inside the LOD
     * @return pointer to data, nullptr if data does not exist
     */
    const void *GetIndices(GFXPlatformFormat &format, size_t LODIndex, size_t batchIndex) const noexcept;

    /**
     * @brief Retrieves the position scale of the entire d3dmesh
     *
     * @return pointer to scale vector, nullptr if it does not exist
     */
    const Vector3 *GetPositionScale() const noexcept;

    /**
     * @brief Retrieves the position offset of the entire d3dmesh
     *
     * @return pointer to offset vector, nullptr if it does not exist
     */
    const Vector3 *GetPositionOffset() const noexcept;

    /**
     * @brief Retrieves the number of bones that the vertices in the LOD are dependent on
     *
     * @param LODIndex LOD index
     * @return bone count
     */
    size_t GetBoneCount(size_t LODIndex) const noexcept;

    /**
     * @brief Retrieves the name hash of a bone in an LOD
     *
     * @param LODIndex LOD index
     * @param boneIndex index of the bone to retrieve the name hash of
     * @return CRC64
     */
    uint64_t GetBoneName(size_t LODIndex, size_t boneIndex) const noexcept;

    /**
     * @brief Returns the stride of @p format
     *
     * @param format format to retrieve the stride of
     * @return stride of format
     */
    static constexpr size_t GetFormatStride(GFXPlatformFormat format)
    {
        switch (format)
        {
        case eGFXPlatformFormat_None:
            return 0;
        case eGFXPlatformFormat_F32:
            return sizeof(float);
        case eGFXPlatformFormat_F32x2:
            return 2 * sizeof(float);
        case eGFXPlatformFormat_F32x3:
            return 3 * sizeof(float);
        case eGFXPlatformFormat_F32x4:
            return 4 * sizeof(float);
        case eGFXPlatformFormat_F16x2:
            return 4;
        case eGFXPlatformFormat_F16x4:
            return 8;
        case eGFXPlatformFormat_S32:
            return sizeof(int32_t);
        case eGFXPlatformFormat_U32:
            return sizeof(uint32_t);
        case eGFXPlatformFormat_S32x2:
            return 2 * sizeof(int32_t);
        case eGFXPlatformFormat_U32x2:
            return 2 * sizeof(uint32_t);
        case eGFXPlatformFormat_S32x3:
            return 3 * sizeof(int32_t);
        case eGFXPlatformFormat_U32x3:
            return 3 * sizeof(uint32_t);
        case eGFXPlatformFormat_S32x4:
            return 4 * sizeof(int32_t);
        case eGFXPlatformFormat_U32x4:
            return 4 * sizeof(uint32_t);
        case eGFXPlatformFormat_S16:
            return sizeof(int16_t);
        case eGFXPlatformFormat_U16:
            return sizeof(uint16_t);
        case eGFXPlatformFormat_S16x2:
            return 2 * sizeof(int16_t);
        case eGFXPlatformFormat_U16x2:
            return 2 * sizeof(uint16_t);
        case eGFXPlatformFormat_S16x4:
            return 4 * sizeof(int16_t);
        case eGFXPlatformFormat_U16x4:
            return 4 * sizeof(uint16_t);
        case eGFXPlatformFormat_SN16:
            return sizeof(int16_t);
        case eGFXPlatformFormat_UN16:
            return sizeof(uint16_t);
        case eGFXPlatformFormat_SN16x2:
            return 2 * sizeof(int16_t);
        case eGFXPlatformFormat_UN16x2:
            return 2 * sizeof(uint16_t);
        case eGFXPlatformFormat_SN16x4:
            return 4 * sizeof(int16_t);
        case eGFXPlatformFormat_UN16x4:
            return 4 * sizeof(uint16_t);
        case eGFXPlatformFormat_S8:
            return sizeof(int8_t);
        case eGFXPlatformFormat_U8:
            return sizeof(uint8_t);
        case eGFXPlatformFormat_S8x2:
            return 2 * sizeof(int8_t);
        case eGFXPlatformFormat_U8x2:
            return 2 * sizeof(uint8_t);
        case eGFXPlatformFormat_S8x4:
            return 4 * sizeof(int8_t);
        case eGFXPlatformFormat_U8x4:
            return 4 * sizeof(uint8_t);
        case eGFXPlatformFormat_SN8:
            return sizeof(int8_t);
        case eGFXPlatformFormat_UN8:
            return sizeof(uint8_t);
        case eGFXPlatformFormat_SN8x2:
            return 2 * sizeof(int8_t);
        case eGFXPlatformFormat_UN8x2:
            return 2 * sizeof(uint8_t);
        case eGFXPlatformFormat_SN8x4:
            return 4 * sizeof(int8_t);
        case eGFXPlatformFormat_UN8x4:
            return 4 * sizeof(uint8_t);
        case eGFXPlatformFormat_SN10_SN11_SN11:
            return sizeof(int32_t);
        case eGFXPlatformFormat_SN10x3_SN2:
            return sizeof(int32_t);
        case eGFXPlatformFormat_UN10x3_UN2:
            return sizeof(uint32_t);
        case eGFXPlatformFormat_D3DCOLOR:
        case eGFXPlatformFormat_Count:
        default:
            break;
        }
        return 0;
    }

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