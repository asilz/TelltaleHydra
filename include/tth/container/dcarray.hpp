#pragma once

#include <tth/stream/stream.hpp>
#include <vector>

namespace TTH
{

template <class T> class DCArray : public std::vector<T>
{
  public:
    using std::vector<T>::vector;
    int32_t Read(Stream &stream)
    {
        uint32_t count;
        uint32_t size = stream.Read(count);
        this->resize(count);
        for (auto &i : *this)
        {
            size += stream.Read(i, false);
        }

        return size;
    }

    int32_t Write(Stream &stream) const
    {

        uint32_t count = this->size();
        int32_t size = stream.Write(count);
        for (auto const &i : *this)
        {
            size += stream.Write(i, false);
        }
        return size;
    }

    static constexpr bool IS_BLOCKED = true;
};
}; // namespace TTH