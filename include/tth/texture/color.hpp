#pragma once

#include <tth/crypto/crc64.hpp>
#include <tth/stream/stream.hpp>

namespace TTH
{
class Color
{
  public:
    float r;
    float g;
    float b;
    float a;

    int32_t Read(Stream &stream)
    {
        int32_t size = stream.Read(r);
        size += stream.Read(g);
        size += stream.Read(b);
        size += stream.Read(a);
        return size;
    }
    int32_t Write(Stream &stream) const
    {
        int32_t size = stream.Write(r);
        size += stream.Write(g);
        size += stream.Write(b);
        size += stream.Write(a);
        return size;
    }

    static constexpr uint64_t GetTypeCRC64() { return CRC64_CaseInsensitive("Color"); }
    static constexpr bool IS_BLOCKED = false;
};
}; // namespace TTH