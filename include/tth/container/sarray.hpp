#pragma once

#include <tth/stream/stream.hpp>

namespace TTH
{

template <class T, size_t N> class SArray
{
  private:
    T data[N];

  public:
    static constexpr bool IS_BLOCKED = true;
    int32_t Read(Stream &stream) // TODO: is this wrong?
    {
        int32_t size = 0;
        for (size_t i = 0; i < N; ++i)
        {
            size += stream.Read(data[i], false);
        }
        return size;
    }
    int32_t Write(Stream &stream) const
    {
        int32_t size = 0;
        for (size_t i = 0; i < N; ++i)
        {
            size += stream.Write(data[i], false);
        }
        return size;
    }

    T &operator[](size_t index) { return data[index]; }
};
} // namespace TTH