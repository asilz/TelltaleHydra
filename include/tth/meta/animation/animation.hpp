#pragma once

#include <memory>
#include <tth/core/any.hpp>
#include <tth/meta/animation/keyframe.hpp>
#include <tth/meta/container/dcarray.hpp>
#include <tth/meta/container/ptr.hpp>
#include <tth/meta/crc64/symbol.hpp>
#include <tth/meta/flags.hpp>
#include <tth/meta/toolprops.hpp>

namespace TTH
{

class Animation // virtual
{
  private:
    struct Value
    {
        uint64_t hash;
        uint16_t valueCount;
        uint16_t typeVersion;
    };

    inline virtual int32_t Read_(Stream &stream)
    {
        int32_t size = 0;
        int32_t err;
        size += stream.Read(&this->mVersion, sizeof(this->mVersion));
        err = this->mFlags.Read(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = this->mName.Read(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        size += stream.Read(&this->mLength, sizeof(this->mLength));
        size += stream.Read(&this->mAdditiveMask, sizeof(this->mAdditiveMask));
        err = this->mToolProps.Read(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;

        err = stream.Seek(4, stream.CUR);
        if (err < 0)
        {
            return err;
        }

        size += stream.Read(&this->mInterfaceCount, sizeof(this->mInterfaceCount));

        int32_t dataBufferSize;
        stream.Read(&dataBufferSize, sizeof(dataBufferSize));

        int32_t animValueTypes;
        stream.Read(&animValueTypes, sizeof(animValueTypes));

        Value *animValues = new Value[animValueTypes];

        for (int32_t i = 0; i < animValueTypes; ++i)
        {
            stream.Read(&animValues[i].hash, sizeof(animValues[i].hash));
            stream.Read(&animValues[i].valueCount, sizeof(animValues[i].valueCount));
            stream.Read(&animValues[i].typeVersion, sizeof(animValues[i].typeVersion));
        }

        this->mValues = new Any[mInterfaceCount]();
        size_t anyIndex = 0;
        for (int32_t i = 0; i < animValueTypes; ++i)
        {
            for (int32_t j = 0; j < animValues[i].valueCount; ++j)
            {
                this->mValues[anyIndex] = Any(animValues[i].hash); // TODO: fix extra copy
                this->mValues[anyIndex++].Read(stream);
            }
        }

        delete[] animValues;

        this->mInterfaceFlags = new Flags[this->mInterfaceCount];
        for (int32_t i = 0; i < this->mInterfaceCount; ++i)
        {
            this->mInterfaceFlags[i].Read(stream);
        }

        uint16_t isNotInterfaceSymbols;
        stream.Read(&isNotInterfaceSymbols, sizeof(isNotInterfaceSymbols));
        if (isNotInterfaceSymbols)
        {
            this->mInterfaceSymbols = nullptr;
        }
        else
        {
            this->mInterfaceSymbols = new Symbol[this->mInterfaceCount];
            for (int32_t i = 0; i < this->mInterfaceCount; ++i)
            {
                this->mInterfaceSymbols[i].Read(stream);
            }
        }

        return size;
    }
    inline virtual int32_t Write_(Stream &stream) const
    {
        int32_t size = 0;
        int32_t err;
        size += stream.Write(&this->mVersion, sizeof(this->mVersion));
        err = this->mFlags.Write(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = this->mName.Write(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        size += stream.Write(&this->mLength, sizeof(this->mLength));
        size += stream.Write(&this->mAdditiveMask, sizeof(this->mAdditiveMask));
        err = this->mToolProps.Write(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        // TODO: Implement
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
        return Animation::Read_(stream) + 4;
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
            return Animation::Read_(stream) + 4;
        }
        return Animation::Read_(stream);
    }
    virtual int32_t Write(Stream &stream) const
    {
        int32_t size = 0;
        size += stream.Write(&size, sizeof(size));
        size += Animation::Write_(stream);
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
        size += Animation::Write_(stream);
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
    Animation() : mValues(nullptr), mInterfaceFlags(nullptr), mInterfaceSymbols(nullptr) {}
    ~Animation()
    {
        delete[] mValues;
        delete[] mInterfaceFlags;
        delete[] mInterfaceSymbols;
    }

    int32_t mVersion;
    class Flags mFlags;
    class Symbol mName;
    float mLength;
    float mAdditiveMask;
    ToolProps mToolProps;
    int32_t mInterfaceCount;
    Any *mValues;
    Flags *mInterfaceFlags;
    Symbol *mInterfaceSymbols;

    static constexpr bool IS_BLOCKED = true;
};
} // namespace TTH