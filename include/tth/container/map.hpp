#pragma once

#include <map>
#include <tth/stream/stream.hpp>

namespace TTH
{

template <class Key, class Value, class Compare = std ::less<Key>> class Map : public std::map<Key, Value, Compare>
{

  public:
    using std::map<Key, Value, Compare>::map;
    static constexpr bool IS_BLOCKED = true;

    int32_t Read(Stream &stream)
    {
        uint32_t count;
        uint32_t size = stream.Read(count);
        while (count--)
        {
            std::pair<Key, Value> kv;
            size += stream.Read<Key>(kv.first, false);
            size += stream.Read<Value>(kv.second, false);
            this->insert(kv);
        }
        return size;
    }

    int32_t Write(Stream &stream) const
    {
        uint32_t count = this->size();
        int32_t size = stream.Write(count);
        for (auto const &[key, val] : *this)
        {
            size += stream.Write<Key>(key, false);
            size += stream.Write<Value>(val, false);
        }
        return size;
    }
};
} // namespace TTH