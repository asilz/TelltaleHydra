#pragma once

#include <tth/crypto/crc64.hpp>
#include <tth/stream/stream.hpp>

namespace TTH
{
struct EnumBase
{
  public:
    int32_t Read(Stream &stream) { return 0; }
    int32_t Write(Stream &stream) const { return 0; }
    static constexpr bool IS_BLOCKED = false;
    static constexpr uint64_t GetTypeCRC64() { return CRC64_CaseInsensitive("EnumBase"); }
};

struct EnumT3MaterialLightModelType : public EnumBase
{
  public:
    int32_t Read(Stream &stream)
    {
        int32_t size = 0;
        int32_t err;
        err = stream.Read(mVal);
        if (err < 0)
        {
            return err;
        }
        size += err;
        EnumBase *interface0 = this;
        err = stream.ReadBase(*interface0);
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
        err = stream.Write(mVal);
        if (err < 0)
        {
            return err;
        }
        size += err;
        const EnumBase *interface0 = this;
        err = stream.WriteBase(*interface0);
        if (err < 0)
        {
            return err;
        }
        size += err;
        return size;
    }
    int32_t mVal;
    static constexpr bool IS_BLOCKED = true;
    static constexpr uint64_t GetTypeCRC64() { return CRC64_CaseInsensitive("EnumT3MaterialLightModelType"); }
};
}; // namespace TTH