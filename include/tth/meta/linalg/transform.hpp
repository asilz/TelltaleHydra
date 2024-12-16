#pragma once

#include <tth/meta/linalg/quaternion.hpp>
#include <tth/meta/linalg/vector.hpp>

class Transform
{
  private:
    inline int32_t Read_(Stream &stream)
    {
        int32_t size = 0;
        int32_t err;
        err = this->mRot.Read(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = this->mTrans.Read(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        return size;
    }
    inline int32_t Write_(Stream &stream) const
    {
        int32_t size = 0;
        int32_t err;
        err = this->mRot.Write(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = this->mTrans.Write(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        return size;
    }

  public:
    int32_t Read(Stream &stream)
    {
        int32_t err = stream.Seek(4, stream.CUR);
        if (err < 0)
        {
            return err;
        }
        return Read_(stream) + 4;
    }
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
    int32_t Write(Stream &stream) const
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
    class Quaternion mRot;
    class Vector3 mTrans;
    static constexpr bool IS_BLOCKED = true;
};