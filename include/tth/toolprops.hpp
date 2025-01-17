#pragma once

#include <tth/stream/stream.hpp>

namespace TTH
{

class ToolProps
{
  public:
    bool mbHasProps;

    int32_t Read(Stream &stream) { return stream.Read(mbHasProps); }
    int32_t Write(Stream &stream) const { return stream.Write(mbHasProps); }

    ToolProps(bool hasProps) : mbHasProps(hasProps) {}

    static constexpr bool IS_BLOCKED = false;
};
}; // namespace TTH