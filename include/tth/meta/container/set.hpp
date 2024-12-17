#pragma once

#include <set>
#include <tth/stream/stream.hpp>

namespace TTH
{

template <class Key, class Compare> class Set : private std::set<Key, Compare>
{

  public:
    using std::set<Key, Compare>::set;
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
            Key key;
            size += ReadObject<Key>(key, stream, false);
            this->insert(key);
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
            Key key;
            size += ReadObject<Key>(key, stream, false);
            this->insert(key);
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
        for (auto const &i : *this)
        {
            size += WriteObject<Key>(i, stream, false);
        }
        if (blocked)
        {
            stream.Seek(-size, stream.CUR);
            (void)stream.Write(&size, sizeof(size));
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
        for (auto const &i : *this)
        {
            size += WriteObject<Key>(i, stream, false);
        }
        if constexpr (IS_BLOCKED)
        {
            stream.Seek(-size, stream.CUR);
            (void)stream.Write(&size, sizeof(size));
            stream.Seek(size - 4, stream.CUR);
        }
        return size;
    }
};

} // namespace TTH