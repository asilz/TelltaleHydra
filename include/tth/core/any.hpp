#pragma once

#include <tth/stream/stream.hpp>
#include <utility>

namespace TTH
{

class Any
{
  private:
    template <typename T, typename = void> struct has_member_create_ : std::false_type
    {
    };

    template <typename T> struct has_member_create_<T, std::void_t<decltype(std::declval<T>().Create())>> : std::true_type
    {
    };

    template <typename T> static inline constexpr bool has_member_create_v_ = has_member_create_<T>::value;

  public:
    explicit Any(uint64_t hash);

    template <class T> explicit Any(T &&obj) : obj_(new T{std::forward<T>(obj)}), dtor_(DtorAny<T>), copy_(CopyAny<T>), read_(ReadAny<T>), write_(WriteAny<T>) {}
    explicit Any() : obj_(nullptr), dtor_(nullptr), copy_(nullptr), read_(nullptr), write_(nullptr) {}

    ~Any()
    {
        if (dtor_)
        {
            dtor_(obj_);
            obj_ = nullptr;
            dtor_ = nullptr;
        }
    }

    Any(const Any &other) : obj_(other.copy_(other.obj_)), dtor_(other.dtor_), copy_(other.copy_), read_(other.read_), write_(other.write_) {}
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
            other.obj_ = nullptr;
            other.dtor_ = nullptr;
        }
        return *this;
    }

    template <class T> void SetType()
    {
        this->~Any();
        obj_ = new T;
        if constexpr (has_member_create_v_<T>)
        {
            static_cast<T *>(obj_)->Create();
        }
        dtor_ = DtorAny<T>;
        read_ = ReadAny<T>;
        write_ = WriteAny<T>;
        copy_ = CopyAny<T>;
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

  private:
    template <class T> static void DtorAny(void *obj)
    {
        if constexpr (has_member_create_v_<T>)
        {
            static_cast<T *>(obj)->Destroy();
        }
        delete static_cast<T *>(obj);
    }
    template <class T> static void *CopyAny(void *obj) { return new T{*static_cast<T *>(obj)}; }

    template <class T> static int32_t ReadAny(Stream &stream, void *obj) { return stream.Read<T>(*static_cast<T *>(obj), false); }
    template <class T> static int32_t WriteAny(Stream &stream, const void *obj) { return stream.Write<T>(*static_cast<const T *>(obj), false); }

    void *obj_;
    void (*dtor_)(void *);
    void *(*copy_)(void *);
    int32_t (*read_)(Stream &, void *);
    int32_t (*write_)(Stream &, const void *);
};

} // namespace TTH