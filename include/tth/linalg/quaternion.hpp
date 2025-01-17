#pragma once

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

    static constexpr bool IS_BLOCKED = 0;
};
}; // namespace TTH