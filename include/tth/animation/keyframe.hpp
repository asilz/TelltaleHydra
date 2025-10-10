#pragma once

#include <tth/container/dcarray.hpp>
#include <tth/crypto/crc64.hpp>
#include <tth/flags.hpp>
#include <tth/linalg/transform.hpp>
#include <tth/linalg/vector.hpp>
#include <tth/stream/stream.hpp>

namespace TTH
{
class AnimationValueInterfaceBase
{
  public:
    Symbol mName;
    Flags mFlags;

    virtual ~AnimationValueInterfaceBase() {}

    virtual int32_t Read(Stream &stream)
    {
        int32_t size = 0;
        int32_t err;
        err = stream.Read(mName);
        if (err < 0)
        {
            return err;
        }
        size += err;

        err = stream.Read(mFlags);
        if (err < 0)
        {
            return err;
        }
        size += err;
        return size;
    }

    virtual int32_t Write(Stream &stream) const
    {
        int32_t size = 0;
        int32_t err;
        err = stream.Write(mName);
        if (err < 0)
        {
            return err;
        }
        size += err;

        err = stream.Write(mFlags);
        if (err < 0)
        {
            return err;
        }
        size += err;
        return size;
    }

    static constexpr bool IS_BLOCKED = true;
};

template <class T> class AnimatedValueInterface : public AnimationValueInterfaceBase
{
  public:
    virtual ~AnimatedValueInterface() {}

    virtual int32_t Read(Stream &stream)
    {
        AnimationValueInterfaceBase *interface = this;
        return stream.ReadBase(*interface);
    }

    virtual int32_t Write(Stream &stream) const
    {
        const AnimationValueInterfaceBase *base = this;
        return stream.Write(*base);
    }

    static constexpr bool IS_BLOCKED = true;
};

template <class T> class KeyframedValue : public AnimatedValueInterface<T>
{
  public:
    struct Sample
    {
        int32_t Read(Stream &stream)
        {
            int32_t size = stream.Read(mTime);
            size += stream.Read(mbInterpolateToNextKey);
            size += stream.Read(mTangentMode);
            size += stream.Read(mValue);
            return size;
        }
        int32_t Write(Stream &stream) const
        {
            int32_t size = stream.Write(mTime);
            size += stream.Write(mbInterpolateToNextKey);
            size += stream.Write(mTangentMode);
            size += stream.Write(mValue);
            return size;
        }

        Sample(float time, bool interpolateToNextKey, int32_t tangentMode, const T &value) : mTime(time), mbInterpolateToNextKey(interpolateToNextKey), mTangentMode(tangentMode), mValue(value) {}
        Sample() : mTime(0.0f), mbInterpolateToNextKey(false), mTangentMode(0) {}

        float mTime;
        bool mbInterpolateToNextKey;
        int32_t mTangentMode;
        T mValue;
        static constexpr bool IS_BLOCKED = false;
    };

    int32_t Read(Stream &stream)
    {
        int32_t size = 0;
        AnimatedValueInterface<T> *interface = this;
        int32_t err = stream.ReadBase(*interface);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Read(mMinValue);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Read(mMaxValue);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Read(mSamples);
        if (err < 0)
        {
            return err;
        }
        size += err;
        return size;
    }
    int32_t Write(Stream &stream) const
    {
        int32_t size = 0;
        const AnimatedValueInterface<T> *interface = this;
        int32_t err = stream.Write(interface);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Write(mMinValue);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Write(mMaxValue);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Write(mSamples);
        if (err < 0)
        {
            return err;
        }
        size += err;
        return size;
    }

    ~KeyframedValue() {}
    T mMinValue;
    T mMaxValue;
    DCArray<Sample> mSamples;

    KeyframedValue() : mSamples(0) {}
    static constexpr uint64_t GetTypeCRC64(uint64_t crc = 0) { return CRC64_CaseInsensitive(">", T::GetTypeCRC64(CRC64_CaseInsensitive("KeyframedValue<"))); }
    static constexpr bool IS_BLOCKED = true;
};

template <> constexpr uint64_t KeyframedValue<bool>::GetTypeCRC64(uint64_t crc) { return CRC64_CaseInsensitive("KeyframedValue<bool>"); }
template <> constexpr uint64_t KeyframedValue<float>::GetTypeCRC64(uint64_t crc) { return CRC64_CaseInsensitive("KeyframedValue<float>"); }
template <> constexpr uint64_t KeyframedValue<double>::GetTypeCRC64(uint64_t crc) { return CRC64_CaseInsensitive("KeyframedValue<double>"); }
template <> constexpr uint64_t KeyframedValue<char>::GetTypeCRC64(uint64_t crc) { return CRC64_CaseInsensitive("KeyframedValue<char>"); }
template <> constexpr uint64_t KeyframedValue<short>::GetTypeCRC64(uint64_t crc) { return CRC64_CaseInsensitive("KeyframedValue<short>"); }
template <> constexpr uint64_t KeyframedValue<int>::GetTypeCRC64(uint64_t crc) { return CRC64_CaseInsensitive("KeyframedValue<int>"); }
template <> constexpr uint64_t KeyframedValue<long>::GetTypeCRC64(uint64_t crc) { return CRC64_CaseInsensitive("KeyframedValue<long>"); }
template <> constexpr uint64_t KeyframedValue<unsigned char>::GetTypeCRC64(uint64_t crc) { return CRC64_CaseInsensitive("KeyframedValue<unsignedchar>"); }
template <> constexpr uint64_t KeyframedValue<unsigned short>::GetTypeCRC64(uint64_t crc) { return CRC64_CaseInsensitive("KeyframedValue<unsignedshort>"); }
template <> constexpr uint64_t KeyframedValue<unsigned int>::GetTypeCRC64(uint64_t crc) { return CRC64_CaseInsensitive("KeyframedValue<unsignedint>"); }
template <> constexpr uint64_t KeyframedValue<unsigned long>::GetTypeCRC64(uint64_t crc) { return CRC64_CaseInsensitive("KeyframedValue<unsignedlong>"); }

}; // namespace TTH