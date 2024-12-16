#pragma once

#include <tth/meta/bitset/base.hpp>
#include <tth/meta/container/dcarray.hpp>
#include <tth/meta/container/set.hpp>
#include <tth/meta/crc64/symbol.hpp>
#include <tth/meta/string/string.hpp>

namespace PreloadPackage
{
struct ResourceKey
{
  private:
    inline int32_t Read_(Stream &stream)
    {
        int32_t size = 0;
        int32_t err;
        err = this->mResourceName.Read(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        size += stream.Read(&this->mMetaClassDescriptionCrc, sizeof(this->mMetaClassDescriptionCrc));
        err = this->mRenderQualities.Read(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        size += stream.Read(&this->mVisible, sizeof(this->mVisible));
        err = this->mPrefix.Read(stream);
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
        err = this->mResourceName.Write(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        size += stream.Write(&this->mMetaClassDescriptionCrc, sizeof(this->mMetaClassDescriptionCrc));
        err = this->mRenderQualities.Write(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        size += stream.Write(&this->mVisible, sizeof(this->mVisible));
        err = this->mPrefix.Write(stream);
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
    class Symbol mResourceName;
    uint64_t mMetaClassDescriptionCrc;
    class BitSetBase<1> mRenderQualities;
    bool mVisible;
    class String mPrefix;
    static constexpr bool IS_BLOCKED = true;
};
struct ResourceSeenTimes
{
  private:
    inline int32_t Read_(Stream &stream)
    {
        int32_t size = 0;
        int32_t err;
        size += stream.Read(&this->mfEarliest, sizeof(this->mfEarliest));
        size += stream.Read(&this->mfLatest, sizeof(this->mfLatest));
        err = this->mAdditionalScenes.Read(stream);
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
        size += stream.Write(&this->mfEarliest, sizeof(this->mfEarliest));
        size += stream.Write(&this->mfLatest, sizeof(this->mfLatest));
        err = this->mAdditionalScenes.Write(stream);
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
    float mfEarliest;
    float mfLatest;
    class Set<class Symbol, struct std::less<class Symbol>> mAdditionalScenes;
    static constexpr bool IS_BLOCKED = false;
};
class RuntimeDataScene
{
  private:
    inline int32_t Read_(Stream &stream)
    {
        int32_t size = 0;
        int32_t err;
        err = this->mResources.Read(stream);
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
        err = this->mResources.Write(stream);
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
    class DCArray<struct PreloadPackage::ResourceKey> mResources;
    static constexpr bool IS_BLOCKED = true;
};
class RuntimeDataDialog
{
  private:
    inline int32_t Read_(Stream &stream)
    {
        int32_t size = 0;
        int32_t err;
        err = this->mDialogResourceVectors.Read(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = this->mStartNodeOffsets.Read(stream);
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
        err = this->mDialogResourceVectors.Write(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = this->mStartNodeOffsets.Write(stream);
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
    class DCArray<struct PreloadPackage::RuntimeDataDialog::DlgObjIdAndResourceVector> mDialogResourceVectors;
    class DCArray<struct PreloadPackage::RuntimeDataDialog::DlgObjIdAndStartNodeOffset> mStartNodeOffsets;
    static constexpr bool IS_BLOCKED = false;

    struct DialogResourceInfo
    {
      private:
        inline int32_t Read_(Stream &stream)
        {
            int32_t size = 0;
            int32_t err;
            err = this->mResourceKey.Read(stream);
            if (err < 0)
            {
                return err;
            }
            size += err;
            err = this->mResourceSeenTimes.Read(stream);
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
            err = this->mResourceKey.Write(stream);
            if (err < 0)
            {
                return err;
            }
            size += err;
            err = this->mResourceSeenTimes.Write(stream);
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
        struct PreloadPackage::ResourceKey mResourceKey;
        struct PreloadPackage::ResourceSeenTimes mResourceSeenTimes;
        static constexpr bool IS_BLOCKED = false;
    };
};

}; // namespace PreloadPackage