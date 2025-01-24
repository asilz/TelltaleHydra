#pragma once

#include <tth/stream/stream.hpp>

namespace TTH
{

template <class T> class TRange
{
  public:
    int32_t Read(Stream &stream)
    {
        int32_t size = 0;
        size += stream.Read(this->min, false);
        size += stream.Read(this->max, false);
        return size;
    }
    int32_t Write(Stream &stream) const
    {
        int32_t size = 0;
        size += stream.Write(this->min, false);
        size += stream.Write(this->max, false);
        return size;
    }

    T min;
    T max;

    static constexpr bool IS_BLOCKED = false;
};

} // namespace TTH