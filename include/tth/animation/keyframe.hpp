#pragma once

#include <tth/container/dcarray.hpp>
#include <tth/crypto/crc64.hpp>
#include <tth/flags.hpp>
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
        AnimationValueInterfaceBase *base = this;
        return stream.Read(*base);
    }

    virtual int32_t Write(Stream &stream) const
    {
        AnimationValueInterfaceBase *base = this;
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
        int32_t err = stream.Read(interface);
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
        AnimatedValueInterface<T> *interface = this;
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
};

}; // namespace TTH