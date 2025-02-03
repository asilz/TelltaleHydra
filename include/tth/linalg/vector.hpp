#pragma once

#include <tth/crypto/crc64.hpp>
#include <tth/stream/stream.hpp>

namespace TTH
{
class Vector4
{
  public:
    float x;
    float y;
    float z;
    float w;

    int32_t Read(Stream &stream);
    int32_t Write(Stream &stream) const;

    static constexpr uint64_t GetTypeCRC64() { return CRC64_CaseInsensitive("Vector4"); }
    static constexpr bool IS_BLOCKED = false;
};
class Vector3
{
  public:
    float x;
    float y;
    float z;

    int32_t Read(Stream &stream);
    int32_t Write(Stream &stream) const;

    static constexpr uint64_t GetTypeCRC64() { return CRC64_CaseInsensitive("Vector3"); }
    static constexpr bool IS_BLOCKED = false;
};
class Vector2
{
  public:
    float x;
    float y;

    int32_t Read(Stream &stream);
    int32_t Write(Stream &stream) const;

    static constexpr uint64_t GetTypeCRC64() { return CRC64_CaseInsensitive("Vector2"); }
    static constexpr bool IS_BLOCKED = false;
};
}; // namespace TTH