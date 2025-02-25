#pragma once

#include <set>
#include <tth/stream/stream.hpp>

namespace TTH
{

template <class Key, class Compare> class Set : public std::set<Key, Compare>
{

  public:
    using std::set<Key, Compare>::set;
    static constexpr bool IS_BLOCKED = true;
    int32_t Read(Stream &stream)
    {
        uint32_t count;
        int32_t size = stream.Read(count);
        while (count--)
        {
            Key key;
            size += stream.Read<Key>(key, false);
            this->insert(key);
        }
        return size;
    }

    int32_t Write(Stream &stream) const
    {
        uint32_t count = this->size();
        int32_t size = stream.Write(count);
        for (auto const &i : *this)
        {
            size += stream.Write<Key>(i, false);
        }
        return size;
    }
};

} // namespace TTH