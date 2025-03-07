#pragma once

#include <cstdio>
#include <tth/core/errno.hpp>
#include <type_traits>

namespace TTH
{

/* Stream wrapper */
class Stream
{
  private:
    FILE *stream;

  public:
    static constexpr int SET = 0;
    static constexpr int CUR = 1;
    static constexpr int END = 2;

    errno_t SeekMetaHeaderEnd(); // TODO: Remove this and implement channel thing

    uint32_t Read(void *buf, size_t size);
    uint32_t Write(const void *buf, size_t size);

    template <class T> int32_t ReadBase(T &obj)
    {
        if constexpr (std::is_class<T>())
        {
            if constexpr (T::IS_BLOCKED)
            {
                Seek(4, CUR);
            }
            return obj.T::Read(*this);
        }

        return Read(static_cast<void *>(&obj), sizeof(obj));
    }

    template <class T> int32_t WriteBase(const T &obj)
    {
        if constexpr (std::is_class<T>())
        {
            int32_t size = 0;
            if constexpr (T::IS_BLOCKED)
            {
                size += Write(size);
            }
            int32_t err = obj.T::Write(*this);
            if (err < 0)
            {
                return err;
            }
            size += err;

            if constexpr (T::IS_BLOCKED)
            {
                Seek(-size, CUR);
                Write(size);
                Seek(size - 4, CUR);
            }
            return size;
        }
        return Write(static_cast<const void *>(&obj), sizeof(obj));
    }

    template <class T> int32_t Read(T &obj)
    {
        if constexpr (std::is_class<T>())
        {
            if constexpr (T::IS_BLOCKED)
            {
                Seek(4, CUR);
            }
            return obj.Read(*this);
        }

        return Read(static_cast<void *>(&obj), sizeof(obj));
    }

    template <class T> int32_t Write(const T &obj)
    {
        if constexpr (std::is_class<T>())
        {
            int32_t size = 0;
            if constexpr (T::IS_BLOCKED)
            {
                size += Write(size);
            }
            int32_t err = obj.Write(*this);
            if (err < 0)
            {
                return err;
            }
            size += err;

            if constexpr (T::IS_BLOCKED)
            {
                Seek(-size, CUR);
                Write(size);
                Seek(size - 4, CUR);
            }
            return size;
        }
        return Write(static_cast<const void *>(&obj), sizeof(obj));
    }

    template <class T> int32_t Read(T &obj, bool blocked)
    {
        if (blocked)
        {
            Seek(4, CUR);
        }
        if constexpr (std::is_class<T>())
        {
            return obj.Read(*this);
        }

        return Read(static_cast<void *>(&obj), sizeof(obj));
    }

    template <class T> int32_t Write(const T &obj, bool blocked)
    {
        int32_t size = 0;
        if (blocked)
        {
            size += Write(size);
        }
        if constexpr (std::is_class<T>())
        {
            int32_t err = obj.Write(*this);
            if (err < 0)
            {
                return size;
            }
            size += err;
        }
        else
        {
            size += Write(static_cast<const void *>(&obj), sizeof(obj));
        }
        if (blocked)
        {
            Seek(-size, CUR);
            Write(size);
            Seek(size - 4, CUR);
        }

        return size;
    }

    size_t tell();
    errno_t Seek(int64_t offset, int whence);
    Stream(const char *path, const char *mode);
    ~Stream();
};

} // namespace TTH
