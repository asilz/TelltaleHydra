#pragma once

#include <tth/container/dcarray.hpp>
#include <tth/core/any.hpp>
#include <tth/d3dmesh/d3dmesh.hpp>
#include <tth/flags.hpp>
#include <tth/handle.hpp>
#include <tth/linalg/vector.hpp>
#include <tth/prop/prop.hpp>
#include <tth/stream/stream.hpp>
#include <tth/string.hpp>
#include <tth/toolprops.hpp>

namespace TTH
{
class BinaryBuffer
{
  public:
    int32_t Read(Stream &stream)
    {
        int32_t size = 0;
        int32_t err = stream.Read(mDataSize);
        if (err < 0)
        {
            return err;
        }
        size += err;

        delete[] data;
        data = new uint8_t[mDataSize];

        err = stream.Read((void *)data, mDataSize);
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
        int32_t err = stream.Write(mDataSize);
        if (err < 0)
        {
            return err;
        }
        size += err;

        err = stream.Write((const void *)data, mDataSize);
        if (err < 0)
        {
            return err;
        }
        size += err;
        return size;
    }
    int32_t mDataSize;
    uint8_t *data;
    static constexpr bool IS_BLOCKED = true;

    ~BinaryBuffer() { delete[] data; }
    BinaryBuffer() : mDataSize(0), data(nullptr) {}
    static constexpr uint64_t GetTypeCRC64() { return CRC64_CaseInsensitive("BinaryBuffer"); }
};
class Sphere
{
  public:
    int32_t Read(Stream &stream)
    {
        int32_t size = 0;
        int32_t err;
        err = stream.Read(mCenter);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Read(mRadius);
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
        int32_t err;
        err = stream.Write(mCenter);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Write(mRadius);
        if (err < 0)
        {
            return err;
        }
        size += err;
        return size;
    }
    class Vector3 mCenter;
    float mRadius;
    static constexpr bool IS_BLOCKED = true;
    static constexpr uint64_t GetTypeCRC64() { return CRC64_CaseInsensitive("Sphere"); }
};
class BoundingBox
{
  public:
    int32_t Read(Stream &stream)
    {
        int32_t size = 0;
        int32_t err;
        err = stream.Read(mMin);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Read(mMax);
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
        int32_t err;
        err = stream.Write(mMin);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Write(mMax);
        if (err < 0)
        {
            return err;
        }
        size += err;
        return size;
    }
    class Vector3 mMin;
    class Vector3 mMax;
    static constexpr bool IS_BLOCKED = false;
    static constexpr uint64_t GetTypeCRC64() { return CRC64_CaseInsensitive("BoundingBox"); }
};
struct T3MaterialEnlightenPrecomputeParams
{
  public:
    int32_t Read(Stream &stream)
    {
        int32_t size = 0;
        int32_t err;
        err = stream.Read(mIndirectReflectivity);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Read(mIndirectTransparency);
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
        int32_t err;
        err = stream.Write(mIndirectReflectivity);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Write(mIndirectTransparency);
        if (err < 0)
        {
            return err;
        }
        size += err;
        return size;
    }
    float mIndirectReflectivity;
    float mIndirectTransparency;
    static constexpr bool IS_BLOCKED = true;
    static constexpr uint64_t GetTypeCRC64() { return CRC64_CaseInsensitive("T3MaterialEnlightenPrecomputeParams"); }
};
struct T3MaterialPassData
{
  public:
    int32_t Read(Stream &stream)
    {
        int32_t size = 0;
        int32_t err;
        err = stream.Read(mPassType);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Read(mBlendMode);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Read(mMaterialCrc);
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
        int32_t err;
        err = stream.Write(mPassType);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Write(mBlendMode);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Write(mMaterialCrc);
        if (err < 0)
        {
            return err;
        }
        size += err;
        return size;
    }
    int32_t mPassType;
    int32_t mBlendMode;
    uint64_t mMaterialCrc;
    static constexpr bool IS_BLOCKED = true;
    static constexpr uint64_t GetTypeCRC64() { return CRC64_CaseInsensitive("T3MaterialPassData"); }
};
struct T3MaterialStaticParameter
{
  public:
    int32_t Read(Stream &stream)
    {
        int32_t size = 0;
        int32_t err;
        err = stream.Read(mName);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Read(mNestedMaterialIndex);
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
        int32_t err;
        err = stream.Write(mName);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Write(mNestedMaterialIndex);
        if (err < 0)
        {
            return err;
        }
        size += err;
        return size;
    }
    class Symbol mName;
    int32_t mNestedMaterialIndex;
    static constexpr bool IS_BLOCKED = true;
    static constexpr uint64_t GetTypeCRC64() { return CRC64_CaseInsensitive("T3MaterialStaticParameter"); }
};
struct T3MaterialPreShader
{
  public:
    int32_t Read(Stream &stream)
    {
        int32_t size = 0;
        int32_t err;
        err = stream.Read(mValueType);
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
        err = stream.Read(mPreShaderOffset);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Read(mScalarParameterOffset);
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
        int32_t err;
        err = stream.Write(mValueType);
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
        err = stream.Write(mPreShaderOffset);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Write(mScalarParameterOffset);
        if (err < 0)
        {
            return err;
        }
        size += err;
        return size;
    }
    int32_t mValueType;
    uint32_t mFlags;
    int32_t mPreShaderOffset;
    int32_t mScalarParameterOffset;
    static constexpr bool IS_BLOCKED = true;
    static constexpr uint64_t GetTypeCRC64() { return CRC64_CaseInsensitive("T3MaterialPreShader"); }
};
struct T3MaterialTransform2D
{
  public:
    int32_t Read(Stream &stream)
    {
        int32_t size = 0;
        int32_t err;
        err = stream.Read(mParameterPrefix);
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
        err = stream.Read(mScalarOffset0);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Read(mScalarOffset1);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Read(mPreShaderScalarOffset0);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Read(mPreShaderScalarOffset1);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Read(mNestedMaterialIndex);
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
        int32_t err;
        err = stream.Write(mParameterPrefix);
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
        err = stream.Write(mScalarOffset0);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Write(mScalarOffset1);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Write(mPreShaderScalarOffset0);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Write(mPreShaderScalarOffset1);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Write(mNestedMaterialIndex);
        if (err < 0)
        {
            return err;
        }
        size += err;
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
    static constexpr uint64_t GetTypeCRC64() { return CRC64_CaseInsensitive("T3MaterialTransform2D"); }
};
struct T3MaterialTexture
{
  public:
    int32_t Read(Stream &stream)
    {
        int32_t size = 0;
        int32_t err;
        err = stream.Read(mName);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Read(mTextureName);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Read(mTextureNameWithoutExtension);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Read(mPropertyType);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Read(mTextureTypes);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Read(mFirstParamIndex);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Read(mParamCount);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Read(mTextureIndex);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Read(mNestedMaterialIndex);
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
        int32_t err;
        err = stream.Write(mName);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Write(mTextureName);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Write(mTextureNameWithoutExtension);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Write(mPropertyType);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Write(mTextureTypes);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Write(mFirstParamIndex);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Write(mParamCount);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Write(mTextureIndex);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Write(mNestedMaterialIndex);
        if (err < 0)
        {
            return err;
        }
        size += err;
        return size;
    }
    class Symbol mName;
    class Symbol mTextureName;
    class Symbol mTextureNameWithoutExtension;
    int32_t mPropertyType;
    class BitSetBase<1> mTextureTypes;
    uint32_t mFirstParamIndex;
    uint32_t mParamCount;
    int32_t mTextureIndex;
    int32_t mNestedMaterialIndex;
    static constexpr bool IS_BLOCKED = true;
    static constexpr uint64_t GetTypeCRC64() { return CRC64_CaseInsensitive("T3MaterialTexture"); }
};
struct T3MaterialParameter
{
  public:
    int32_t Read(Stream &stream)
    {
        int32_t size = 0;
        int32_t err;
        err = stream.Read(mName);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Read(mPropertyType);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Read(mValueType);
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
        err = stream.Read(mScalarOffset);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Read(mPreShaderScalarOffset);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Read(mNestedMaterialIndex);
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
        int32_t err;
        err = stream.Write(mName);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Write(mPropertyType);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Write(mValueType);
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
        err = stream.Write(mScalarOffset);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Write(mPreShaderScalarOffset);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Write(mNestedMaterialIndex);
        if (err < 0)
        {
            return err;
        }
        size += err;
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
    static constexpr uint64_t GetTypeCRC64() { return CRC64_CaseInsensitive("T3MaterialParameter"); }
};
struct T3MaterialTextureParam
{
  public:
    int32_t Read(Stream &stream)
    {
        int32_t size = 0;
        int32_t err;
        err = stream.Read(mParamType);
        if (err < 0)
        {
            return err;
        }
        size += err;

        err = stream.Read(mValueType);
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
        err = stream.Read(mScalarOffset);
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
        int32_t err;
        err = stream.Write(mParamType);
        if (err < 0)
        {
            return err;
        }
        size += err;

        err = stream.Write(mValueType);
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
        err = stream.Write(mScalarOffset);
        if (err < 0)
        {
            return err;
        }
        size += err;
        return size;
    }

