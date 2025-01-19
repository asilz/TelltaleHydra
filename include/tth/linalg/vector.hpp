#pragma once

#include <tth/stream/stream.hpp>

namespace TTH
{
class Vector3
{
  public:
    float x;
    float y;
    float z;

    int32_t Read(Stream &stream);
    int32_t Write(Stream &stream) const;

    static constexpr bool IS_BLOCKED = false;
};
}; // namespace TTH