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
    static constexpr uint64_t GetTypeCRC64() { return CRC64_CaseInsensitive("T3Texture"); }
};
}; // namespace TTH