    int32_t mParamType;
    int32_t mValueType;
    uint32_t mFlags; // Why are these not Flags?
    int32_t mScalarOffset;
    static constexpr bool IS_BLOCKED = true;
    static constexpr uint64_t GetTypeCRC64() { return CRC64_CaseInsensitive("T3MaterialTextureParam"); }
};
struct T3MaterialNestedMaterial
{
  public:
    int32_t Read(Stream &stream) { return stream.Read(mhMaterial); }
    int32_t Write(Stream &stream) const { return stream.Write(mhMaterial); }

    Handle<PropertySet> mhMaterial; // TODO: Change to Handle<PropertySet>
    static constexpr bool IS_BLOCKED = true;
    static constexpr uint64_t GetTypeCRC64() { return CRC64_CaseInsensitive("T3MaterialNestedMaterial"); }
};
struct T3MaterialCompiledData
{
  public:
    int32_t Read(Stream &stream)
    {
        int32_t size = 0;
        int32_t err;
        err = stream.Read(mParameters);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Read(mTextures);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Read(mTransforms);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Read(mNestedMaterials);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Read(mPreShaders);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Read(mStaticParameters);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Read(mTextureParams);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Read(mPasses);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Read(mMaterialBlendModes);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Read(mMaterialPasses);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Read(mMaterialChannels);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Read(mShaderInputs);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Read(mOptionalPropertyTypes);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Read(mPreShaderBuffer);
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
        err = stream.Read(mParameterBufferScalarSize[0]);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Read(mParameterBufferScalarSize[1]);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Read(mPreShaderParameterBufferScalarSize);
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
        int32_t err;
        err = stream.Write(mParameters);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Write(mTextures);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Write(mTransforms);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Write(mNestedMaterials);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Write(mPreShaders);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Write(mStaticParameters);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Write(mTextureParams);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Write(mPasses);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Write(mMaterialBlendModes);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Write(mMaterialPasses);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Write(mMaterialChannels);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Write(mShaderInputs);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Write(mOptionalPropertyTypes);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Write(mPreShaderBuffer);
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
        err = stream.Write(mParameterBufferScalarSize[0]);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Write(mParameterBufferScalarSize[1]);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Write(mPreShaderParameterBufferScalarSize);
        if (err < 0)
        {
            return err;
        }
        size += err;
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
    class BitSetBase<1> mMaterialBlendModes;
    class BitSetBase<1> mMaterialPasses;
    class BitSetBase<2> mMaterialChannels;
    class BitSetBase<2> mShaderInputs;
    class BitSetBase<1> mOptionalPropertyTypes;
    class BinaryBuffer mPreShaderBuffer;
    class Flags mFlags;
    uint32_t mParameterBufferScalarSize[2];
    uint32_t mPreShaderParameterBufferScalarSize;
    static constexpr bool IS_BLOCKED = true;
    static constexpr uint64_t GetTypeCRC64() { return CRC64_CaseInsensitive("T3MaterialCompiledData"); }
};
struct T3MaterialRuntimeProperty
{
  public:
    int32_t Read(Stream &stream)
    {
        int32_t size = 0;
        int32_t err;
        err = stream.Read(mName);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Read(mRuntimeName);
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
        int32_t err;
        err = stream.Write(mName);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Write(mRuntimeName);
        if (err < 0)
        {
            return err;
        }
        size += err;
        return size;
    }
    class Symbol mName;
    class Symbol mRuntimeName;
    static constexpr bool IS_BLOCKED = true;
    static constexpr uint64_t GetTypeCRC64() { return CRC64_CaseInsensitive("T3MaterialRuntimeProperty"); }
};
struct T3GFXBuffer
{
  public:
    int32_t Read(Stream &stream)
    {
        int32_t size = 0;
        int32_t err;
        err = stream.Read(mResourceUsage);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Read(mBufferFormat);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Read(mBufferUsage);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Read(mCount);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Read(mStride);
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
        int32_t err;
        err = stream.Write(mResourceUsage);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Write(mBufferFormat);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Write(mBufferUsage);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Write(mCount);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Write(mStride);
        if (err < 0)
        {
            return err;
        }
        size += err;
        return size;
    }
    int32_t mResourceUsage;
    int32_t mBufferFormat;
    uint32_t mBufferUsage;
    uint32_t mCount;
    uint32_t mStride;
    static constexpr bool IS_BLOCKED = true;
    static constexpr uint64_t GetTypeCRC64() { return CRC64_CaseInsensitive("T3GFXBuffer"); }
};
struct GFXPlatformAttributeParams
{
  public:
    int32_t Read(Stream &stream)
    {
        int32_t size = 0;
        int32_t err;
        err = stream.Read(mAttribute);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Read(mFormat);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Read(mAttributeIndex);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Read(mBufferIndex);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Read(mBufferOffset);
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
        int32_t err;
        err = stream.Write(mAttribute);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Write(mFormat);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Write(mAttributeIndex);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Write(mBufferIndex);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Write(mBufferOffset);
        if (err < 0)
        {
            return err;
        }
        size += err;
        return size;
    }
    int32_t mAttribute;
    int32_t mFormat;
    uint32_t mAttributeIndex;
    uint32_t mBufferIndex;
    uint32_t mBufferOffset;
    static constexpr bool IS_BLOCKED = true;
    static constexpr uint64_t GetTypeCRC64() { return CRC64_CaseInsensitive("GFXPlatformAttributeParams"); }
};
struct T3GFXVertexState
{
  public:
    int32_t Read(Stream &stream)
    {
        int32_t size = 0;
        int32_t err;
        err = stream.Read(mVertexCountPerInstance);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Read(mIndexBufferCount);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Read(mVertexBufferCount);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Read(mAttributeCount);
        if (err < 0)
        {
            return err;
        }
        size += err;

        for (uint32_t i = 0; i < mAttributeCount; ++i)
        {
            err = stream.Read(mAttributes[i], false);
            if (err < 0)
            {
                return err;
            }
            size += err;
        }

        for (uint32_t i = 0; i < mIndexBufferCount; ++i)
        {
            err = stream.Read(mpIndexBuffer[i], false);
            if (err < 0)
            {
                return err;
            }
            size += err;
        }
        for (uint32_t i = 0; i < mVertexBufferCount; ++i)
        {
            err = stream.Read(mpVertexBuffer[i], false);
            if (err < 0)
            {
                return err;
            }
            size += err;
        }

        return size;
    }
    int32_t Write(Stream &stream) const
    {
        int32_t size = 0;
        int32_t err;
        err = stream.Write(mVertexCountPerInstance);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Write(mIndexBufferCount);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Write(mVertexBufferCount);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Write(mAttributeCount);
        if (err < 0)
        {
            return err;
        }
        size += err;

        for (uint32_t i = 0; i < mAttributeCount; ++i)
        {
            err = stream.Write(mAttributes[i], false);
            if (err < 0)
            {
                return err;
            }
            size += err;
        }

        for (uint32_t i = 0; i < mIndexBufferCount; ++i)
        {
            err = stream.Write(mpIndexBuffer[i], false);
            if (err < 0)
            {
                return err;
            }
            size += err;
        }
        for (uint32_t i = 0; i < mVertexBufferCount; ++i)
        {
            err = stream.Write(mpVertexBuffer[i], false);
            if (err < 0)
            {
                return err;
            }
            size += err;
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
    static constexpr uint64_t GetTypeCRC64() { return CRC64_CaseInsensitive("T3GFXVertexState"); }
};
struct T3MeshTexCoordTransform
{
  public:
    int32_t Read(Stream &stream)
    {
        int32_t size = 0;
        int32_t err;
        err = stream.Read(mScale);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Read(mOffset);
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
        int32_t err;
        err = stream.Write(mScale);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Write(mOffset);
        if (err < 0)
        {
            return err;
        }
        size += err;
        return size;
    }
    class Vector2 mScale;
    class Vector2 mOffset;
    static constexpr bool IS_BLOCKED = true;
    static constexpr uint64_t GetTypeCRC64() { return CRC64_CaseInsensitive("T3MeshTexCoordTransform"); }
};
struct T3MaterialRequirements
{
  public:
    int32_t Read(Stream &stream)
    {
        int32_t size = 0;
        int32_t err;
        err = stream.Read(mPasses);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Read(mChannels);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Read(mInputs);
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
        int32_t err;
        err = stream.Write(mPasses);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Write(mChannels);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Write(mInputs);
        if (err < 0)
        {
            return err;
        }
        size += err;
        return size;
    }
    class BitSetBase<1> mPasses;
    class BitSetBase<2> mChannels;
    class BitSetBase<2> mInputs;
    static constexpr bool IS_BLOCKED = true;
    static constexpr uint64_t GetTypeCRC64() { return CRC64_CaseInsensitive("T3MaterialRequirements"); }
};
struct T3MeshMaterial
{
  public:
    int32_t Read(Stream &stream)
    {
        int32_t size = 0;
        int32_t err;
        err = stream.Read(mhMaterial);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Read(mBaseMaterialName);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Read(mLegacyRenderTextureProperty);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Read(mBoundingBox);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Read(mBoundingSphere);
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
    int32_t Write(Stream &stream) const
    {
        int32_t size = 0;
        int32_t err;
        err = stream.Write(mhMaterial);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Write(mBaseMaterialName);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Write(mLegacyRenderTextureProperty);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Write(mBoundingBox);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Write(mBoundingSphere);
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
    class Handle<class PropertySet> mhMaterial;
    class Symbol mBaseMaterialName;
    class Symbol mLegacyRenderTextureProperty;
    class BoundingBox mBoundingBox;
    class Sphere mBoundingSphere;
    class Flags mFlags;
    static constexpr bool IS_BLOCKED = true;
    static constexpr uint64_t GetTypeCRC64() { return CRC64_CaseInsensitive("T3MeshMaterial"); }
};

struct T3MeshTextureIndices
{
  public:
    int32_t Read(Stream &stream)
    {
        int32_t size = 0;
        do
        {
            uint32_t index;
            size += stream.Read(index);
            if (index == 0xffffffff)
            {
                break;
            }
            int32_t value;
            size += stream.Read(value);
            if (index < 2)
            {
                mIndex[index] = value;
            }
        } while (1);
        return size;
    }
    int32_t Write(Stream &stream) const
    {
        int32_t size = 0;
        for (uint32_t i = 0; i < sizeof(mIndex) / sizeof(mIndex[0]); ++i)
        {
            if (mIndex[i] > -1)
            {
                size += stream.Write(i);
                size += stream.Write(mIndex[i]);
            }
        }
        size += stream.Write((const void *)("\xff\xff\xff\xff"), sizeof(uint32_t));
        return size;
    }

    int32_t mIndex[2];
    static constexpr bool IS_BLOCKED = true;
    static constexpr uint64_t GetTypeCRC64() { return CRC64_CaseInsensitive("T3MeshTextureIndices"); }
};

struct T3MeshBatch
{
  public:
    int32_t Read(Stream &stream)
    {
        int32_t size = 0;
        int32_t err;
        err = stream.Read(mBoundingBox);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Read(mBoundingSphere);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Read(mBatchUsage);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Read(mMinVertIndex);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Read(mMaxVertIndex);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Read(mBaseIndex);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Read(mStartIndex);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Read(mNumPrimitives);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Read(mNumIndices);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Read(mTextureIndices);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Read(mMaterialIndex);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Read(mAdjacencyStartIndex);
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
        int32_t err;
        err = stream.Write(mBoundingBox);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Write(mBoundingSphere);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Write(mBatchUsage);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Write(mMinVertIndex);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Write(mMaxVertIndex);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Write(mBaseIndex);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Write(mStartIndex);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Write(mNumPrimitives);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Write(mNumIndices);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Write(mTextureIndices);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Write(mMaterialIndex);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Write(mAdjacencyStartIndex);
        if (err < 0)
        {
            return err;
        }
        size += err;
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
    static constexpr uint64_t GetTypeCRC64() { return CRC64_CaseInsensitive("T3MeshBatch"); }
};
struct T3MeshLOD
{
  public:
    int32_t Read(Stream &stream)
    {
        int32_t size = 0;
        int32_t err;
        err = stream.Read(mBatches[0]);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Read(mBatches[1]);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Read(mVertexStreams);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Read(mBoundingBox);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Read(mBoundingSphere);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Read(mVertexStateIndex);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Read(mNumPrimitives);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Read(mNumBatches);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Read(mPixelSize);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Read(mBones);
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
        int32_t err;
        err = stream.Write(mBatches[0]);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Write(mBatches[1]);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Write(mVertexStreams);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Write(mBoundingBox);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Write(mBoundingSphere);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Write(mVertexStateIndex);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Write(mNumPrimitives);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Write(mNumBatches);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Write(mPixelSize);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Write(mBones);
        if (err < 0)
        {
            return err;
        }
        size += err;
        return size;
    }
    class DCArray<struct T3MeshBatch> mBatches[2];
    class BitSetBase<1> mVertexStreams;
    class BoundingBox mBoundingBox;
    class Sphere mBoundingSphere;
    uint32_t mVertexStateIndex;
    uint32_t mNumPrimitives;
    uint32_t mNumBatches;
    float mPixelSize;
    class DCArray<class Symbol> mBones;
    static constexpr bool IS_BLOCKED = true;
    static constexpr uint64_t GetTypeCRC64() { return CRC64_CaseInsensitive("T3MeshLOD"); }
};

struct T3MeshCPUSkinningEntry
{
    int32_t Read(Stream &stream)
    {
        int32_t size = 0;
        int32_t err;
        err = stream.Read(mNumVerts);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Read(mBoneCount);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Read(mBoneIndices[0]);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Read(mBoneIndices[1]);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Read(mBoneIndices[2]);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Read(mBoneIndices[3]);
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
        int32_t err;
        err = stream.Write(mNumVerts);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Write(mBoneCount);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Write(mBoneIndices[0]);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Write(mBoneIndices[1]);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Write(mBoneIndices[2]);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Write(mBoneIndices[3]);
        if (err < 0)
        {
            return err;
        }
        size += err;
        return size;
    }

    uint32_t mNumVerts;
    uint32_t mBoneCount;
    uint16_t mBoneIndices[4];

    static constexpr uint64_t GetTypeCRC64() { return CRC64_CaseInsensitive("T3MeshCPUSkinningEntry"); }
    static constexpr bool IS_BLOCKED = true;
};

struct T3MeshCPUSkinningData
{
    int32_t Read(Stream &stream)
    {
        int32_t size = 0;
        int32_t err;
        err = stream.Read(mEntries);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Read(mPositionFormat);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Read(mWeightFormat);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Read(mNormalFormat);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Read(mVertexStreams);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Read(mNormalCount);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Read(mVertexSize);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Read(mData);
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
        int32_t err;
        err = stream.Write(mEntries);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Write(mPositionFormat);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Write(mWeightFormat);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Write(mNormalFormat);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Write(mVertexStreams);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Write(mNormalCount);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Write(mVertexSize);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Write(mData);
        if (err < 0)
        {
            return err;
        }
        size += err;
        return size;
    }

    DCArray<T3MeshCPUSkinningEntry> mEntries;
    int32_t mPositionFormat;
    int32_t mWeightFormat;
    int32_t mNormalFormat;
    BitSetBase<1> mVertexStreams;
    uint32_t mNormalCount;
    uint32_t mVertexSize;
    BinaryBuffer mData;

    static constexpr uint64_t GetTypeCRC64() { return CRC64_CaseInsensitive("T3MeshCPUSkinningData"); }
    static constexpr bool IS_BLOCKED = true;
};

struct T3MeshLocalTransformEntry
{
  public:
    int32_t Read(Stream &stream)
    {
        int32_t size = 0;
        int32_t err;
        err = stream.Read(mTransform);
        if (err < 0)
        {
            return err;
        }
        size += err;

        err = stream.Read(mCameraFacingType);
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
        int32_t err;
        err = stream.Write(mTransform);
        if (err < 0)
        {
            return err;
        }
        size += err;

        err = stream.Write(mCameraFacingType);
        if (err < 0)
        {
            return err;
        }
        size += err;
        return size;
    }

    Transform mTransform;
    int32_t mCameraFacingType;
    static constexpr bool IS_BLOCKED = true;
    static constexpr uint64_t GetTypeCRC64() { return CRC64_CaseInsensitive("T3MeshLocalTransformEntry"); }
};

struct T3MeshBoneEntry
{
  public:
    int32_t Read(Stream &stream)
    {
        int32_t size = 0;
        int32_t err;
        err = stream.Read(mBoneName);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Read(mBoundingBox);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Read(mBoundingSphere);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Read(mNumVerts);
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
        int32_t err;
        err = stream.Write(mBoneName);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Write(mBoundingBox);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Write(mBoundingSphere);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Write(mNumVerts);
        if (err < 0)
        {
            return err;
        }
        size += err;
        return size;
    }
    class Symbol mBoneName;
    class BoundingBox mBoundingBox;
    class Sphere mBoundingSphere;
    int32_t mNumVerts;
    static constexpr bool IS_BLOCKED = true;
    static constexpr uint64_t GetTypeCRC64() { return CRC64_CaseInsensitive("T3MeshBoneEntry"); }
};

struct T3MeshMaterialOverride
{
  public:
    int32_t Read(Stream &stream)
    {
        int32_t size = 0;
        int32_t err;
        err = stream.Read(mhOverrideMaterial);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Read(mMaterialIndex);
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
        int32_t err;
        err = stream.Write(mhOverrideMaterial);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Write(mMaterialIndex);
        if (err < 0)
        {
            return err;
        }
        size += err;
        return size;
    }

    Handle<PropertySet> mhOverrideMaterial;
    uint32_t mMaterialIndex;
    static constexpr bool IS_BLOCKED = true;
    static constexpr uint64_t GetTypeCRC64() { return CRC64_CaseInsensitive("T3MeshMaterialOverride"); }
};

struct T3MeshTexture
{
  public:
    int32_t Read(Stream &stream)
    {
        int32_t size = 0;
        int32_t err;
        err = stream.Read(mTextureType);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Read(mhTexture);
        if (err < 0)
        {
            return err;
        }
        size += err;

        err = stream.Read(mNameSymbol);
        if (err < 0)
        {
            return err;
        }
        size += err;

        err = stream.Read(mBoundingBox);
        if (err < 0)
        {
            return err;
        }
        size += err;

        err = stream.Read(mBoundingSphere);
        if (err < 0)
        {
            return err;
        }
        size += err;

        err = stream.Read(mMaxObjAreaPerUVArea);
        if (err < 0)
        {
            return err;
        }
        size += err;

        err = stream.Read(mAverageObjAreaPerUVArea);
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
        int32_t err;
        err = stream.Write(mTextureType);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Write(mhTexture);
        if (err < 0)
        {
            return err;
        }
        size += err;

        err = stream.Write(mNameSymbol);
        if (err < 0)
        {
            return err;
        }
        size += err;

        err = stream.Write(mBoundingBox);
        if (err < 0)
        {
            return err;
        }
        size += err;

        err = stream.Write(mBoundingSphere);
        if (err < 0)
        {
            return err;
        }
        size += err;

        err = stream.Write(mMaxObjAreaPerUVArea);
        if (err < 0)
        {
            return err;
        }
        size += err;

        err = stream.Write(mAverageObjAreaPerUVArea);
        if (err < 0)
        {
            return err;
        }
        size += err;

        return size;
    }
    int32_t mTextureType;
    Handle<D3DMesh> mhTexture; // TODO: Change to Handle<T3Texture>
    Symbol mNameSymbol;
    BoundingBox mBoundingBox;
    Sphere mBoundingSphere;
    float mMaxObjAreaPerUVArea;
    float mAverageObjAreaPerUVArea;
    static constexpr bool IS_BLOCKED = true;
    static constexpr uint64_t GetTypeCRC64() { return CRC64_CaseInsensitive("T3MeshTexture"); }
};

struct T3MaterialData
{
  public:
    int32_t Read(Stream &stream)
    {
        int32_t size = 0;
        int32_t err;
        err = stream.Read(mMaterialName);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Read(mRuntimePropertiesName);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Read(mLegacyRenderTextureProperty);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Read(mLegacyBlendModeRuntimeProperty);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Read(mRuntimeProperties);
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
        err = stream.Read(mVersion);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Read(mCompiledDataCount);
        if (err < 0)
        {
            return err;
        }
        size += err;

        for (uint32_t i = 0; i < mCompiledDataCount; ++i)
        {
            uint32_t index;
            err = stream.Read(index);
            if (err < 0)
            {
                return err;
            }
            size += err;
            err = stream.Read(mCompiledData2[index], false);
            if (err < 0)
            {
                return err;
            }
            size += err;
        }

        return size;
    }
    int32_t Write(Stream &stream) const
    {
        int32_t size = 0;
        int32_t err;
        err = stream.Write(mMaterialName);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Write(mRuntimePropertiesName);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Write(mLegacyRenderTextureProperty);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Write(mLegacyBlendModeRuntimeProperty);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Write(mRuntimeProperties);
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
        err = stream.Write(mVersion);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Write(mCompiledDataCount);
        if (err < 0)
        {
            return err;
        }
        size += err;
        for (uint32_t i = 0; i < mCompiledDataCount; ++i)
        {
            err = stream.Write(i);
            if (err < 0)
            {
                return err;
            }
            size += err;
            err = stream.Write(mCompiledData2[i]);
            if (err < 0)
            {
                return err;
            }
            size += err;
        }
        return size;
    }
    class Symbol mMaterialName;
    class Symbol mRuntimePropertiesName;
    class Symbol mLegacyRenderTextureProperty;
    class Symbol mLegacyBlendModeRuntimeProperty;
    class DCArray<struct T3MaterialRuntimeProperty> mRuntimeProperties;
    class Flags mFlags;
    int32_t mVersion;

    uint32_t mCompiledDataCount;
    T3MaterialCompiledData mCompiledData2[2];
    static constexpr bool IS_BLOCKED = true;
    static constexpr uint64_t GetTypeCRC64() { return CRC64_CaseInsensitive("T3MaterialData"); }
};

struct T3MeshData
{
  public:
    int32_t Read(Stream &stream)
    {
        int32_t size = 0;
        int32_t err;
        err = stream.Read(mLODs);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Read(mTextures);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Read(mMaterials);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Read(mMaterialOverrides);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Read(mBones);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Read(mLocalTransforms);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Read(mMaterialRequirements);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Read(mVertexStreams);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Read(mBoundingBox);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Read(mBoundingSphere);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Read(mEndianType);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Read(mPositionScale);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Read(mPositionWScale);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Read(mPositionOffset);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Read(mLightmapTexelAreaPerSurfaceArea);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Read(mPropertyKeyBase);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Read(mVertexCount);
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

        uint32_t texCoordCount;
        err = stream.Read(texCoordCount);
        if (err < 0)
        {
            return err;
        }
        size += err;

        while (texCoordCount--)
        {
            uint32_t texCoordIndex;
            err = stream.Read(texCoordIndex);
            if (err < 0)
            {
                return err;
            }
            size += err;
            err = stream.Read(mTexCoordTransform[texCoordIndex], false);
            if (err < 0)
            {
                return err;
            }
            size += err;
        }

        if (this->mFlags.mFlags & eHasCPUSkinning)
        {
            T3MeshCPUSkinningData *mpCPUSkinningData = new T3MeshCPUSkinningData();
            err = stream.Read(*mpCPUSkinningData);
            if (err < 0)
            {
                return err;
            }
            size += err;
        }
        err = stream.Read(mVertexStates, false);
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
        int32_t err;
        err = stream.Write(mLODs);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Write(mTextures);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Write(mMaterials);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Write(mMaterialOverrides);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Write(mBones);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Write(mLocalTransforms);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Write(mMaterialRequirements);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Write(mVertexStreams);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Write(mBoundingBox);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Write(mBoundingSphere);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Write(mEndianType);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Write(mPositionScale);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Write(mPositionWScale);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Write(mPositionOffset);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Write(mLightmapTexelAreaPerSurfaceArea);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Write(mPropertyKeyBase);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Write(mVertexCount);
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
    enum MeshFlags // T3MeshData
    {
        eDeformable = 0x1,
        eHasLocalCameraFacing = 0x2,
        eHasLocalCameraFacingY = 0x4,
        eHasLocalCameraFacingLocalY = 0x8,
        eHasCPUSkinning = 0x10,
        eHasComputeSkinning = 0x20
    };

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

    T3MeshTexCoordTransform mTexCoordTransform[4];
    T3MeshCPUSkinningData *mpCPUSkinningData;
    DCArray<T3GFXVertexState> mVertexStates;

    static constexpr bool IS_BLOCKED = true;
    static constexpr uint64_t GetTypeCRC64() { return CRC64_CaseInsensitive("T3MeshData"); }
};
}; // namespace TTH