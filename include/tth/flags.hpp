#pragma once

#include <tth/crypto/crc64.hpp>
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

    static constexpr uint64_t GetTypeCRC64() { return CRC64_CaseInsensitive("Flags"); }
    static constexpr bool IS_BLOCKED = false;
};

template <size_t N> class BitSetBase
{
  public:
    int32_t Read(Stream &stream) { return stream.Read((void *)(mWords), sizeof(mWords)); }
    int32_t Write(Stream &stream) const { return stream.Write((const void *)(mWords), sizeof(mWords)); }
    uint32_t mWords[N];
    static constexpr bool IS_BLOCKED = true;
};
}; // namespace TTH