#include <texture/t3texture.hpp>
#include <tth/container/dcarray.hpp>
#include <tth/linalg/vector.hpp>
#include <tth/string.hpp>
#include <tth/texture/t3texture.hpp>
#include <tth/toolprops.hpp>

namespace TTH
{
class T3Texture::Impl
{
  public:
    int32_t Read(Stream &stream)
    {
        int32_t size = 0;
        int32_t err;
        err = stream.Read(mVersion);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Read(mSamplerState);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Read(mPlatform);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Read(mName);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Read(mImportName);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Read(mImportScale);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Read(mToolProps);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Read(mNumMipLevels);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Read(mWidth);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Read(mHeight);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Read(mDepth);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Read(mArraySize);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Read(mSurfaceFormat);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Read(mTextureLayout);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Read(mSurfaceGamma);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Read(mSurfaceMultisample);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Read(mResourceUsage);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Read(mType);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Read(mSwizzle);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Read(mSpecularGlossExponent);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Read(mHDRLightmapScale);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Read(mToonGradientCutoff);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Read(mAlphaMode);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Read(mColorMode);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Read(mUVOffset);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Read(mUVScale);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Read(mArrayFrameNames);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Read(mToonRegions);
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
        err = stream.Write(mVersion);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Write(mSamplerState);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Write(mPlatform);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Write(mName);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Write(mImportName);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Write(mImportScale);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Write(mToolProps);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Write(mNumMipLevels);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Write(mWidth);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Write(mHeight);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Write(mDepth);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Write(mArraySize);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Write(mSurfaceFormat);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Write(mTextureLayout);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Write(mSurfaceGamma);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Write(mSurfaceMultisample);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Write(mResourceUsage);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Write(mType);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Write(mSwizzle);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Write(mSpecularGlossExponent);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Write(mHDRLightmapScale);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Write(mToonGradientCutoff);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Write(mAlphaMode);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Write(mColorMode);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Write(mUVOffset);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Write(mUVScale);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Write(mArrayFrameNames);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Write(mToonRegions);
        if (err < 0)
        {
            return err;
        }
        size += err;
        return size;
    }
    int32_t mVersion;
    T3SamplerStateBlock mSamplerState;
    EnumPlatformType mPlatform;
    String mName;
    String mImportName;
    float mImportScale;
    ToolProps mToolProps;
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
    RenderSwizzleParams mSwizzle;
    float mSpecularGlossExponent;
    float mHDRLightmapScale;
    float mToonGradientCutoff;
    int32_t mAlphaMode;
    int32_t mColorMode;
    Vector2 mUVOffset;
    Vector2 mUVScale;
    DCArray<Symbol> mArrayFrameNames;
    DCArray<T3ToonGradientRegion> mToonRegions;
    static constexpr bool IS_BLOCKED = true;
};

int32_t T3Texture::Read(Stream &stream) { return impl->Read(stream); }
int32_t T3Texture::Write(Stream &stream) const { return impl->Write(stream); }
errno_t T3Texture::Create()
{
    impl = new Impl();
    return 0;
}
void T3Texture::Destroy() { delete impl; }
}; // namespace TTH