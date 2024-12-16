#pragma once

#include <tth/meta/crc64/symbol.hpp>

class HandleBase
{
  private:
    inline virtual int32_t Read_(Stream &stream)
    {
        int32_t err = symbol.Read(stream);
        if (err < 0)
        {
            return err;
        }
        return err + stream.Read(&this->a8, sizeof(this->a8));
    }
    inline virtual int32_t Write_(Stream &stream) const
    {
        int32_t err = symbol.Write(stream);
        if (err < 0)
        {
            return err;
        }
        return err + stream.Write(&this->a8, sizeof(this->a8));
    }

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
    Symbol symbol;
    int64_t a8;
    static constexpr bool IS_BLOCKED = false;
};

template <class T> class Handle : public HandleBase
{
  private:
    virtual inline int32_t Read_(Stream &stream) { return symbol.Read(stream); }
    virtual inline int32_t Write_(Stream &stream) const { return symbol.Write(stream); }

  public:
    virtual int32_t Read(Stream &stream)
    {
        int32_t err = stream.Seek(4, stream.CUR);
        if (err < 0)
        {
            return err;
        }
        return Read_(stream) + 4;
    }
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
    virtual int32_t Write(Stream &stream) const
    {
        int32_t size = 0;
        size += stream.Write(&size, sizeof(size));
        size += Write_(stream);
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
        return size;
    }
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
    static constexpr bool IS_BLOCKED = true;
};