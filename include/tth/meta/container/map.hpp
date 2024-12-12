#pragma once

#include <map>
#include <tth/stream/stream.hpp>

template <class Key, class Value, class Compare> class Map : public std::map<Key, Value, Compare>
{
  public:
    static constexpr bool IS_BLOCKED = true;
    uint32_t Read(Stream &stream, bool blocked = IS_BLOCKED)
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
            size += kv.first.Read(stream, false);
            size += kv.second.Read(stream, false);
            this->insert(kv);
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
        uint32_t count = this->size();
        size += stream.Write(&count, sizeof(count));
        for (auto const &[key, val] : *this)
        {
            size += key.Write(stream);
            size += val.Write(stream);
        }

        if (blocked)
        {
            stream.Seek(-size, stream.CUR);
            stream.Write(&size, sizeof(size));
            stream.Seek(size - 4, stream.CUR);
        }
        return size;
    }
};