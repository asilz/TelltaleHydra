#pragma once

#include <inttypes.h>
#include <stddef.h>
#include <tth/crypto/crc64.hpp>
#include <tth/linalg/transform.hpp>

namespace TTH
{
class Skeleton
{
  private:
    class Impl;
    Impl *impl;

  public:
    int32_t Read(Stream &stream) noexcept;
    int32_t Write(Stream &stream) const noexcept;

    /**
     * @brief Retrieves the local position of the bone with index @p boneIndex
     *
     * @param boneIndex index of the bone
     * @return constant position vector pointer, nullptr if index out of range
     */
    const Vector3 *GetBoneLocalPosition(size_t boneIndex) const noexcept;

    /**
     * @brief Retrieves the local rotation of the bone with index @p boneIndex
     *
     * @param boneIndex index of the bone
     * @return constant rotation quaternion pointer, nullptr if index out of range
     */
    const Quaternion *GetBoneLocalRotation(size_t boneIndex) const noexcept;

    /**
     * @brief Retrieves the index of the parent of the bone with index @p boneIndex
     *
     * @param boneIndex index of the bone
     * @return positive bone index if bone has a parent, otherwise -1
     */
    int32_t GetBoneParentIndex(size_t boneIndex) const noexcept;

    /**
     * @brief Retrieves a symbol containing a hash of the bone name with index @p boneIndex
     *
     * @param boneIndex index of the bone
     * @return Symbol with a name hash
     */
    Symbol GetBoneCRC64(size_t boneIndex) const noexcept;

    /**
     * @brief Retrieves the number of bones in the skeleton
     *
     * @return bone count
     */
    size_t GetBoneCount() const noexcept;

    /**
     * @brief Retrieves the version CRC32 of the animation
     *
     * @return CRC32
     */
    uint32_t GetVersionCRC32() const noexcept;

    /**
     * @brief Retrieves the type CRC64 of this datatype
     *
     * @return CRC64
     */
    static constexpr uint64_t GetTypeCRC64() { return CRC64_CaseInsensitive("Skeleton"); }

    static constexpr bool IS_BLOCKED = true;

    errno_t Create();
    void Destroy();
};
}; // namespace TTH