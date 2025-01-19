#pragma once

#include <tth/stream/stream.hpp>

namespace TTH
{

class Flags
{
  public:
    uint32_t mFlags;

    int32_t Read(Stream &stream) { return stream.Read(mFlags); }
    int32_t Write(Stream &stream) const { return stream.Write(mFlags); }

    Flags(uint32_t flags) : mFlags(flags) {}
    Flags() : mFlags(0) {}

    static constexpr bool IS_BLOCKED = false;
};
}; // namespace TTH