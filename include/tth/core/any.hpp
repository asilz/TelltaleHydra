#pragma once

#include <tth/core/utils.hpp>
#include <tth/stream/object.hpp>
#include <tth/stream/stream.hpp>
#include <utility>

class Any
{
  public:
    explicit Any(uint64_t hash);

    template <class T> explicit Any(T &&obj) : obj_(new T{std::forward<T>(obj)}), dtor_(DtorAny<T>), copy_(CopyAny<T>), read_(ReadAny<T>), write_(WriteAny<T>), typeName_(::GetTypeName<T>()) {}
    explicit Any() : obj_(nullptr), dtor_(nullptr), copy_(nullptr), read_(nullptr), write_(nullptr), typeName_(nullptr) {}

    ~Any()
    {
        if (dtor_)
        {
            dtor_(obj_);
            obj_ = nullptr;
            dtor_ = nullptr;
        }
    }

    Any(const Any &other) : obj_(other.copy_(other.obj_)), dtor_(other.dtor_), copy_(other.copy_), read_(other.read_), write_(other.write_), typeName_(other.typeName_) {}
    Any &operator=(Any &&other) noexcept
    {
        if (this != &other)
        {
            if (dtor_)
            {
                dtor_(obj_);
            }
            obj_ = other.obj_;
            dtor_ = other.dtor_;
            copy_ = other.copy_;
            read_ = other.read_;
            write_ = other.write_;
            typeName_ = other.typeName_;
            other.obj_ = nullptr;
            other.dtor_ = nullptr;
        }
        return *this;
    }

    template <class T> void SetType()
    {
        this->~Any();
        obj_ = new T;
        dtor_ = DtorAny<T>;
        read_ = ReadAny<T>;
        write_ = WriteAny<T>;
        copy_ = CopyAny<T>;
        typeName_ = ::GetTypeName<T>();
    }
    template <class T> T *GetTypePtr()
    {
        if (dtor_ == Any::DtorAny<T>)
        {
            return static_cast<T *>(obj_);
        }
        return nullptr;
    }

    static constexpr bool IS_BLOCKED = false;

    uint32_t Read(Stream &stream) { return read_(stream, obj_); }
    uint32_t Write(Stream &stream) const { return write_(stream, obj_); }

    const char *GetTypeName() { return typeName_; }

  private:
    template <class T> static void DtorAny(void *obj) { delete static_cast<T *>(obj); }
    template <class T> static void *CopyAny(void *obj) { return new T{*static_cast<T *>(obj)}; }

    template <class T> static uint32_t ReadAny(Stream &stream, void *obj) { return ReadObject<T>(*static_cast<T *>(obj), stream, false); }
    template <class T> static uint32_t WriteAny(Stream &stream, const void *obj) { return WriteObject<T>(*static_cast<const T *>(obj), stream, false); }

    void *obj_;
    void (*dtor_)(void *);
    void *(*copy_)(void *);
    uint32_t (*read_)(Stream &, void *);
    uint32_t (*write_)(Stream &, const void *);
    const char *typeName_;
};