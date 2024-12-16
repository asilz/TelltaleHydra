#pragma once

#include <tth/stream/stream.hpp>

class Color
{
  private:
    inline int32_t Read_(Stream &stream)
    {
        int32_t size = stream.Read(&this->r, sizeof(this->r));
        size += stream.Read(&this->g, sizeof(this->g));
        size += stream.Read(&this->b, sizeof(this->b));
        size += stream.Read(&this->a, sizeof(this->a));
        return size;
    }
    inline int32_t Write_(Stream &stream) const
    {
        int32_t size = stream.Write(&this->r, sizeof(this->r));
        size += stream.Write(&this->g, sizeof(this->g));
        size += stream.Write(&this->b, sizeof(this->b));
        size += stream.Write(&this->a, sizeof(this->a));
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
    float r;
    float g;
    float b;
    float a;
    static constexpr bool IS_BLOCKED = false;
};

class T3ToonGradientRegion
{
  private:
    inline virtual int32_t Read_(Stream &stream)
    {
        int32_t size = 0;
        int32_t err;
        err = this->mColor.Read(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        size += stream.Read(&this->mSize, sizeof(this->mSize));
        size += stream.Read(&this->mGradientSize, sizeof(this->mGradientSize));
        return size;
    }
    inline virtual int32_t Write_(Stream &stream) const
    {
        int32_t size = 0;
        int32_t err;
        err = this->mColor.Write(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        size += stream.Write(&this->mSize, sizeof(this->mSize));
        size += stream.Write(&this->mGradientSize, sizeof(this->mGradientSize));
        return size;
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
    class Color mColor;
    float mSize;
    float mGradientSize;
    static constexpr bool IS_BLOCKED = false;
};