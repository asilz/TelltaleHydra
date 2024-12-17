#pragma once

#include <map>
#include <tth/stream/object.hpp>
#include <tth/stream/stream.hpp>

template <class Key, class Value, class Compare = std ::less<Key>> class Map : private std::map<Key, Value, Compare>
{

  public:
    using std::map<Key, Value, Compare>::map;
    static constexpr bool IS_BLOCKED = true;
    uint32_t Read(Stream &stream, bool blocked)
    {
        if (blocked)
        {
            stream.Seek(4, stream.CUR);
        }
        uint32_t count;
        uint32_t size = stream.Read(&count, sizeof(count));
        while (count--)
        {
            std::pair<Key, Value> kv;
            size += ReadObject<Key>(kv.first, stream, false);
            size += ReadObject<Value>(kv.second, stream, false);
            this->insert(kv);
        }
        return size;
    }

    uint32_t Read(Stream &stream)
    {
        if constexpr (IS_BLOCKED)
        {
            stream.Seek(4, stream.CUR);
        }
        uint32_t count;
        uint32_t size = stream.Read(&count, sizeof(count));
        while (count--)
        {
            std::pair<Key, Value> kv;
            size += ReadObject<Key>(kv.first, stream, false);
            size += ReadObject<Value>(kv.second, stream, false);
            this->insert(kv);
        }
        return size;
    }

    uint32_t Write(Stream &stream, bool blocked) const
    {
        uint32_t size = 0;
        if (blocked)
        {
            size += stream.Write(&size, sizeof(size));
        }
        uint32_t count = this->size();
        size += stream.Write(&count, sizeof(count));
        for (auto const &[key, val] : *this)
        {
            size += WriteObject<Key>(key, stream, false);
            size += WriteObject<Value>(val, stream, false);
        }

        if (blocked)
        {
            stream.Seek(-size, stream.CUR);
            stream.Write(&size, sizeof(size));
            stream.Seek(size - 4, stream.CUR);
        }
        return size;
    }

    uint32_t Write(Stream &stream) const
    {
        uint32_t size = 0;
        if constexpr (IS_BLOCKED)
        {
            size += stream.Write(&size, sizeof(size));
        }
        uint32_t count = this->size();
        size += stream.Write(&count, sizeof(count));
        for (auto const &[key, val] : *this)
        {
            size += WriteObject<Key>(key, stream, false);
            size += WriteObject<Value>(val, stream, false);
        }

        if constexpr (IS_BLOCKED)
        {
            stream.Seek(-size, stream.CUR);
            stream.Write(&size, sizeof(size));
            stream.Seek(size - 4, stream.CUR);
        }
        return size;
    }
};