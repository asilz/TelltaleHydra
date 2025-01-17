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

    static constexpr bool IS_BLOCKED = 1;
};
}; // namespace TTH