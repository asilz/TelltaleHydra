#pragma once

#include <tth/stream/object.hpp>

template <class T> class TRange
{
  private:
    inline int32_t Read_(Stream &stream)
    {
        int32_t size = 0;
        size += ReadObject<T>(this->min, stream, false);
        size += ReadObject<T>(this->max, stream, false);
        return size;
    }
    inline int32_t Write_(Stream &stream) const
    {
        int32_t size = 0;
        size += WriteObject<T>(this->min, stream, false);
        size += WriteObject<T>(this->max, stream, false);
        return size;
    }

  public:
    int32_t Read(Stream &stream) { return Read_(stream); }
    int32_t Read(Stream &stream, bool blocked)
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
    int32_t Write(Stream &stream) const { return Write_(stream); }
    int32_t Write(Stream &stream, bool blocked) const
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
    T min;
    T max;
    static constexpr bool IS_BLOCKED = false;
};