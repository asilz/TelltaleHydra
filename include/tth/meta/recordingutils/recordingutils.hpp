#pragma once

#include <tth/meta/enum/enumbase.hpp>

namespace TTH
{

namespace RecordingUtils
{

struct EnumRecordingStatus : public EnumBase
{
  private:
    inline virtual int32_t Read_(Stream &stream)
    {
        int32_t size = 0;
        int32_t err;
        size += stream.Read(&this->mVal, sizeof(this->mVal));
        err = EnumBase::Read(stream, true);
        if (err < 0)
        {
            return err;
        }
        size += err;
        return size;
    }
    inline virtual int32_t Write_(Stream &stream) const
    {
        int32_t size = 0;
        int32_t err;
        size += stream.Write(&this->mVal, sizeof(this->mVal));
        err = EnumBase::Read(stream, true);
        if (err < 0)
        {
            return err;
        }
        size += err;
        return size;
    }

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
    int32_t mVal;
    static constexpr bool IS_BLOCKED = true;
};
}; // namespace RecordingUtils

} // namespace TTH