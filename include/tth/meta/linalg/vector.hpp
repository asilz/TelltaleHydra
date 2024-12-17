#pragma once

#include <tth/stream/stream.hpp>

namespace TTH
{

class Vector4
{
  private:
    inline int32_t Read_(Stream &stream)
    {
        int32_t size = stream.Read(&this->x, sizeof(this->x));
        size += stream.Read(&this->y, sizeof(this->y));
        size += stream.Read(&this->z, sizeof(this->z));
        size += stream.Read(&this->w, sizeof(this->w));
        return size;
    }
    inline int32_t Write_(Stream &stream) const
    {
        int32_t size = stream.Write(&this->x, sizeof(this->x));
        size += stream.Write(&this->y, sizeof(this->y));
        size += stream.Write(&this->z, sizeof(this->z));
        size += stream.Write(&this->w, sizeof(this->w));
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
    float x;
    float y;
    float z;
    float w;
    static constexpr bool IS_BLOCKED = false;
};

class Vector3
{
  private:
    inline int32_t Read_(Stream &stream)
    {
        int32_t size = 0;
        size += stream.Read(&this->x, sizeof(this->x));
        size += stream.Read(&this->y, sizeof(this->y));
        size += stream.Read(&this->z, sizeof(this->z));
        return size;
    }
    inline int32_t Write_(Stream &stream) const
    {
        int32_t size = 0;
        size += stream.Write(&this->x, sizeof(this->x));
        size += stream.Write(&this->y, sizeof(this->y));
        size += stream.Write(&this->z, sizeof(this->z));
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
    float x;
    float y;
    float z;
    static constexpr bool IS_BLOCKED = false;
};

class Vector2
{
  private:
    inline int32_t Read_(Stream &stream)
    {
        int32_t size = 0;
        size += stream.Read(&this->x, sizeof(this->x));
        size += stream.Read(&this->y, sizeof(this->y));
        return size;
    }
    inline int32_t Write_(Stream &stream) const
    {
        int32_t size = 0;
        size += stream.Write(&this->x, sizeof(this->x));
        size += stream.Write(&this->y, sizeof(this->y));
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
    float x;
    float y;
    static constexpr bool IS_BLOCKED = false;
};

} // namespace TTH
