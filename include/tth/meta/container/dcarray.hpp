#pragma once

#include <tth/stream/object.hpp>
#include <tth/stream/stream.hpp>
#include <vector>

template <class T> class DCArray : private std::vector<T>
{
  public:
    using std::vector<T>::vector;
    static constexpr bool IS_BLOCKED = true;
    uint32_t Read(Stream &stream, bool blocked)
    {
        if (blocked)
        {
            stream.Seek(4, stream.CUR);
        }
        uint32_t count;
        uint32_t size = stream.Read(&count, sizeof(count));
        this->resize(count);
        for (auto &i : *this)
        {
            size += ReadObject<T>(i, stream);
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
        this->resize(count);
        for (auto &i : *this)
        {
            size += ReadObject<T>(i, stream);
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
            size += WriteObject<T>(i, stream);
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
        for (auto const &i : *this)
        {
            size += WriteObject<T>(i, stream);
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

template <class T> using DArray = DCArray<T>;
