#pragma once

#include <tth/crypto/crc64.hpp>
#include <tth/enum.hpp>
#include <tth/stream/stream.hpp>
#include <tth/texture/color.hpp>

namespace TTH
{
struct RenderSwizzleParams
{
  public:
    int32_t Read(Stream &stream) { return stream.Read(static_cast<void *>(mSwizzle), sizeof(mSwizzle)); }
    int32_t Write(Stream &stream) const { return stream.Write(static_cast<const void *>(mSwizzle), sizeof(mSwizzle)); }
    uint8_t mSwizzle[4];
    static constexpr bool IS_BLOCKED = true;
    static constexpr uint64_t GetTypeCRC64() { return CRC64_CaseInsensitive("RenderSwizzleParams"); }
};
class T3SamplerStateBlock
{
  public:
    int32_t Read(Stream &stream) { return stream.Read(mData); }
    int32_t Write(Stream &stream) const { return stream.Write(mData); }
    uint32_t mData;
    static constexpr bool IS_BLOCKED = true;
    static constexpr uint64_t GetTypeCRC64() { return CRC64_CaseInsensitive("T3SamplerStateBlock"); }
};
class T3ToonGradientRegion
{
  public:
    int32_t Read(Stream &stream)
    {
        int32_t size = 0;
        int32_t err;
        err = stream.Read(mColor);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Read(mSize);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Read(mGradientSize);
        if (err < 0)
        {
            return err;
        }
        size += err;
        return size;
    }
    int32_t Write(Stream &stream) const
    {
        int32_t size = 0;
        int32_t err;
        err = stream.Write(mColor);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Write(mSize);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Write(mGradientSize);
        if (err < 0)
        {
            return err;
        }
        size += err;
        return size;
    }
    Color mColor;
    float mSize;
    float mGradientSize;
    static constexpr bool IS_BLOCKED = false;
    static constexpr uint64_t GetTypeCRC64() { return CRC64_CaseInsensitive("T3ToonGradientRegion"); }
};
}; // namespace TTH