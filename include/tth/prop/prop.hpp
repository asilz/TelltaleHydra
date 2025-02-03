#pragma once

#include <tth/crypto/crc64.hpp>
#include <tth/stream/stream.hpp>

namespace TTH
{
class PropertySet
{
  private:
    class Impl;
    Impl *impl;

  public:
    int32_t Read(Stream &stream) noexcept;
    int32_t Write(Stream &stream) const noexcept;

    errno_t Create();
    void Destroy();

    static constexpr uint64_t GetTypeCRC64() { return CRC64_CaseInsensitive("PropertySet"); }
    static constexpr bool IS_BLOCKED = true;
};
}; // namespace TTH