#pragma once

#include <tth/meta/container/dcarray.hpp>
#include <tth/meta/crc64/symbol.hpp>
#include <tth/meta/flags.hpp>
#include <tth/meta/linalg/vector.hpp>
#include <tth/stream/object.hpp>

class AnimationValueInterfaceBase
{
  private:
    inline virtual int32_t Read_(Stream &stream)
    {
        int32_t size = 0;
        int32_t err;
        err = this->mName.Read(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = this->mFlags.Read(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        return size;
    }
    inline virtual int32_t Write_(Stream &stream) const
    {
        int32_t size = 0;
        int32_t err;
        err = this->mName.Write(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = this->mFlags.Write(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        return size;
    }

  public:
    virtual int32_t Read(Stream &stream)
    {
        int32_t err = stream.Seek(4, stream.CUR);
        if (err < 0)
        {
            return err;
        }
        return Read_(stream) + 4;
    }
    virtual int32_t Read(Stream &stream, bool blocked)
    {
        if (blocked)
        {
            int32_t err = stream.Seek(4, stream.CUR);
            if (err < 0)
            {
                return err;
            };
            return Read_(stream) + 4;
        }
        return Read_(stream);
    }
    virtual int32_t Write(Stream &stream) const
    {
        int32_t size = 0;
        size += stream.Write(&size, sizeof(size));
        size += Write_(stream);
        int32_t err = stream.Seek(-size, stream.CUR);
        if (err < 0)
        {
            return err;
        }
        (void)stream.Write(&size, sizeof(size));
        err = stream.Seek(size - 4, stream.CUR);
        if (err < 0)
        {
            return err;
        }
        return size;
    }
    virtual int32_t Write(Stream &stream, bool blocked) const
    {
        int32_t size = 0;
        if (blocked)
        {
            size += stream.Write(&size, sizeof(size));
        }
        size += Write_(stream);
        if (blocked)
        {
            int32_t err = stream.Seek(-size, stream.CUR);
            if (err < 0)
            {
                return err;
            }
            (void)stream.Write(&size, sizeof(size));
            err = stream.Seek(size - 4, stream.CUR);
            if (err < 0)
            {
                return err;
            }
        }
        return size;
    }
    virtual ~AnimationValueInterfaceBase() {}

    static constexpr bool IS_BLOCKED = true;

    Symbol mName;
    Flags mFlags;
};

template <class T> class AnimatedValueInterface : AnimationValueInterfaceBase
{
  private:
    inline virtual int32_t Read_(Stream &stream) { return AnimationValueInterfaceBase::Read(stream, true); }
    inline virtual int32_t Write_(Stream &stream) const { return AnimationValueInterfaceBase::Write(stream, true); }

  public:
    virtual int32_t Read(Stream &stream)
    {
        int32_t err = stream.Seek(4, stream.CUR);
        if (err < 0)
        {
            return err;
        }
        return Read_(stream) + 4;
    }
    virtual int32_t Read(Stream &stream, bool blocked)
    {
        if (blocked)
        {
            int32_t err = stream.Seek(4, stream.CUR);
            if (err < 0)
            {
                return err;
            };
            return Read_(stream) + 4;
        }
        return Read_(stream);
    }
    virtual int32_t Write(Stream &stream) const
    {
        int32_t size = 0;
        size += stream.Write(&size, sizeof(size));
        size += Write_(stream);
        int32_t err = stream.Seek(-size, stream.CUR);
        if (err < 0)
        {
            return err;
        }
        (void)stream.Write(&size, sizeof(size));
        err = stream.Seek(size - 4, stream.CUR);
        if (err < 0)
        {
            return err;
        }
        return size;
    }
    virtual int32_t Write(Stream &stream, bool blocked) const
    {
        int32_t size = 0;
        if (blocked)
        {
            size += stream.Write(&size, sizeof(size));
        }
        size += Write_(stream);
        if (blocked)
        {
            int32_t err = stream.Seek(-size, stream.CUR);
            if (err < 0)
            {
                return err;
            }
            (void)stream.Write(&size, sizeof(size));
            err = stream.Seek(size - 4, stream.CUR);
            if (err < 0)
            {
                return err;
            }
        }
        return size;
    }
    virtual ~AnimatedValueInterface() {}
    static constexpr bool IS_BLOCKED = true;
};

template <class T> class KeyframedValue : public AnimatedValueInterface<T>
{
  private:
    inline int32_t Read_(Stream &stream)
    {
        int32_t size = 0;
        int32_t err = AnimatedValueInterface<T>::Read(stream, true);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = ReadObject<T>(this->mMinValue, stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = ReadObject<T>(this->mMaxValue, stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = this->mSamples.Read(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        return size;
    }
    inline int32_t Write_(Stream &stream) const
    {
        int32_t size = 0;
        int32_t err = AnimatedValueInterface<T>::Write(stream, true);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = WriteObject<T>(this->mMinValue, stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = WriteObject<T>(this->mMaxValue, stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = this->mSamples.Write(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        return size;
    }

  public:
    int32_t Read(Stream &stream)
    {
        int32_t err = stream.Seek(4, stream.CUR);
        if (err < 0)
        {
            return err;
        }
        return Read_(stream) + 4;
    }
    int32_t Read(Stream &stream, bool blocked)
    {
        if (blocked)
        {
            int32_t err = stream.Seek(4, stream.CUR);
            if (err < 0)
            {
                return err;
            };
            return Read_(stream) + 4;
        }
        return Read_(stream);
    }
    int32_t Write(Stream &stream) const
    {
        int32_t size = 0;
        size += stream.Write(&size, sizeof(size));
        size += Write_(stream);
        int32_t err = stream.Seek(-size, stream.CUR);
        if (err < 0)
        {
            return err;
        }
        (void)stream.Write(&size, sizeof(size));
        err = stream.Seek(size - 4, stream.CUR);
        if (err < 0)
        {
            return err;
        }
        return size;
    }
    int32_t Write(Stream &stream, bool blocked) const
    {
        int32_t size = 0;
        if (blocked)
        {
            size += stream.Write(&size, sizeof(size));
        }
        size += Write_(stream);
        if (blocked)
        {
            int32_t err = stream.Seek(-size, stream.CUR);
            if (err < 0)
            {
                return err;
            }
            (void)stream.Write(&size, sizeof(size));
            err = stream.Seek(size - 4, stream.CUR);
            if (err < 0)
            {
                return err;
            }
        }
        return size;
    }

    struct Sample
    {
      private:
        inline int32_t Read_(Stream &stream)
        {
            int32_t size = stream.Read(&this->mTime, sizeof(this->mTime));
            size += stream.Read(&this->mbInterpolateToNextKey, sizeof(this->mbInterpolateToNextKey));
            size += stream.Read(&this->mTangentMode, sizeof(this->mTangentMode));
            size += ReadObject<T>(this->value, stream);
            return size;
        }
        inline int32_t Write_(Stream &stream) const
        {
            int32_t size = stream.Write(&this->mTime, sizeof(this->mTime));
            size += stream.Write(&this->mbInterpolateToNextKey, sizeof(this->mbInterpolateToNextKey));
            size += stream.Write(&this->mTangentMode, sizeof(this->mTangentMode));
            size += WriteObject<T>(this->value, stream);
            return size;
        }

      public:
        int32_t Read(Stream &stream) { return Read_(stream); }
        int32_t Read(Stream &stream, bool blocked)
        {
            if (blocked)
            {
                int32_t err = stream.Seek(4, stream.CUR);
                if (err < 0)
                {
                    return err;
                };
                return Read_(stream) + 4;
            }
            return Read_(stream);
        }
        int32_t Write(Stream &stream) const { return Write_(stream); }
        int32_t Write(Stream &stream, bool blocked) const
        {
            int32_t size = 0;
            if (blocked)
            {
                size += stream.Write(&size, sizeof(size));
            }
            size += Write_(stream);
            if (blocked)
            {
                int32_t err = stream.Seek(-size, stream.CUR);
                if (err < 0)
                {
                    return err;
                }
                (void)stream.Write(&size, sizeof(size));
                err = stream.Seek(size - 4, stream.CUR);
                if (err < 0)
                {
                    return err;
                }
            }
            return size;
        }

        float mTime;
        bool mbInterpolateToNextKey;
        int32_t mTangentMode;
        T value;
        static constexpr bool IS_BLOCKED = false;
    };
    ~KeyframedValue() {}
    T mMinValue;
    T mMaxValue;
    DCArray<Sample> mSamples;
};

class CompressedSkeletonPoseKeys2 : public AnimationValueInterfaceBase
{
  private:
    inline int32_t Read_(Stream &stream) override
    {
        stream.Read(&this->mDataSize, sizeof(this->mDataSize));
        mpData = new uint8_t[mDataSize];
        stream.Read(mpData, mDataSize);
        return mDataSize + 4;
    }
    inline int32_t Write_(Stream &stream) const override
    {
        stream.Write(&this->mDataSize, sizeof(this->mDataSize));
        stream.Write(mpData, mDataSize);
        return mDataSize + 4;
    }

  public:
    int32_t Read(Stream &stream) override { return Read_(stream); }
    int32_t Read(Stream &stream, bool blocked) override
    {
        if (blocked)
        {
            int32_t err = stream.Seek(4, stream.CUR);
            if (err < 0)
            {
                return err;
            };
            return Read_(stream) + 4;
        }
        return Read_(stream);
    }
    int32_t Write(Stream &stream) const override { return Write_(stream); }
    int32_t Write(Stream &stream, bool blocked) const override
    {
        int32_t size = 0;
        if (blocked)
        {
            size += stream.Write(&size, sizeof(size));
        }
        size += Write_(stream);
        if (blocked)
        {
            int32_t err = stream.Seek(-size, stream.CUR);
            if (err < 0)
            {
                return err;
            }
            (void)stream.Write(&size, sizeof(size));
            err = stream.Seek(size - 4, stream.CUR);
            if (err < 0)
            {
                return err;
            }
        }
        return size;
    }

    ~CompressedSkeletonPoseKeys2() { delete mpData; }
    CompressedSkeletonPoseKeys2() : mDataSize(0), mpData(nullptr) {}

    uint32_t mDataSize;
    uint8_t *mpData;

    static constexpr bool IS_BLOCKED = false;
};