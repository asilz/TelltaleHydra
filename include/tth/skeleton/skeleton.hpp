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
    int32_t Read(Stream &stream);
    int32_t Write(Stream &stream) const;

    const Vector3 *GetBoneLocalPosition(size_t boneIndex) const;
    const Quaternion *GetBoneLocalRotation(size_t boneIndex) const;
    size_t GetBoneParentIndex(size_t boneIndex) const;
    Symbol GetBoneCRC64(size_t boneIndex) const;

        /**
     * @brief Retrieves the version CRC32 of the animation
     *
     * @return CRC32
     */
    uint32_t GetVersionCRC32() const;

    /**
     * @brief Retrieves the type CRC64 of this datatype
     *
     * @return CRC64
     */
    constexpr uint64_t GetTypeCRC64() const { return CRC64_CaseInsensitive("Skeleton"); }

    static constexpr bool IS_BLOCKED = true;

    Skeleton();
    ~Skeleton();
};
}; // namespace TTH