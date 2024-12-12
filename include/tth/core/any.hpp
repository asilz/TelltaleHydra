#pragma once

#include <tth/stream/stream.hpp>
#include <utility>

class Any
{
  public:
    template <class T> Any(T &&obj) : obj_(new T{std::forward<T>(obj)}), dtor_(DtorAny<T>), copy_(CopyAny<T>), read_(ReadAny<T>), write_(WriteAny<T>) {}
    ~Any() { dtor_(obj_); }

    Any(const Any &other) : obj_(other.copy_(other.obj_)), dtor_(other.dtor_), copy_(other.copy_) {}

    template <class T> T *GetTypePtr()
    {
        if (dtor_ == Any::DtorAny<T>)
        {
            return static_cast<T *>(obj_);
        }
        return nullptr;
    }

    static constexpr bool IS_BLOCKED = false;

    uint32_t Read(Stream &stream, bool blocked = IS_BLOCKED) { return read_(stream, obj_); }
    uint32_t Write(Stream &stream, bool blocked = IS_BLOCKED) { return write_(stream, obj_); }

  private:
    template <class T> static void DtorAny(void *obj) { delete static_cast<T *>(obj); }
    template <class T> static void *CopyAny(void *obj) { return new T{*static_cast<T *>(obj)}; }

    template <class T> static uint32_t ReadAny(Stream &stream, void *obj)
    {
        if constexpr (requires { T::Read(); })
        {
            return static_cast<T *>(obj).Read(stream);
        }
        else
        {
            return 0;
        }
    }
    template <class T> static uint32_t WriteAny(Stream &stream, const void *obj)
    {
        if constexpr (requires { T::Write(); })
        {
            return static_cast<T *>(obj).Write(stream);
        }
        else
        {
            return 0;
        }
    }

    void *obj_;
    void (*dtor_)(void *);
    void *(*copy_)(void *);
    uint32_t (*read_)(Stream &, void *);
    uint32_t (*write_)(Stream &, const void *);
};