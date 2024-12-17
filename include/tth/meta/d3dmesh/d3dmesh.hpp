#pragma once

#include <tth/core/any.hpp>
#include <tth/meta/bitset/base.hpp>
#include <tth/meta/container/dcarray.hpp>
#include <tth/meta/crc64/symbol.hpp>
#include <tth/meta/flags.hpp>
#include <tth/meta/handle/handle.hpp>
#include <tth/meta/linalg/transform.hpp>
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
    ~BinaryBuffer() { delete data; }
    BinaryBuffer() : mDataSize(0), data(nullptr) {}

    int32_t mDataSize;
    uint8_t *data;
    static constexpr bool IS_BLOCKED = true;
};

struct T3MeshTextureIndices
{
  private:
    inline int32_t Read_(Stream &stream)
    {
        int32_t size = 0;
        int32_t err;
        return size;
    }
    inline int32_t Write_(Stream &stream) const
    {
        int32_t size = 0;
        int32_t err;
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
    static constexpr bool IS_BLOCKED = false;
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
        int32_t size = 0;
        int32_t err;
        size += stream.Read(&this->mIndirectReflectivity, sizeof(this->mIndirectReflectivity));
        size += stream.Read(&this->mIndirectTransparency, sizeof(this->mIndirectTransparency));
        return size;
    }
    inline int32_t Write_(Stream &stream) const
    {
        int32_t size = 0;
        int32_t err;
        size += stream.Write(&this->mIndirectReflectivity, sizeof(this->mIndirectReflectivity));
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
        int32_t size = 0;
        int32_t err;
        size += stream.Read(&this->mResourceUsage, sizeof(this->mResourceUsage));
        size += stream.Read(&this->mBufferFormat, sizeof(this->mBufferFormat));
        size += stream.Read(&this->mBufferUsage, sizeof(this->mBufferUsage));
        size += stream.Read(&this->mCount, sizeof(this->mCount));
        size += stream.Read(&this->mStride, sizeof(this->mStride));
        return size;
    }
    inline int32_t Write_(Stream &stream) const
    {
        int32_t size = 0;
        int32_t err;
        size += stream.Write(&this->mResourceUsage, sizeof(this->mResourceUsage));
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
        int32_t size = 0;
        int32_t err;
        size += stream.Read(&this->mAttribute, sizeof(this->mAttribute));
        size += stream.Read(&this->mFormat, sizeof(this->mFormat));
        size += stream.Read(&this->mAttributeIndex, sizeof(this->mAttributeIndex));
        size += stream.Read(&this->mBufferIndex, sizeof(this->mBufferIndex));
        size += stream.Read(&this->mBufferOffset, sizeof(this->mBufferOffset));
        return size;
    }
    inline int32_t Write_(Stream &stream) const
    {
        int32_t size = 0;
        int32_t err;
        size += stream.Write(&this->mAttribute, sizeof(this->mAttribute));
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
        int32_t size = 0;
        int32_t err;
        size += stream.Read(&this->mVertexCountPerInstance, sizeof(this->mVertexCountPerInstance));
        size += stream.Read(&this->mIndexBufferCount, sizeof(this->mIndexBufferCount));
        size += stream.Read(&this->mVertexBufferCount, sizeof(this->mVertexBufferCount));
        size += stream.Read(&this->mAttributeCount, sizeof(this->mAttributeCount));
        return size;
    }
    inline int32_t Write_(Stream &stream) const
    {
        int32_t size = 0;
        int32_t err;
        size += stream.Write(&this->mVertexCountPerInstance, sizeof(this->mVertexCountPerInstance));
        size += stream.Write(&this->mIndexBufferCount, sizeof(this->mIndexBufferCount));
        size += stream.Write(&this->mVertexBufferCount, sizeof(this->mVertexBufferCount));
        size += stream.Write(&this->mAttributeCount, sizeof(this->mAttributeCount));
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
        int32_t size = 0;
        int32_t err;
        size += stream.Read(&this->mPassType, sizeof(this->mPassType));
        size += stream.Read(&this->mBlendMode, sizeof(this->mBlendMode));
        size += stream.Read(&this->mMaterialCrc, sizeof(this->mMaterialCrc));
        return size;
    }
    inline int32_t Write_(Stream &stream) const
    {
        int32_t size = 0;
        int32_t err;
        size += stream.Write(&this->mPassType, sizeof(this->mPassType));
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
        int32_t size = 0;
        int32_t err;
        size += stream.Read(&this->mValueType, sizeof(this->mValueType));
        size += stream.Read(&this->mFlags, sizeof(this->mFlags));
        size += stream.Read(&this->mPreShaderOffset, sizeof(this->mPreShaderOffset));
        size += stream.Read(&this->mScalarParameterOffset, sizeof(this->mScalarParameterOffset));
        return size;
    }
    inline int32_t Write_(Stream &stream) const
    {
        int32_t size = 0;
        int32_t err;
        size += stream.Write(&this->mValueType, sizeof(this->mValueType));
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
    uint32_t mParameterBufferScalarSize[0];
    uint32_t mParameterBufferScalarSize[1];
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
    class Symbol mMaterialName;
    class Symbol mRuntimePropertiesName;
    class Symbol mLegacyRenderTextureProperty;
    class Symbol mLegacyBlendModeRuntimeProperty;
    int32_t mDomain;
    class DCArray<struct T3MaterialRuntimeProperty> mRuntimeProperties;
    class Flags mFlags;
    int32_t mVersion;
    class DCArray<struct T3MaterialCompiledData> mCompiledData2;
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
    class DCArray<struct T3MeshBatch> mBatches[0];
    class DCArray<struct T3MeshBatch> mBatches[1];
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
        return size;
    }
    inline int32_t Write_(Stream &stream) const
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
    class DCArray<struct T3MeshLOD> mLODs;
    class DCArray<struct T3MeshTexture> mTextures;
    class DCArray<struct T3MeshMaterial> mMaterials;
    class DCArray<struct T3MeshMaterialOverride> mMaterialOverrides;
    class DCArray<struct T3MeshBoneEntry> mBones;
    class DCArray<struct T3MeshLocalTransformEntry> mLocalTransforms;
    struct T3MaterialRequirements mMaterialRequirements;
    class BitSetBase<1> mVertexStreams;
    class BoundingBox mBoundingBox;
    class Sphere mBoundingSphere;
    int32_t mEndianType;
    class Vector3 mPositionScale;
    class Vector3 mPositionWScale;
    class Vector3 mPositionOffset;
    float mLightmapTexelAreaPerSurfaceArea;
    class Symbol mPropertyKeyBase;
    uint32_t mVertexCount;
    class Flags mFlags;
    class DCArray<struct T3MeshEffectPreload> mMeshPreload;
    static constexpr bool IS_BLOCKED = true;
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
        uint64_t typeHash;
        Any resource;
    };

    class String mName;
    int32_t mVersion;
    class ToolProps mToolProps;
    float mLightmapGlobalScale;
    int32_t mLightmapTexCoordVersion;
    uint64_t mLODParamCRC;
    static constexpr bool IS_BLOCKED = true;
};

} // namespace TTH