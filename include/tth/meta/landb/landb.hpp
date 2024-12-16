#pragma once

#include <tth/meta/container/dcarray.hpp>
#include <tth/meta/container/map.hpp>
#include <tth/meta/flags.hpp>
#include <tth/meta/handle/handle.hpp>
#include <tth/meta/recordingutils/recordingutils.hpp>
#include <tth/meta/string/string.hpp>
#include <tth/meta/toolprops.hpp>
#include <tth/meta/uid/uid.hpp>

class LocalizationRegistry
{
  private:
    inline int32_t Read_(Stream &stream)
    {
        int32_t size = 0;
        int32_t err;
        err = this->mFlagIndexMap.Read(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = this->mFlagIndexMapReverse.Read(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = this->mToolProps.Read(stream);
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
        err = this->mFlagIndexMap.Write(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = this->mFlagIndexMapReverse.Write(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = this->mToolProps.Write(stream);
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
    class Map<class Symbol, int, struct std::less<class Symbol>> mFlagIndexMap;
    class Map<int, class Symbol, struct std::less<int>> mFlagIndexMapReverse;
    class ToolProps mToolProps;
    static constexpr bool IS_BLOCKED = true;
};

class LocalizeInfo
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
    class Flags mFlags;
    static constexpr bool IS_BLOCKED = true;
};
class LanguageResLocal
{
  private:
    inline int32_t Read_(Stream &stream)
    {
        int32_t size = 0;
        int32_t err;
        err = this->mPrefix.Read(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = this->mText.Read(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = this->mLocalInfo.Read(stream);
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
        err = this->mPrefix.Write(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = this->mText.Write(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = this->mLocalInfo.Write(stream);
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
    class String mPrefix;
    class String mText;
    class LocalizeInfo mLocalInfo;
    static constexpr bool IS_BLOCKED = true;
};
class LanguageRes
{
  private:
    inline int32_t Read_(Stream &stream)
    {
        int32_t size = 0;
        int32_t err;
        err = this->mResName.Read(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        size += stream.Read(&this->mID, sizeof(this->mID));
        size += stream.Read(&this->mIDAlias, sizeof(this->mIDAlias));
        err = this->mhAnimation.Read(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = this->mhVoiceData.Read(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = this->mLocalData.Read(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        size += stream.Read(&this->mLengthOverride, sizeof(this->mLengthOverride));
        err = this->mResolvedLocalData.Read(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = this->mRecordingStatus.Read(stream);
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
        err = this->mResName.Write(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        size += stream.Write(&this->mID, sizeof(this->mID));
        size += stream.Write(&this->mIDAlias, sizeof(this->mIDAlias));
        err = this->mhAnimation.Write(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = this->mhVoiceData.Write(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = this->mLocalData.Write(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        size += stream.Write(&this->mLengthOverride, sizeof(this->mLengthOverride));
        err = this->mResolvedLocalData.Write(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = this->mRecordingStatus.Write(stream);
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
    class Symbol mResName;
    uint32_t mID;
    uint32_t mIDAlias;
    class Handle<class Animation> mhAnimation;
    class Handle<class SoundData> mhVoiceData;
    class DCArray<class LanguageResLocal> mLocalData;
    float mLengthOverride;
    class LanguageResLocal mResolvedLocalData;
    struct RecordingUtils::EnumRecordingStatus mRecordingStatus;
    class Flags mFlags;
    static constexpr bool IS_BLOCKED = true;
};
class LanguageDB : public UID::Owner, public UID::Generator
{
  private:
    inline int32_t Read_(Stream &stream)
    {
        int32_t size = 0;
        int32_t err;
        err = UID::Owner::Read(stream, true);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = UID::Generator::Read(stream, true);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = this->mLanguageResources.Read(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = this->mRegistry.Read(stream);
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
        size += stream.Read(&this->mProjectID, sizeof(this->mProjectID));
        err = this->mExpandedIDRanges.Read(stream);
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
        err = UID::Owner::Write(stream, true);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = UID::Generator::Write(stream, true);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = this->mLanguageResources.Write(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = this->mRegistry.Write(stream);
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
        size += stream.Write(&this->mProjectID, sizeof(this->mProjectID));
        err = this->mExpandedIDRanges.Write(stream);
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
    class Map<unsigned int, class LanguageRes, struct std::less<unsigned int>> mLanguageResources;
    class LocalizationRegistry mRegistry;
    class Flags mFlags;
    uint32_t mProjectID;
    class DCArray<class ProjectDatabaseIDPair> mExpandedIDRanges;
    static constexpr bool IS_BLOCKED = true;
};
