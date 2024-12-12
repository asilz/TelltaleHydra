#pragma once

#include <tth/stream/stream.hpp>

template <class T, size_t N> class SArray
{
  private:
    T data[N];

  public:
    static constexpr bool IS_BLOCKED = true;
    uint32_t Read(Stream &stream, bool blocked = IS_BLOCKED)
    {
        if (blocked)
        {
            stream.Seek(4, stream.CUR);
        }
        uint32_t size = 0;
        for (size_t i = 0; i < N; ++i)
        {
            size += data[i].Read(stream, false);
        }

        return size;
    }
    uint32_t Write(Stream &stream, bool blocked = IS_BLOCKED) const
    {
        uint32_t size = 0;
        if (blocked)
        {
            size += stream.Write(&size, sizeof(size));
        }
        for (size_t i = 0; i < N; ++i)
        {
            size += data[i].Write(stream, false);
        }
        if (blocked)
        {
            stream.Seek(-size, stream.CUR);
            stream.Write(&size, sizeof(size));
            stream.Seek(size - 4, stream.CUR);
        }
        return size;
    }

    T &operator[](size_t index) { return data[index]; }
};