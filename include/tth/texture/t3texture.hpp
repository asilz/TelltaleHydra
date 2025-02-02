#pragma once

#include <tth/crypto/crc64.hpp>
#include <tth/stream/stream.hpp>

namespace TTH
{
class T3Texture
{
  private:
    class Impl;
    Impl *impl;

  public:
    int32_t Read(Stream &stream);
    int32_t Write(Stream &stream) const;

    static constexpr uint64_t GetTypeCRC64() { return CRC64_CaseInsensitive("T3Texture"); }
    static constexpr bool IS_BLOCKED = true;
};
}; // namespace TTH