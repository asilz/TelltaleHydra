#pragma once

#include <stddef.h>
#include <tth/animation/keyframe.hpp>
#include <tth/core/errno.hpp>
#include <tth/crypto/crc64.hpp>
#include <tth/linalg/transform.hpp>
#include <tth/stream/stream.hpp>

namespace TTH
{

class Animation
{
  private:
    class Impl;
    Impl *impl;

  public:
    int32_t Read(Stream &stream);
    int32_t Write(Stream &stream) const;

    /**
     * @brief Retrieves the duration of the animation
     *
     * @return duration of the animation
     */
    float GetDuration() const;

    /**
     * @brief Retrieves the number of frames for a specific bone
     *
     * @param boneCRC hash that indicates the bone to retrieve the keyframe count for
     * @return Keyframe count
     */
    size_t GetKeyframeCount(Symbol boneCRC) const;

    /**
     * @brief Retrieves the number of bones that the animation affects
     *
     * @return Bone count
     */
    size_t GetBoneCount() const;

    /**
     * @brief Retrieves the CRC64 of all the bones in the animation and stores them in @p output
     *
     * @param output array with a capacity to store the crc64 of all the bones in the animation
     * @return Bone count
     */
    const Symbol *GetBonesCRC64() const;

    /**
     * @brief Retrieves the keyframes of a specific bone
     *
     * @param output array with size equal to the bone count that will be filled keyframes
     * @return 0 on success, negative error code on failure
     */
    errno_t GetKeyframes(KeyframedValue<Transform> *output) const;

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
    constexpr uint64_t GetTypeCRC64() const { return CRC64_CaseInsensitive("Animation"); }

    Animation();
    ~Animation();

    static constexpr bool IS_BLOCKED = true;
};

}; // namespace TTH