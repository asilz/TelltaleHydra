#pragma once

#include <tth/stream/stream.hpp>

class Symbol
{
  private:
    inline int32_t Read_(Stream &stream) { return stream.Read(&this->mCrc64, sizeof(this->mCrc64)); }
    inline int32_t Write_(Stream &stream) const { return stream.Write(&this->mCrc64, sizeof(this->mCrc64)); }

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
    bool operator<(const Symbol &rhs) const { return mCrc64 < rhs.mCrc64; }
    uint64_t mCrc64;
    static constexpr bool IS_BLOCKED = false;
};