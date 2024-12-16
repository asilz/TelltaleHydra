#pragma once

#include <tth/stream/stream.hpp>

struct EnumBase
{
  private:
    inline virtual int32_t Read_(Stream &stream) { return 0; }
    inline virtual int32_t Write_(Stream &stream) const { return 0; }

  public:
    virtual int32_t Read(Stream &stream) { return Read_(stream); }
    virtual int32_t Read(Stream &stream, bool blocked)
    {
        if (blocked)
        {
            int32_t err = stream.Seek(4, stream.CUR);
            if (err < 0)
            {
                return err;
            };
            return Read_(stream) + 4;
        }
        return Read_(stream);
    }
    virtual int32_t Write(Stream &stream) const { return Write_(stream); }
    virtual int32_t Write(Stream &stream, bool blocked) const
    {
        int32_t size = 0;
        if (blocked)
        {
            size += stream.Write(&size, sizeof(size));
        }
        size += Write_(stream);
        if (blocked)
        {
            int32_t err = stream.Seek(-size, stream.CUR);
            if (err < 0)
            {
                return err;
            }
            (void)stream.Write(&size, sizeof(size));
            err = stream.Seek(size - 4, stream.CUR);
            if (err < 0)
            {
                return err;
            }
        }
        return size;
    }
    static constexpr bool IS_BLOCKED = false;
};
