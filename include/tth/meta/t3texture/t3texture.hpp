#pragma once

#include <tth/meta/container/dcarray.hpp>
#include <tth/meta/enum/enumplatformtype.hpp>
#include <tth/meta/linalg/vector.hpp>
#include <tth/meta/string/string.hpp>
#include <tth/meta/t3texture/color.hpp>
#include <tth/meta/t3texture/swizzle.hpp>
#include <tth/meta/toolprops.hpp>

namespace TTH
{

class T3SamplerStateBlock
{
  private:
    inline int32_t Read_(Stream &stream) { return stream.Read(&this->mData, sizeof(this->mData)); }
    inline int32_t Write_(Stream &stream) const { return stream.Write(&this->mData, sizeof(this->mData)); }

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
    uint32_t mData;
    static constexpr bool IS_BLOCKED = true;
};

class T3Texture
{
  private:
    inline int32_t Read_(Stream &stream)
    {
        int32_t size = 0;
        int32_t err;
        size += stream.Read(&this->mVersion, sizeof(this->mVersion));
        err = this->mSamplerState.Read(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = this->mPlatform.Read(stream);
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
        err = this->mImportName.Read(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        size += stream.Read(&this->mImportScale, sizeof(this->mImportScale));
        err = this->mToolProps.Read(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        size += stream.Read(&this->mNumMipLevels, sizeof(this->mNumMipLevels));
        size += stream.Read(&this->mWidth, sizeof(this->mWidth));
        size += stream.Read(&this->mHeight, sizeof(this->mHeight));
        size += stream.Read(&this->mDepth, sizeof(this->mDepth));
        size += stream.Read(&this->mArraySize, sizeof(this->mArraySize));
        size += stream.Read(&this->mSurfaceFormat, sizeof(this->mSurfaceFormat));
        size += stream.Read(&this->mTextureLayout, sizeof(this->mTextureLayout));
        size += stream.Read(&this->mSurfaceGamma, sizeof(this->mSurfaceGamma));
        size += stream.Read(&this->mSurfaceMultisample, sizeof(this->mSurfaceMultisample));
        size += stream.Read(&this->mResourceUsage, sizeof(this->mResourceUsage));
        size += stream.Read(&this->mType, sizeof(this->mType));
        err = this->mSwizzle.Read(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        size += stream.Read(&this->mSpecularGlossExponent, sizeof(this->mSpecularGlossExponent));
        size += stream.Read(&this->mHDRLightmapScale, sizeof(this->mHDRLightmapScale));
        size += stream.Read(&this->mToonGradientCutoff, sizeof(this->mToonGradientCutoff));
        size += stream.Read(&this->mAlphaMode, sizeof(this->mAlphaMode));
        size += stream.Read(&this->mColorMode, sizeof(this->mColorMode));
        err = this->mUVOffset.Read(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = this->mUVScale.Read(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = this->mArrayFrameNames.Read(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = this->mToonRegions.Read(stream);
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
        size += stream.Write(&this->mVersion, sizeof(this->mVersion));
        err = this->mSamplerState.Write(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = this->mPlatform.Write(stream);
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
        err = this->mImportName.Write(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        size += stream.Write(&this->mImportScale, sizeof(this->mImportScale));
        err = this->mToolProps.Write(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        size += stream.Write(&this->mNumMipLevels, sizeof(this->mNumMipLevels));
        size += stream.Write(&this->mWidth, sizeof(this->mWidth));
        size += stream.Write(&this->mHeight, sizeof(this->mHeight));
        size += stream.Write(&this->mDepth, sizeof(this->mDepth));
        size += stream.Write(&this->mArraySize, sizeof(this->mArraySize));
        size += stream.Write(&this->mSurfaceFormat, sizeof(this->mSurfaceFormat));
        size += stream.Write(&this->mTextureLayout, sizeof(this->mTextureLayout));
        size += stream.Write(&this->mSurfaceGamma, sizeof(this->mSurfaceGamma));
        size += stream.Write(&this->mSurfaceMultisample, sizeof(this->mSurfaceMultisample));
        size += stream.Write(&this->mResourceUsage, sizeof(this->mResourceUsage));
        size += stream.Write(&this->mType, sizeof(this->mType));
        err = this->mSwizzle.Write(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        size += stream.Write(&this->mSpecularGlossExponent, sizeof(this->mSpecularGlossExponent));
        size += stream.Write(&this->mHDRLightmapScale, sizeof(this->mHDRLightmapScale));
        size += stream.Write(&this->mToonGradientCutoff, sizeof(this->mToonGradientCutoff));
        size += stream.Write(&this->mAlphaMode, sizeof(this->mAlphaMode));
        size += stream.Write(&this->mColorMode, sizeof(this->mColorMode));
        err = this->mUVOffset.Write(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = this->mUVScale.Write(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = this->mArrayFrameNames.Write(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = this->mToonRegions.Write(stream);
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

    struct RegionStreamHeader
    {
      private:
        inline int32_t Read_(Stream &stream)
        {
            int32_t size = stream.Read(&this->mFaceIndex, sizeof(this->mFaceIndex));
            size += stream.Read(&this->mMipIndex, sizeof(this->mMipIndex));
            size += stream.Read(&this->mMipCount, sizeof(this->mMipCount));
            size += stream.Read(&this->mDataSize, sizeof(this->mDataSize));
            size += stream.Read(&this->mPitch, sizeof(this->mPitch));
            size += stream.Read(&this->mSlicePitch, sizeof(this->mSlicePitch));
            return size;
        }
        inline int32_t Write_(Stream &stream) const
        {
            int32_t size = stream.Write(&this->mFaceIndex, sizeof(this->mFaceIndex));
            size += stream.Write(&this->mMipIndex, sizeof(this->mMipIndex));
            size += stream.Write(&this->mMipCount, sizeof(this->mMipCount));
            size += stream.Write(&this->mDataSize, sizeof(this->mDataSize));
            size += stream.Write(&this->mPitch, sizeof(this->mPitch));
            size += stream.Write(&this->mSlicePitch, sizeof(this->mSlicePitch));
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
        int32_t mFaceIndex;
        int32_t mMipIndex;
        int32_t mMipCount;
        int32_t mDataSize;
        int32_t mPitch;
        int32_t mSlicePitch;
        static constexpr bool IS_BLOCKED = true;
    };
    struct StreamHeader
    {
      private:
        inline int32_t Read_(Stream &stream)
        {
            int32_t size = stream.Read(&this->mRegionCount, sizeof(this->mRegionCount));
            size += stream.Read(&this->mAuxDataCount, sizeof(this->mAuxDataCount));
            size += stream.Read(&this->mTotalDataSize, sizeof(this->mTotalDataSize));
            return size;
        }
        inline int32_t Write_(Stream &stream) const
        {
            int32_t size = stream.Write(&this->mRegionCount, sizeof(this->mRegionCount));
            size += stream.Write(&this->mAuxDataCount, sizeof(this->mAuxDataCount));
            size += stream.Write(&this->mTotalDataSize, sizeof(this->mTotalDataSize));
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
        int32_t mRegionCount;
        int32_t mAuxDataCount;
        int32_t mTotalDataSize;
        static constexpr bool IS_BLOCKED = true;
    };

    int32_t mVersion;
    class T3SamplerStateBlock mSamplerState;
    struct EnumPlatformType mPlatform;
    class String mName;
    class String mImportName;
    float mImportScale;
    class ToolProps mToolProps;
    uint32_t mNumMipLevels;
    uint32_t mWidth;
    uint32_t mHeight;
    uint32_t mDepth;
    uint32_t mArraySize;
    int32_t mSurfaceFormat;
    int32_t mTextureLayout;
    int32_t mSurfaceGamma;
    int32_t mSurfaceMultisample;
    int32_t mResourceUsage;
    int32_t mType;
    struct RenderSwizzleParams mSwizzle;
    float mSpecularGlossExponent;
    float mHDRLightmapScale;
    float mToonGradientCutoff;
    int32_t mAlphaMode;
    int32_t mColorMode;
    class Vector2 mUVOffset;
    class Vector2 mUVScale;
    class DCArray<class Symbol> mArrayFrameNames;
    class DCArray<class T3ToonGradientRegion> mToonRegions;

    static constexpr bool IS_BLOCKED = true;
};

} // namespace TTH
