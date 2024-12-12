#pragma once

#include <tth/stream/stream.hpp>
#include <vector>

template <class T> class DCArray : public std::vector<T>
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
        this->resize(count);
        for (uint32_t i = 0; i < count; ++i)
        {
            size += this[i].Read(stream, false);
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
        for (auto const &i : *this)
        {
            size += i.Write(stream, false);
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
