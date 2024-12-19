#pragma once

#include <tth/core/any.hpp>
#include <tth/core/log.hpp>
#include <tth/meta/bitset/base.hpp>
#include <tth/meta/container/dcarray.hpp>
#include <tth/meta/container/ptr.hpp>
#include <tth/meta/crc64/symbol.hpp>
#include <tth/meta/flags.hpp>
#include <tth/meta/handle/handle.hpp>
#include <tth/meta/linalg/transform.hpp>
#include <tth/meta/prop/prop.hpp>
#include <tth/meta/string/string.hpp>
#include <tth/meta/t3texture/t3texture.hpp>
#include <tth/meta/toolprops.hpp>

namespace TTH
{

class BinaryBuffer
{
  private:
    inline int32_t Read_(Stream &stream)
    {
        stream.Read(&mDataSize, sizeof(mDataSize));
        data = new uint8_t[mDataSize];
        stream.Read(data, mDataSize);
        return mDataSize + sizeof(mDataSize);
    }
    inline int32_t Write_(Stream &stream) const
    {
        stream.Write(&mDataSize, sizeof(mDataSize));
        stream.Write(data, mDataSize);
        return mDataSize + sizeof(mDataSize);
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
    ~BinaryBuffer() { delete[] data; }
    BinaryBuffer() : mDataSize(0), data(nullptr) {}

    int32_t mDataSize;
    uint8_t *data;
    static constexpr bool IS_BLOCKED = true;
};

struct T3MaterialTextureParam
{
  private:
    inline int32_t Read_(Stream &stream)
    {
        int32_t size = stream.Read(&mParamType, sizeof(mParamType));
        size += stream.Read(&mValueType, sizeof(mValueType));
        size += stream.Read(&mFlags, sizeof(mFlags));
        size += stream.Read(&mScalarOffset, sizeof(mScalarOffset));

        return size;
    }
    inline int32_t Write_(Stream &stream) const
    {
        int32_t size = stream.Write(&mParamType, sizeof(mParamType));
        size += stream.Write(&mValueType, sizeof(mValueType));
        size += stream.Write(&mFlags, sizeof(mFlags));
        size += stream.Write(&mScalarOffset, sizeof(mScalarOffset));
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
    int32_t mParamType;
    int32_t mValueType;
    uint32_t mFlags; // Why are these not Flags?
    int32_t mScalarOffset;
    static constexpr bool IS_BLOCKED = true;
};

struct T3MaterialNestedMaterial
{
  private:
    inline int32_t Read_(Stream &stream) { return this->mhMaterial.Read(stream); }
    inline int32_t Write_(Stream &stream) const { return this->mhMaterial.Write(stream); }

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
    Handle<PropertySet> mhMaterial;
    static constexpr bool IS_BLOCKED = true;
};

struct T3MeshMaterialOverride
{
  private:
    inline int32_t Read_(Stream &stream)
    {
        int32_t size = 0;
        int32_t err;
        err = this->mhOverrideMaterial.Read(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        size += stream.Read(&mMaterialIndex, sizeof(mMaterialIndex));
        return size;
    }
    inline int32_t Write_(Stream &stream) const
    {
        int32_t size = 0;
        int32_t err;
        err = this->mhOverrideMaterial.Write(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        size += stream.Write(&mMaterialIndex, sizeof(mMaterialIndex));
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
    Handle<PropertySet> mhOverrideMaterial;
    uint32_t mMaterialIndex;
    static constexpr bool IS_BLOCKED = true;
};

struct T3MeshLocalTransformEntry
{
  private:
    inline int32_t Read_(Stream &stream)
    {
        int32_t size = 0;
        int32_t err;
        err = this->mTransform.Read(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        size += stream.Read(&mCameraFacingType, sizeof(mCameraFacingType));
        return size;
    }
    inline int32_t Write_(Stream &stream) const
    {
        int32_t size = 0;
        int32_t err;
        err = this->mTransform.Write(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        size += stream.Write(&mCameraFacingType, sizeof(mCameraFacingType));
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
    Transform mTransform;
    int32_t mCameraFacingType;
    static constexpr bool IS_BLOCKED = true;
};

struct T3MeshTextureIndices
{
  private:
    inline int32_t Read_(Stream &stream)
    {
        int32_t size = 0;
        do
        {
            uint32_t index;
            size += stream.Read(&index, sizeof(index));
            if (index == 0xffffffff)
            {
                break;
            }
            int32_t value;
            size += stream.Read(&value, sizeof(value));
            if (index < 2)
            {
                mIndex[index] = value;
            }
        } while (1);
        return size;
    }
    inline int32_t Write_(Stream &stream) const
    {
        int32_t size = 0;
        for (uint32_t i = 0; i < sizeof(mIndex) / sizeof(mIndex[0]); ++i)
        {
            if (mIndex[i] > -1)
            {
                size += stream.Write(&i, sizeof(i));
                size += stream.Write(&mIndex[i], sizeof(mIndex[i]));
            }
        }
        size += stream.Write("\xff\xff\xff\xff", sizeof(uint32_t));
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
    static constexpr bool IS_BLOCKED = true;

    int32_t mIndex[2];
};

struct T3MaterialParameter
{
  private:
    inline int32_t Read_(Stream &stream)
    {
        int32_t size = 0;
        int32_t err;
        err = this->mName.Read(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        size += stream.Read(&this->mPropertyType, sizeof(this->mPropertyType));
        size += stream.Read(&this->mValueType, sizeof(this->mValueType));
        size += stream.Read(&this->mFlags, sizeof(this->mFlags));
        size += stream.Read(&this->mScalarOffset, sizeof(this->mScalarOffset));
        size += stream.Read(&this->mPreShaderScalarOffset, sizeof(this->mPreShaderScalarOffset));
        size += stream.Read(&this->mNestedMaterialIndex, sizeof(this->mNestedMaterialIndex));
        return size;
    }
    inline int32_t Write_(Stream &stream) const
    {
        int32_t size = 0;
        int32_t err;
        err = this->mName.Write(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        size += stream.Write(&this->mPropertyType, sizeof(this->mPropertyType));
        size += stream.Write(&this->mValueType, sizeof(this->mValueType));
        size += stream.Write(&this->mFlags, sizeof(this->mFlags));
        size += stream.Write(&this->mScalarOffset, sizeof(this->mScalarOffset));
        size += stream.Write(&this->mPreShaderScalarOffset, sizeof(this->mPreShaderScalarOffset));
        size += stream.Write(&this->mNestedMaterialIndex, sizeof(this->mNestedMaterialIndex));
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
    class Symbol mName;
    int32_t mPropertyType;
    int32_t mValueType;
    uint32_t mFlags;
    int32_t mScalarOffset;
    int32_t mPreShaderScalarOffset;
    int32_t mNestedMaterialIndex;
    static constexpr bool IS_BLOCKED = true;
};

class LocationInfo
{
  private:
    inline int32_t Read_(Stream &stream)
    {
        int32_t size = 0;
        int32_t err;
        err = this->mAttachmentAgent.Read(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = this->mAttachmentNode.Read(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = this->mInitialLocalTransform.Read(stream);
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
        int32_t err;
        err = this->mAttachmentAgent.Write(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = this->mAttachmentNode.Write(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = this->mInitialLocalTransform.Write(stream);
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
    class String mAttachmentAgent;
    class Symbol mAttachmentNode;
    class Transform mInitialLocalTransform;
    static constexpr bool IS_BLOCKED = true;
};
struct T3MaterialEnlightenPrecomputeParams
{
  private:
    inline int32_t Read_(Stream &stream)
    {
        int32_t size = stream.Read(&this->mIndirectReflectivity, sizeof(this->mIndirectReflectivity));
        size += stream.Read(&this->mIndirectTransparency, sizeof(this->mIndirectTransparency));
        return size;
    }
    inline int32_t Write_(Stream &stream) const
    {
        int32_t size = stream.Write(&this->mIndirectReflectivity, sizeof(this->mIndirectReflectivity));
        size += stream.Write(&this->mIndirectTransparency, sizeof(this->mIndirectTransparency));
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
    float mIndirectReflectivity;
    float mIndirectTransparency;
    static constexpr bool IS_BLOCKED = true;
};
struct T3GFXBuffer
{
  private:
    inline int32_t Read_(Stream &stream)
    {
        int32_t size = stream.Read(&this->mResourceUsage, sizeof(this->mResourceUsage));
        size += stream.Read(&this->mBufferFormat, sizeof(this->mBufferFormat));
        size += stream.Read(&this->mBufferUsage, sizeof(this->mBufferUsage));
        size += stream.Read(&this->mCount, sizeof(this->mCount));
        size += stream.Read(&this->mStride, sizeof(this->mStride));
        return size;
    }
    inline int32_t Write_(Stream &stream) const
    {
        int32_t size = stream.Write(&this->mResourceUsage, sizeof(this->mResourceUsage));
        size += stream.Write(&this->mBufferFormat, sizeof(this->mBufferFormat));
        size += stream.Write(&this->mBufferUsage, sizeof(this->mBufferUsage));
        size += stream.Write(&this->mCount, sizeof(this->mCount));
        size += stream.Write(&this->mStride, sizeof(this->mStride));
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
    int32_t mResourceUsage;
    int32_t mBufferFormat;
    uint32_t mBufferUsage;
    uint32_t mCount;
    uint32_t mStride;
    static constexpr bool IS_BLOCKED = true;
};
struct GFXPlatformAttributeParams
{
  private:
    inline int32_t Read_(Stream &stream)
    {
        int32_t size = stream.Read(&this->mAttribute, sizeof(this->mAttribute));
        size += stream.Read(&this->mFormat, sizeof(this->mFormat));
        size += stream.Read(&this->mAttributeIndex, sizeof(this->mAttributeIndex));
        size += stream.Read(&this->mBufferIndex, sizeof(this->mBufferIndex));
        size += stream.Read(&this->mBufferOffset, sizeof(this->mBufferOffset));
        return size;
    }
    inline int32_t Write_(Stream &stream) const
    {
        int32_t size = stream.Write(&this->mAttribute, sizeof(this->mAttribute));
        size += stream.Write(&this->mFormat, sizeof(this->mFormat));
        size += stream.Write(&this->mAttributeIndex, sizeof(this->mAttributeIndex));
        size += stream.Write(&this->mBufferIndex, sizeof(this->mBufferIndex));
        size += stream.Write(&this->mBufferOffset, sizeof(this->mBufferOffset));
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
    int32_t mAttribute;
    int32_t mFormat;
    uint32_t mAttributeIndex;
    uint32_t mBufferIndex;
    uint32_t mBufferOffset;
    static constexpr bool IS_BLOCKED = true;
};
struct T3GFXVertexState
{
  private:
    inline int32_t Read_(Stream &stream)
    {
        int32_t size = stream.Read(&this->mVertexCountPerInstance, sizeof(this->mVertexCountPerInstance));
        size += stream.Read(&this->mIndexBufferCount, sizeof(this->mIndexBufferCount));
        size += stream.Read(&this->mVertexBufferCount, sizeof(this->mVertexBufferCount));
        size += stream.Read(&this->mAttributeCount, sizeof(this->mAttributeCount));

        for (uint32_t i = 0; i < mAttributeCount; ++i)
        {
            int32_t err = this->mAttributes[i].Read(stream, false);
            if (err < 0)
            {
                return err;
            }
            size += err;
        }
        for (uint32_t i = 0; i < mIndexBufferCount; ++i)
        {
            int32_t err = this->mpIndexBuffer[i].Read(stream, false);
            if (err < 0)
            {
                return err;
            }
            size += err;
        }
        for (uint32_t i = 0; i < mVertexBufferCount; ++i)
        {
            int32_t err = this->mpVertexBuffer[i].Read(stream, false);
            if (err < 0)
            {
                return err;
            }
            size += err;
        }

        return size;
    }
    inline int32_t Write_(Stream &stream) const
    {
        int32_t size = stream.Write(&this->mVertexCountPerInstance, sizeof(this->mVertexCountPerInstance));
        size += stream.Write(&this->mIndexBufferCount, sizeof(this->mIndexBufferCount));
        size += stream.Write(&this->mVertexBufferCount, sizeof(this->mVertexBufferCount));
        size += stream.Write(&this->mAttributeCount, sizeof(this->mAttributeCount));

        for (uint32_t i = 0; i < mIndexBufferCount; ++i)
        {
            int32_t err = this->mpIndexBuffer[i].Write(stream);
            if (err < 0)
            {
                return err;
            }
            size += err;
        }
        for (uint32_t i = 0; i < mVertexBufferCount; ++i)
        {
            int32_t err = this->mpVertexBuffer[i].Write(stream);
            if (err < 0)
            {
                return err;
            }
            size += err;
        }
        for (uint32_t i = 0; i < mAttributeCount; ++i)
        {
            int32_t err = this->mAttributes[i].Write(stream);
            if (err < 0)
            {
                return err;
            }
            size += err;
        }

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
    uint32_t mVertexCountPerInstance;
    uint32_t mIndexBufferCount;
    uint32_t mVertexBufferCount;
    uint32_t mAttributeCount;

    T3GFXBuffer mpIndexBuffer[4];
    T3GFXBuffer mpVertexBuffer[32];
    GFXPlatformAttributeParams mAttributes[32];
    static constexpr bool IS_BLOCKED = true;
};

class Sphere
{
  private:
    inline int32_t Read_(Stream &stream)
    {
        int32_t size = 0;
        int32_t err;
        err = this->mCenter.Read(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        size += stream.Read(&this->mRadius, sizeof(this->mRadius));
        return size;
    }
    inline int32_t Write_(Stream &stream) const
    {
        int32_t size = 0;
        int32_t err;
        err = this->mCenter.Write(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        size += stream.Write(&this->mRadius, sizeof(this->mRadius));
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
    class Vector3 mCenter;
    float mRadius;
    static constexpr bool IS_BLOCKED = true;
};
class BoundingBox
{
  private:
    inline int32_t Read_(Stream &stream)
    {
        int32_t size = 0;
        int32_t err;
        err = this->mMin.Read(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = this->mMax.Read(stream);
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
        int32_t err;
        err = this->mMin.Write(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = this->mMax.Write(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
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
    class Vector3 mMin;
    class Vector3 mMax;
    static constexpr bool IS_BLOCKED = false;
};

struct T3MeshBoneEntry
{
  private:
    inline int32_t Read_(Stream &stream)
    {
        int32_t size = 0;
        int32_t err;
        err = this->mBoneName.Read(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;

        err = this->mBoundingBox.Read(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;

        err = this->mBoundingSphere.Read(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;

        size += stream.Read(&this->mNumVerts, sizeof(this->mNumVerts));
        return size;
    }
    inline int32_t Write_(Stream &stream) const
    {
        int32_t size = 0;
        int32_t err;
        err = this->mBoneName.Write(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;

        err = this->mBoundingBox.Write(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;

        err = this->mBoundingSphere.Write(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;

        size += stream.Write(&this->mNumVerts, sizeof(this->mNumVerts));
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
    Symbol mBoneName;
    BoundingBox mBoundingBox;
    Sphere mBoundingSphere;
    int32_t mNumVerts;
    static constexpr bool IS_BLOCKED = true;
};

struct T3MeshTexture
{
  private:
    inline int32_t Read_(Stream &stream)
    {
        int32_t size = 0;
        int32_t err;

        size += stream.Read(&mTextureType, sizeof(mTextureType));

        err = this->mhTexture.Read(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;

        err = this->mNameSymbol.Read(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;

        err = this->mBoundingBox.Read(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;

        err = this->mBoundingSphere.Read(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;

        size += stream.Read(&mMaxObjAreaPerUVArea, sizeof(mMaxObjAreaPerUVArea));
        size += stream.Read(&mAverageObjAreaPerUVArea, sizeof(mAverageObjAreaPerUVArea));
        return size;
    }
    inline int32_t Write_(Stream &stream) const
    {
        int32_t size = 0;
        int32_t err;

        size += stream.Write(&mTextureType, sizeof(mTextureType));

        err = this->mhTexture.Write(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;

        err = this->mNameSymbol.Write(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;

        err = this->mBoundingBox.Write(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;

        err = this->mBoundingSphere.Write(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;

        size += stream.Write(&mMaxObjAreaPerUVArea, sizeof(mMaxObjAreaPerUVArea));
        size += stream.Write(&mAverageObjAreaPerUVArea, sizeof(mAverageObjAreaPerUVArea));
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
    int32_t mTextureType;
    Handle<T3Texture> mhTexture;
    Symbol mNameSymbol;
    BoundingBox mBoundingBox;
    Sphere mBoundingSphere;
    float mMaxObjAreaPerUVArea;
    float mAverageObjAreaPerUVArea;
    static constexpr bool IS_BLOCKED = true;
};

struct T3MaterialRequirements
{
  private:
    inline int32_t Read_(Stream &stream)
    {
        int32_t size = 0;
        int32_t err;
        err = this->mPasses.Read(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = this->mChannels.Read(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = this->mInputs.Read(stream);
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
        int32_t err;
        err = this->mPasses.Write(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = this->mChannels.Write(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = this->mInputs.Write(stream);
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
    class BitSetBase<1> mPasses;
    class BitSetBase<2> mChannels;
    class BitSetBase<3> mInputs;
    static constexpr bool IS_BLOCKED = true;
};

struct T3MeshEffectPreloadDynamicFeatures
{
  private:
    inline int32_t Read_(Stream &stream)
    {
        int32_t size = 0;
        int32_t err;
        err = this->mDynamicFeatures.Read(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        size += stream.Read(&this->mPriority, sizeof(this->mPriority));
        return size;
    }
    inline int32_t Write_(Stream &stream) const
    {
        int32_t size = 0;
        int32_t err;
        err = this->mDynamicFeatures.Write(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        size += stream.Write(&this->mPriority, sizeof(this->mPriority));
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
    class BitSetBase<1> mDynamicFeatures;
    int32_t mPriority;
    static constexpr bool IS_BLOCKED = true;
};
struct T3MeshEffectPreloadEntry
{
  private:
    inline int32_t Read_(Stream &stream)
    {
        int32_t size = 0;
        int32_t err;
        size += stream.Read(&this->mEffectType, sizeof(this->mEffectType));
        err = this->mStaticEffectFeatures.Read(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        size += stream.Read(&this->mMaterialCRC, sizeof(this->mMaterialCRC));
        err = this->mDynamicEffectFeatures.Read(stream);
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
        int32_t err;
        size += stream.Write(&this->mEffectType, sizeof(this->mEffectType));
        err = this->mStaticEffectFeatures.Write(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        size += stream.Write(&this->mMaterialCRC, sizeof(this->mMaterialCRC));
        err = this->mDynamicEffectFeatures.Write(stream);
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
    uint32_t mEffectType;
    class BitSetBase<3> mStaticEffectFeatures;
    uint64_t mMaterialCRC;
    class DCArray<struct T3MeshEffectPreloadDynamicFeatures> mDynamicEffectFeatures;
    static constexpr bool IS_BLOCKED = true;
};
struct T3MeshEffectPreload
{
  private:
    inline int32_t Read_(Stream &stream)
    {
        int32_t size = 0;
        int32_t err;
        size += stream.Read(&this->mEffectQuality, sizeof(this->mEffectQuality));
        err = this->mEntries.Read(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        size += stream.Read(&this->mTotalEffectCount, sizeof(this->mTotalEffectCount));
        return size;
    }
    inline int32_t Write_(Stream &stream) const
    {
        int32_t size = 0;
        int32_t err;
        size += stream.Write(&this->mEffectQuality, sizeof(this->mEffectQuality));
        err = this->mEntries.Write(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        size += stream.Write(&this->mTotalEffectCount, sizeof(this->mTotalEffectCount));
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
    int32_t mEffectQuality;
    class DCArray<struct T3MeshEffectPreloadEntry> mEntries;
    uint32_t mTotalEffectCount;
    static constexpr bool IS_BLOCKED = true;
};

struct T3MeshMaterial
{
  private:
    inline int32_t Read_(Stream &stream)
    {
        int32_t size = 0;
        int32_t err;
        err = this->mhMaterial.Read(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = this->mBaseMaterialName.Read(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = this->mLegacyRenderTextureProperty.Read(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = this->mBoundingBox.Read(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = this->mBoundingSphere.Read(stream);
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
    inline int32_t Write_(Stream &stream) const
    {
        int32_t size = 0;
        int32_t err;
        err = this->mhMaterial.Write(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = this->mBaseMaterialName.Write(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = this->mLegacyRenderTextureProperty.Write(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = this->mBoundingBox.Write(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = this->mBoundingSphere.Write(stream);
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
    class Handle<class PropertySet> mhMaterial;
    class Symbol mBaseMaterialName;
    class Symbol mLegacyRenderTextureProperty;
    class BoundingBox mBoundingBox;
    class Sphere mBoundingSphere;
    class Flags mFlags;
    static constexpr bool IS_BLOCKED = true;
};

struct T3MaterialTexture
{
  private:
    inline int32_t Read_(Stream &stream)
    {
        int32_t size = 0;
        int32_t err;
        err = this->mName.Read(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = this->mTextureName.Read(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = this->mTextureNameWithoutExtension.Read(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        size += stream.Read(&this->mLayout, sizeof(this->mLayout));
        size += stream.Read(&this->mPropertyType, sizeof(this->mPropertyType));
        err = this->mTextureTypes.Read(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        size += stream.Read(&this->mFirstParamIndex, sizeof(this->mFirstParamIndex));
        size += stream.Read(&this->mParamCount, sizeof(this->mParamCount));
        size += stream.Read(&this->mTextureIndex, sizeof(this->mTextureIndex));
        size += stream.Read(&this->mNestedMaterialIndex, sizeof(this->mNestedMaterialIndex));
        return size;
    }
    inline int32_t Write_(Stream &stream) const
    {
        int32_t size = 0;
        int32_t err;
        err = this->mName.Write(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = this->mTextureName.Write(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = this->mTextureNameWithoutExtension.Write(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        size += stream.Write(&this->mLayout, sizeof(this->mLayout));
        size += stream.Write(&this->mPropertyType, sizeof(this->mPropertyType));
        err = this->mTextureTypes.Write(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        size += stream.Write(&this->mFirstParamIndex, sizeof(this->mFirstParamIndex));
        size += stream.Write(&this->mParamCount, sizeof(this->mParamCount));
        size += stream.Write(&this->mTextureIndex, sizeof(this->mTextureIndex));
        size += stream.Write(&this->mNestedMaterialIndex, sizeof(this->mNestedMaterialIndex));
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
    class Symbol mName;
    class Symbol mTextureName;
    class Symbol mTextureNameWithoutExtension;
    int32_t mLayout;
    int32_t mPropertyType;
    class BitSetBase<1> mTextureTypes;
    uint32_t mFirstParamIndex;
    uint32_t mParamCount;
    int32_t mTextureIndex;
    int32_t mNestedMaterialIndex;
    static constexpr bool IS_BLOCKED = true;
};

struct T3MaterialTransform2D
{
  private:
    inline int32_t Read_(Stream &stream)
    {
        int32_t size = 0;
        int32_t err;
        err = this->mParameterPrefix.Read(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        size += stream.Read(&this->mFlags, sizeof(this->mFlags));
        size += stream.Read(&this->mScalarOffset0, sizeof(this->mScalarOffset0));
        size += stream.Read(&this->mScalarOffset1, sizeof(this->mScalarOffset1));
        size += stream.Read(&this->mPreShaderScalarOffset0, sizeof(this->mPreShaderScalarOffset0));
        size += stream.Read(&this->mPreShaderScalarOffset1, sizeof(this->mPreShaderScalarOffset1));
        size += stream.Read(&this->mNestedMaterialIndex, sizeof(this->mNestedMaterialIndex));
        return size;
    }
    inline int32_t Write_(Stream &stream) const
    {
        int32_t size = 0;
        int32_t err;
        err = this->mParameterPrefix.Write(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        size += stream.Write(&this->mFlags, sizeof(this->mFlags));
        size += stream.Write(&this->mScalarOffset0, sizeof(this->mScalarOffset0));
        size += stream.Write(&this->mScalarOffset1, sizeof(this->mScalarOffset1));
        size += stream.Write(&this->mPreShaderScalarOffset0, sizeof(this->mPreShaderScalarOffset0));
        size += stream.Write(&this->mPreShaderScalarOffset1, sizeof(this->mPreShaderScalarOffset1));
        size += stream.Write(&this->mNestedMaterialIndex, sizeof(this->mNestedMaterialIndex));
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
    class Symbol mParameterPrefix;
    uint32_t mFlags;
    int32_t mScalarOffset0;
    int32_t mScalarOffset1;
    int32_t mPreShaderScalarOffset0;
    int32_t mPreShaderScalarOffset1;
    int32_t mNestedMaterialIndex;
    static constexpr bool IS_BLOCKED = true;
};
struct T3MaterialStaticParameter
{
  private:
    inline int32_t Read_(Stream &stream)
    {
        int32_t size = 0;
        int32_t err;
        err = this->mName.Read(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        size += stream.Read(&this->mNestedMaterialIndex, sizeof(this->mNestedMaterialIndex));
        return size;
    }
    inline int32_t Write_(Stream &stream) const
    {
        int32_t size = 0;
        int32_t err;
        err = this->mName.Write(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        size += stream.Write(&this->mNestedMaterialIndex, sizeof(this->mNestedMaterialIndex));
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
    class Symbol mName;
    int32_t mNestedMaterialIndex;
    static constexpr bool IS_BLOCKED = true;
};

struct T3MaterialPassData
{
  private:
    inline int32_t Read_(Stream &stream)
    {
        int32_t size = stream.Read(&this->mPassType, sizeof(this->mPassType));
        size += stream.Read(&this->mBlendMode, sizeof(this->mBlendMode));
        size += stream.Read(&this->mMaterialCrc, sizeof(this->mMaterialCrc));
        return size;
    }
    inline int32_t Write_(Stream &stream) const
    {
        int32_t size = stream.Write(&this->mPassType, sizeof(this->mPassType));
        size += stream.Write(&this->mBlendMode, sizeof(this->mBlendMode));
        size += stream.Write(&this->mMaterialCrc, sizeof(this->mMaterialCrc));
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
    int32_t mPassType;
    int32_t mBlendMode;
    uint64_t mMaterialCrc;
    static constexpr bool IS_BLOCKED = true;
};
struct T3MaterialPreShader
{
  private:
    inline int32_t Read_(Stream &stream)
    {
        int32_t size = stream.Read(&this->mValueType, sizeof(this->mValueType));
        size += stream.Read(&this->mFlags, sizeof(this->mFlags));
        size += stream.Read(&this->mPreShaderOffset, sizeof(this->mPreShaderOffset));
        size += stream.Read(&this->mScalarParameterOffset, sizeof(this->mScalarParameterOffset));
        return size;
    }
    inline int32_t Write_(Stream &stream) const
    {
        int32_t size = stream.Write(&this->mValueType, sizeof(this->mValueType));
        size += stream.Write(&this->mFlags, sizeof(this->mFlags));
        size += stream.Write(&this->mPreShaderOffset, sizeof(this->mPreShaderOffset));
        size += stream.Write(&this->mScalarParameterOffset, sizeof(this->mScalarParameterOffset));
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
    int32_t mValueType;
    uint32_t mFlags;
    int32_t mPreShaderOffset;
    int32_t mScalarParameterOffset;
    static constexpr bool IS_BLOCKED = true;
};

struct T3MaterialRuntimeProperty
{
  private:
    inline int32_t Read_(Stream &stream)
    {
        int32_t size = 0;
        int32_t err;
        err = this->mName.Read(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = this->mRuntimeName.Read(stream);
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
        int32_t err;
        err = this->mName.Write(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = this->mRuntimeName.Write(stream);
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
    class Symbol mName;
    class Symbol mRuntimeName;
    static constexpr bool IS_BLOCKED = true;
};

struct T3MaterialCompiledData
{
  private:
    inline int32_t Read_(Stream &stream)
    {
        int32_t size = 0;
        int32_t err;
        err = this->mParameters.Read(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = this->mTextures.Read(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = this->mTransforms.Read(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = this->mNestedMaterials.Read(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = this->mPreShaders.Read(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = this->mStaticParameters.Read(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = this->mTextureParams.Read(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = this->mPasses.Read(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        size += stream.Read(&this->mMaterialQuality, sizeof(this->mMaterialQuality));
        err = this->mMaterialBlendModes.Read(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = this->mMaterialPasses.Read(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = this->mMaterialChannels.Read(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = this->mShaderInputs.Read(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = this->mSceneTextures.Read(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = this->mOptionalPropertyTypes.Read(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = this->mPreShaderBuffer.Read(stream);
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
        size += stream.Read(&this->mParameterBufferScalarSize[0], sizeof(this->mParameterBufferScalarSize[0]));
        size += stream.Read(&this->mParameterBufferScalarSize[1], sizeof(this->mParameterBufferScalarSize[1]));
        size += stream.Read(&this->mPreShaderParameterBufferScalarSize, sizeof(this->mPreShaderParameterBufferScalarSize));
        return size;
    }
    inline int32_t Write_(Stream &stream) const
    {
        int32_t size = 0;
        int32_t err;
        err = this->mParameters.Write(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = this->mTextures.Write(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = this->mTransforms.Write(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = this->mNestedMaterials.Write(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = this->mPreShaders.Write(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = this->mStaticParameters.Write(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = this->mTextureParams.Write(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = this->mPasses.Write(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        size += stream.Write(&this->mMaterialQuality, sizeof(this->mMaterialQuality));
        err = this->mMaterialBlendModes.Write(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = this->mMaterialPasses.Write(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = this->mMaterialChannels.Write(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = this->mShaderInputs.Write(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = this->mSceneTextures.Write(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = this->mOptionalPropertyTypes.Write(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = this->mPreShaderBuffer.Write(stream);
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
        size += stream.Write(&this->mParameterBufferScalarSize[0], sizeof(this->mParameterBufferScalarSize[0]));
        size += stream.Write(&this->mParameterBufferScalarSize[1], sizeof(this->mParameterBufferScalarSize[1]));
        size += stream.Write(&this->mPreShaderParameterBufferScalarSize, sizeof(this->mPreShaderParameterBufferScalarSize));
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
    class DCArray<struct T3MaterialParameter> mParameters;
    class DCArray<struct T3MaterialTexture> mTextures;
    class DCArray<struct T3MaterialTransform2D> mTransforms;
    class DCArray<struct T3MaterialNestedMaterial> mNestedMaterials;
    class DCArray<struct T3MaterialPreShader> mPreShaders;
    class DCArray<struct T3MaterialStaticParameter> mStaticParameters;
    class DCArray<struct T3MaterialTextureParam> mTextureParams;
    class DCArray<struct T3MaterialPassData> mPasses;
    int32_t mMaterialQuality;
    class BitSetBase<1> mMaterialBlendModes;
    class BitSetBase<1> mMaterialPasses;
    class BitSetBase<2> mMaterialChannels;
    class BitSetBase<3> mShaderInputs;
    class BitSetBase<1> mSceneTextures;
    class BitSetBase<1> mOptionalPropertyTypes;
    class BinaryBuffer mPreShaderBuffer;
    class Flags mFlags;
    uint32_t mParameterBufferScalarSize[2];
    uint32_t mPreShaderParameterBufferScalarSize;
    static constexpr bool IS_BLOCKED = true;
};

struct T3MaterialData
{
  private:
    inline int32_t Read_(Stream &stream)
    {
        int32_t size = 0;
        int32_t err;
        err = this->mMaterialName.Read(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = this->mRuntimePropertiesName.Read(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = this->mLegacyRenderTextureProperty.Read(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = this->mLegacyBlendModeRuntimeProperty.Read(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        size += stream.Read(&this->mDomain, sizeof(this->mDomain));
        err = this->mRuntimeProperties.Read(stream);
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
        size += stream.Read(&this->mVersion, sizeof(this->mVersion));
        err = this->mCompiledData2.Read(stream);
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
        int32_t err;
        err = this->mMaterialName.Write(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = this->mRuntimePropertiesName.Write(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = this->mLegacyRenderTextureProperty.Write(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = this->mLegacyBlendModeRuntimeProperty.Write(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        size += stream.Write(&this->mDomain, sizeof(this->mDomain));
        err = this->mRuntimeProperties.Write(stream);
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
        size += stream.Write(&this->mVersion, sizeof(this->mVersion));
        err = this->mCompiledData2.Write(stream);
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
    Symbol mMaterialName;
    Symbol mRuntimePropertiesName;
    Symbol mLegacyRenderTextureProperty;
    Symbol mLegacyBlendModeRuntimeProperty;
    int32_t mDomain;
    DCArray<T3MaterialRuntimeProperty> mRuntimeProperties;
    Flags mFlags;
    int32_t mVersion;
    DCArray<T3MaterialCompiledData> mCompiledData2;
    static constexpr bool IS_BLOCKED = true;
};

struct T3MeshBatch
{
  private:
    inline int32_t Read_(Stream &stream)
    {
        int32_t size = 0;
        int32_t err;
        err = this->mBoundingBox.Read(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = this->mBoundingSphere.Read(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = this->mBatchUsage.Read(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        size += stream.Read(&this->mMinVertIndex, sizeof(this->mMinVertIndex));
        size += stream.Read(&this->mMaxVertIndex, sizeof(this->mMaxVertIndex));
        size += stream.Read(&this->mBaseIndex, sizeof(this->mBaseIndex));
        size += stream.Read(&this->mStartIndex, sizeof(this->mStartIndex));
        size += stream.Read(&this->mNumPrimitives, sizeof(this->mNumPrimitives));
        size += stream.Read(&this->mNumIndices, sizeof(this->mNumIndices));
        err = this->mTextureIndices.Read(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        size += stream.Read(&this->mMaterialIndex, sizeof(this->mMaterialIndex));
        size += stream.Read(&this->mAdjacencyStartIndex, sizeof(this->mAdjacencyStartIndex));
        return size;
    }
    inline int32_t Write_(Stream &stream) const
    {
        int32_t size = 0;
        int32_t err;
        err = this->mBoundingBox.Write(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = this->mBoundingSphere.Write(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = this->mBatchUsage.Write(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        size += stream.Write(&this->mMinVertIndex, sizeof(this->mMinVertIndex));
        size += stream.Write(&this->mMaxVertIndex, sizeof(this->mMaxVertIndex));
        size += stream.Write(&this->mBaseIndex, sizeof(this->mBaseIndex));
        size += stream.Write(&this->mStartIndex, sizeof(this->mStartIndex));
        size += stream.Write(&this->mNumPrimitives, sizeof(this->mNumPrimitives));
        size += stream.Write(&this->mNumIndices, sizeof(this->mNumIndices));
        err = this->mTextureIndices.Write(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        size += stream.Write(&this->mMaterialIndex, sizeof(this->mMaterialIndex));
        size += stream.Write(&this->mAdjacencyStartIndex, sizeof(this->mAdjacencyStartIndex));
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
    class BoundingBox mBoundingBox;
    class Sphere mBoundingSphere;
    class Flags mBatchUsage;
    uint32_t mMinVertIndex;
    uint32_t mMaxVertIndex;
    uint32_t mBaseIndex;
    uint32_t mStartIndex;
    uint32_t mNumPrimitives;
    uint32_t mNumIndices;
    struct T3MeshTextureIndices mTextureIndices;
    int32_t mMaterialIndex;
    uint32_t mAdjacencyStartIndex;
    static constexpr bool IS_BLOCKED = true;
};

struct T3MeshLOD
{
  private:
    inline int32_t Read_(Stream &stream)
    {
        int32_t size = 0;
        int32_t err;
        err = this->mBatches[0].Read(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = this->mBatches[1].Read(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = this->mVertexStreams.Read(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = this->mBoundingBox.Read(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = this->mBoundingSphere.Read(stream);
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
        size += stream.Read(&this->mVertexStateIndex, sizeof(this->mVertexStateIndex));
        size += stream.Read(&this->mNumPrimitives, sizeof(this->mNumPrimitives));
        size += stream.Read(&this->mNumBatches, sizeof(this->mNumBatches));
        size += stream.Read(&this->mVertexStart, sizeof(this->mVertexStart));
        size += stream.Read(&this->mVertexCount, sizeof(this->mVertexCount));
        size += stream.Read(&this->mTextureAtlasWidth, sizeof(this->mTextureAtlasWidth));
        size += stream.Read(&this->mTextureAtlasHeight, sizeof(this->mTextureAtlasHeight));
        size += stream.Read(&this->mPixelSize, sizeof(this->mPixelSize));
        size += stream.Read(&this->mDistance, sizeof(this->mDistance));
        err = this->mBones.Read(stream);
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
        int32_t err;
        err = this->mBatches[0].Write(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = this->mBatches[1].Write(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = this->mVertexStreams.Write(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = this->mBoundingBox.Write(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = this->mBoundingSphere.Write(stream);
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
        size += stream.Write(&this->mVertexStateIndex, sizeof(this->mVertexStateIndex));
        size += stream.Write(&this->mNumPrimitives, sizeof(this->mNumPrimitives));
        size += stream.Write(&this->mNumBatches, sizeof(this->mNumBatches));
        size += stream.Write(&this->mVertexStart, sizeof(this->mVertexStart));
        size += stream.Write(&this->mVertexCount, sizeof(this->mVertexCount));
        size += stream.Write(&this->mTextureAtlasWidth, sizeof(this->mTextureAtlasWidth));
        size += stream.Write(&this->mTextureAtlasHeight, sizeof(this->mTextureAtlasHeight));
        size += stream.Write(&this->mPixelSize, sizeof(this->mPixelSize));
        size += stream.Write(&this->mDistance, sizeof(this->mDistance));
        err = this->mBones.Write(stream);
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
    class DCArray<struct T3MeshBatch> mBatches[2];
    class BitSetBase<1> mVertexStreams;
    class BoundingBox mBoundingBox;
    class Sphere mBoundingSphere;
    class Flags mFlags;
    uint32_t mVertexStateIndex;
    uint32_t mNumPrimitives;
    uint32_t mNumBatches;
    uint32_t mVertexStart;
    uint32_t mVertexCount;
    uint32_t mTextureAtlasWidth;
    uint32_t mTextureAtlasHeight;
    float mPixelSize;
    float mDistance;
    class DCArray<class Symbol> mBones;
    static constexpr bool IS_BLOCKED = true;
};

struct T3MeshTexCoordTransform
{
  private:
    inline int32_t Read_(Stream &stream)
    {
        int32_t size = 0;
        int32_t err;
        err = this->mScale.Read(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = this->mOffset.Read(stream);
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
        int32_t err;
        err = this->mScale.Write(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = this->mOffset.Write(stream);
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
    Vector2 mScale;
    Vector2 mOffset;
    static constexpr bool IS_BLOCKED = true;
};

struct T3MeshCPUSkinningData
{
  private:
    inline int32_t Read_(Stream &stream)
    {
        int32_t size = stream.Read(&this->mPositionFormat, sizeof(this->mPositionFormat));
        size += stream.Read(&this->mWeightFormat, sizeof(this->mWeightFormat));
        size += stream.Read(&this->mNormalFormat, sizeof(this->mNormalFormat));

        int32_t err = this->mVertexStreams.Read(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;

        size += stream.Read(&this->mNormalCount, sizeof(this->mNormalCount));
        size += stream.Read(&this->mWeightOffset, sizeof(this->mWeightOffset));
        size += stream.Read(&this->mVertexSize, sizeof(this->mVertexSize));
        size += stream.Read(&this->mWeightSize, sizeof(this->mWeightSize));

        err = this->mData.Read(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        return size;
    }
    inline int32_t Write_(Stream &stream) const
    {
        int32_t size = stream.Write(&this->mPositionFormat, sizeof(this->mPositionFormat));
        size += stream.Write(&this->mWeightFormat, sizeof(this->mWeightFormat));
        size += stream.Write(&this->mNormalFormat, sizeof(this->mNormalFormat));

        int32_t err = this->mVertexStreams.Write(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;

        size += stream.Write(&this->mNormalCount, sizeof(this->mNormalCount));
        size += stream.Write(&this->mWeightOffset, sizeof(this->mWeightOffset));
        size += stream.Write(&this->mVertexSize, sizeof(this->mVertexSize));
        size += stream.Write(&this->mWeightSize, sizeof(this->mWeightSize));

        err = this->mData.Write(stream);
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
    int32_t mPositionFormat;
    int32_t mWeightFormat;
    int32_t mNormalFormat;
    BitSetBase<1> mVertexStreams;
    uint32_t mNormalCount;
    uint32_t mWeightOffset;
    uint32_t mVertexSize;
    uint32_t mWeightSize;
    BinaryBuffer mData;
    static constexpr bool IS_BLOCKED = true;
};

struct T3MeshData
{
  private:
    inline int32_t Read_(Stream &stream)
    {
        int32_t size = 0;
        int32_t err;
        err = this->mLODs.Read(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = this->mTextures.Read(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = this->mMaterials.Read(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = this->mMaterialOverrides.Read(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = this->mBones.Read(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = this->mLocalTransforms.Read(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = this->mMaterialRequirements.Read(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = this->mVertexStreams.Read(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = this->mBoundingBox.Read(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = this->mBoundingSphere.Read(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        size += stream.Read(&this->mEndianType, sizeof(this->mEndianType));
        err = this->mPositionScale.Read(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = this->mPositionWScale.Read(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = this->mPositionOffset.Read(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        size += stream.Read(&this->mLightmapTexelAreaPerSurfaceArea, sizeof(this->mLightmapTexelAreaPerSurfaceArea));
        err = this->mPropertyKeyBase.Read(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        size += stream.Read(&this->mVertexCount, sizeof(this->mVertexCount));
        err = this->mFlags.Read(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = this->mMeshPreload.Read(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;

        uint32_t texCoordCount;
        size += stream.Read(&texCoordCount, sizeof(texCoordCount));
        while (texCoordCount--)
        {
            uint32_t texCoordIndex;
            size += stream.Read(&texCoordIndex, sizeof(texCoordIndex));
            size += this->mTexCoordTransform[texCoordIndex].Read(stream);
        }

        if (this->mFlags.mFlags & eHasCPUSkinning)
        {
            T3MeshCPUSkinningData *mpCPUSkinningData = new T3MeshCPUSkinningData();
            size += mpCPUSkinningData->Read(stream);
        }

        size += mVertexStates.Read(stream, false);

        return size;
    }
    inline int32_t Write_(Stream &stream) const // TODO: Implement
    {
        int32_t size = 0;
        int32_t err;
        err = this->mLODs.Write(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = this->mTextures.Write(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = this->mMaterials.Write(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = this->mMaterialOverrides.Write(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = this->mBones.Write(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = this->mLocalTransforms.Write(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = this->mMaterialRequirements.Write(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = this->mVertexStreams.Write(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = this->mBoundingBox.Write(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = this->mBoundingSphere.Write(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        size += stream.Write(&this->mEndianType, sizeof(this->mEndianType));
        err = this->mPositionScale.Write(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = this->mPositionWScale.Write(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = this->mPositionOffset.Write(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        size += stream.Write(&this->mLightmapTexelAreaPerSurfaceArea, sizeof(this->mLightmapTexelAreaPerSurfaceArea));
        err = this->mPropertyKeyBase.Write(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        size += stream.Write(&this->mVertexCount, sizeof(this->mVertexCount));
        err = this->mFlags.Write(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = this->mMeshPreload.Write(stream);
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
    enum MeshFlags // T3MeshData
    {
        eDeformable = 0x1,
        eHasLocalCameraFacing = 0x2,
        eHasLocalCameraFacingY = 0x4,
        eHasLocalCameraFacingLocalY = 0x8,
        eHasCPUSkinning = 0x10,
        eHasComputeSkinning = 0x20
    };

    T3MeshData()
        : mLODs(DCArray<T3MeshLOD>()), mTextures(DCArray<T3MeshTexture>()), mMaterials(DCArray<T3MeshMaterial>()), mBones(DCArray<T3MeshBoneEntry>()),
          mLocalTransforms(DCArray<T3MeshLocalTransformEntry>()), mMaterialRequirements(T3MaterialRequirements()), mVertexStreams(BitSetBase<1>()), mBoundingBox(BoundingBox()),
          mBoundingSphere(Sphere()), mEndianType(-1), mPositionScale(Vector3()), mPositionWScale(Vector3()), mPositionOffset(Vector3()), mLightmapTexelAreaPerSurfaceArea(0.0f),
          mPropertyKeyBase(Symbol()), mVertexCount(0), mFlags(Flags()), mMeshPreload(DCArray<T3MeshEffectPreload>()), mpCPUSkinningData(nullptr), mVertexStates(DCArray<T3GFXVertexState>())
    {
    }

    ~T3MeshData() { delete mpCPUSkinningData; }

    DCArray<T3MeshLOD> mLODs;
    DCArray<T3MeshTexture> mTextures;
    DCArray<T3MeshMaterial> mMaterials;
    DCArray<T3MeshMaterialOverride> mMaterialOverrides;
    DCArray<T3MeshBoneEntry> mBones;
    DCArray<T3MeshLocalTransformEntry> mLocalTransforms;
    T3MaterialRequirements mMaterialRequirements;
    BitSetBase<1> mVertexStreams;
    BoundingBox mBoundingBox;
    Sphere mBoundingSphere;
    int32_t mEndianType;
    Vector3 mPositionScale;
    Vector3 mPositionWScale;
    Vector3 mPositionOffset;
    float mLightmapTexelAreaPerSurfaceArea;
    Symbol mPropertyKeyBase;
    uint32_t mVertexCount;
    Flags mFlags; // check MeshFlags above
    DCArray<T3MeshEffectPreload> mMeshPreload;

    T3MeshTexCoordTransform mTexCoordTransform[4];
    T3MeshCPUSkinningData *mpCPUSkinningData;
    DCArray<T3GFXVertexState> mVertexStates;

    static constexpr bool IS_BLOCKED = true;
};

struct T3OcclusionMeshBatch
{
  private:
    inline int32_t Read_(Stream &stream)
    {
        int32_t size = 0;
        int32_t err;
        err = this->mFlags.Read(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        size += stream.Read(&this->mStartIndex, sizeof(this->mStartIndex));
        size += stream.Read(&this->mNumTriangles, sizeof(this->mNumTriangles));
        return size;
    }
    inline int32_t Write_(Stream &stream) const
    {
        int32_t size = 0;
        int32_t err;
        err = this->mFlags.Write(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        size += stream.Write(&this->mStartIndex, sizeof(this->mStartIndex));
        size += stream.Write(&this->mNumTriangles, sizeof(this->mNumTriangles));
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
    Flags mFlags;
    uint32_t mStartIndex;
    uint32_t mNumTriangles;
    static constexpr bool IS_BLOCKED = true;
};

struct T3OcclusionMeshData
{
  private:
    inline int32_t Read_(Stream &stream)
    {
        int32_t size = 0;
        int32_t err;
        err = this->mData.Read(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = this->mBoundingBox.Read(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = this->mBoundingSphere.Read(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = this->mBatches.Read(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        size += stream.Read(&this->mVertexCount, sizeof(this->mVertexCount));
        return size;
    }
    inline int32_t Write_(Stream &stream) const
    {
        int32_t size = 0;
        int32_t err;
        err = this->mData.Write(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = this->mBoundingBox.Write(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = this->mBoundingSphere.Write(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = this->mBatches.Write(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        size += stream.Write(&this->mVertexCount, sizeof(this->mVertexCount));
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
    class BinaryBuffer mData;
    class BoundingBox mBoundingBox;
    class Sphere mBoundingSphere;
    class DCArray<struct T3OcclusionMeshBatch> mBatches;
    uint32_t mVertexCount;
    static constexpr bool IS_BLOCKED = false;
};

class D3DMesh
{
  private:
    inline int32_t Read_(Stream &stream)
    {
        int32_t size = 0;
        int32_t err;
        err = this->mName.Read(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        TTH_LOG_INFO("%s\n", this->mName.c_str());

        size += stream.Read(&this->mVersion, sizeof(this->mVersion));
        err = this->mToolProps.Read(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        size += stream.Read(&this->mLightmapGlobalScale, sizeof(this->mLightmapGlobalScale));
        size += stream.Read(&this->mLightmapTexCoordVersion, sizeof(this->mLightmapTexCoordVersion));
        size += stream.Read(&this->mLODParamCRC, sizeof(this->mLODParamCRC));

        size += stream.Read(&this->mAsyncResourceCount, sizeof(this->mAsyncResourceCount));
        this->mAsyncResources = new AsyncResource[mAsyncResourceCount];
        for (uint32_t i = 0; i < mAsyncResourceCount; ++i)
        {
            mAsyncResources[i].nameHash.Read(stream);
            mAsyncResources[i].typeHash.Read(stream);
            mAsyncResources[i].resource = Any(mAsyncResources[i].typeHash.mCrc64);
            mAsyncResources[i].resource.Read(stream);
        }

        size += stream.Read(&this->unknown, sizeof(this->unknown));
        char isOcclusionMeshData;
        size += stream.Read(&isOcclusionMeshData, sizeof(isOcclusionMeshData));
        if (isOcclusionMeshData == '1')
        {
            this->mpOcclusionMeshData = new T3OcclusionMeshData();
            size += this->mpOcclusionMeshData->Read(stream, true);
        }
        else
        {
            this->mpOcclusionMeshData = nullptr;
        }

        size += this->mMeshData.Read(stream);

        size_t startOfAsync = stream.tell();
        stream.Seek(0, stream.END);
        this->asyncSize = stream.tell() - startOfAsync;
        stream.Seek(startOfAsync, stream.SET);

        this->async = new uint8_t[this->asyncSize];
        size += stream.Read(this->async, this->asyncSize);

        return size;
    }
    inline int32_t Write_(Stream &stream) const // TODO: Implement
    {
        int32_t size = 0;
        int32_t err;
        err = this->mName.Write(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        size += stream.Write(&this->mVersion, sizeof(this->mVersion));
        err = this->mToolProps.Write(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        size += stream.Write(&this->mLightmapGlobalScale, sizeof(this->mLightmapGlobalScale));
        size += stream.Write(&this->mLightmapTexCoordVersion, sizeof(this->mLightmapTexCoordVersion));
        size += stream.Write(&this->mLODParamCRC, sizeof(this->mLODParamCRC));

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

    struct AsyncResource
    {
        Symbol nameHash;
        Symbol typeHash;
        Any resource;

        AsyncResource() : nameHash(Symbol()), typeHash(Symbol()), resource(Any()) {}
    };

    D3DMesh()
        : mName(String()), mVersion(-1), mToolProps(ToolProps()), mLightmapGlobalScale(0.0f), mLightmapTexCoordVersion(-1), mLODParamCRC(0), mAsyncResourceCount(0), mAsyncResources(nullptr),
          unknown(0), mpOcclusionMeshData(nullptr), mMeshData(T3MeshData()), asyncSize(0), async(nullptr)
    {
    }

    ~D3DMesh()
    {
        delete[] mAsyncResources;
        delete mpOcclusionMeshData;
        delete[] async;
    }

    class String mName;
    int32_t mVersion;
    class ToolProps mToolProps;
    float mLightmapGlobalScale;
    int32_t mLightmapTexCoordVersion;
    uint64_t mLODParamCRC;

    uint32_t mAsyncResourceCount;
    AsyncResource *mAsyncResources;
    int32_t unknown;
    T3OcclusionMeshData *mpOcclusionMeshData;
    T3MeshData mMeshData;
    size_t asyncSize;
    uint8_t *async;
    static constexpr bool IS_BLOCKED = true;
};

} // namespace TTH