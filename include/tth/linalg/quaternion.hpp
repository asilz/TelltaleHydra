#pragma once

#include <tth/crypto/crc64.hpp>
#include <tth/stream/stream.hpp>

namespace TTH
{
class Quaternion
{
  public:
    float x;
    float y;
    float z;
    float w;

    int32_t Read(Stream &stream);
    int32_t Write(Stream &stream) const;

    Quaternion operator*(const Quaternion &t) const
    {
        return Quaternion{w * t.x + x * t.w + y * t.z - z * t.y, w * t.y + y * t.w + z * t.x - x * t.z, w * t.z + z * t.w + x * t.y - y * t.x, w * t.w - x * t.x - y * t.y - z * t.z};
    }

    static constexpr uint64_t GetTypeCRC64() { return CRC64_CaseInsensitive("Quaternion"); }
    static constexpr bool IS_BLOCKED = false;
};
}; // namespace TTH