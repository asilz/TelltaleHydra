#pragma once

#include <tth/stream/stream.hpp>
#include <type_traits>

template <class T> inline uint32_t WriteObject(const T &object, Stream &stream)
{
    if constexpr (std::is_class<T>())
    {
        return object.Write(stream, false);
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
        return object.Read(stream, false);
    }
    else
    {
        return stream.Read(&object, sizeof(object));
    }
}