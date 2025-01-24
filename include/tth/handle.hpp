#pragma once

#include <tth/crypto/crc64.hpp>
#include <tth/stream/stream.hpp>

namespace TTH
{

class HandleBase
{
  public:
    virtual int32_t Read(Stream &stream)
    {
        int32_t size = 0;
        int32_t err = stream.Read(symbol);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Read(a8);
        if (err < 0)
        {
            return err;
        }
        size += err;

        return size;
    }
    virtual int32_t Write(Stream &stream) const
    {
        int32_t size = 0;
        int32_t err = stream.Write(symbol);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Write(a8);
        if (err < 0)
        {
            return err;
        }
        size += err;

        return size;
    }

    virtual ~HandleBase() {};

    Symbol symbol;
    int64_t a8;

    static constexpr uint64_t GetTypeCRC64() { return CRC64_CaseInsensitive("HandleBase"); }
    static constexpr bool IS_BLOCKED = false;
};

template <class T> class Handle : public HandleBase
{
  public:
    int32_t Read(Stream &stream) { return stream.Read(symbol); }
    int32_t Write(Stream &stream) const { return stream.Write(symbol); }

    virtual ~Handle() {}

    static constexpr bool IS_BLOCKED = true;
};
} // namespace TTH