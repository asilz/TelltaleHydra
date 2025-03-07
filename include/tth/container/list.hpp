#pragma once

#include <list>
#include <tth/stream/stream.hpp>

namespace TTH
{

template <class T> class DCArray : public std::list<T>
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
            size += stream.Read<T>(i, false);
        }

        return size;
    }

    int32_t Write(Stream &stream) const
    {

        uint32_t count = this->size();
        int32_t size = stream.Write(count);
        for (auto const &i : *this)
        {
            size += stream.Write<T>(i, false);
        }
        return size;
    }

    static constexpr bool IS_BLOCKED = true;
};
}; // namespace TTH