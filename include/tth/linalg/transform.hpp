#pragma once

#include <tth/linalg/quaternion.hpp>
#include <tth/linalg/vector.hpp>

namespace TTH
{
class Transform
{
  public:
    Quaternion mRot;
    Vector3 mTrans;

    int32_t Read(Stream &stream);
    int32_t Write(Stream &stream) const;

    static constexpr uint64_t GetTypeCRC64(uint64_t crc = 0) { return CRC64_CaseInsensitive("Transform", crc); }
    static constexpr bool IS_BLOCKED = true;
};
}; // namespace TTH