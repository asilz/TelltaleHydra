#pragma once

#include <tth/stream/stream.hpp>
#include <type_traits>

template <class T> inline uint32_t WriteObject(const T &object, Stream &stream, bool blocked)
{
    if constexpr (std::is_class<T>())
    {
        return object.Write(stream, blocked);
    }
    else
    {
        return stream.Write(&object, sizeof(object));
    }
}
template <class T> inline uint32_t ReadObject(T &object, Stream &stream, bool blocked)
{
    if constexpr (std::is_class<T>())
    {
        return object.Read(stream, blocked);
    }
    else
    {
        return stream.Read(&object, sizeof(object));
    }
}

template <class T> inline uint32_t WriteObject(const T &object, Stream &stream)
{
    if constexpr (std::is_class<T>())
    {
        return object.Write(stream);
    }
    else
    {
        return stream.Write(&object, sizeof(object));
    }
}

template <class T> inline uint32_t ReadObject(T &object, Stream &stream)
{
    if constexpr (std::is_class<T>())
    {
        return object.Read(stream);
    }
    else
    {
        return stream.Read(&object, sizeof(object));
    }
}
