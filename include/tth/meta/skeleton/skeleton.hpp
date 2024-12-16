#pragma once

#include <tth/meta/container/dcarray.hpp>
#include <tth/meta/container/map.hpp>
#include <tth/meta/container/sarray.hpp>
#include <tth/meta/crc64/symbol.hpp>
#include <tth/meta/flags.hpp>
#include <tth/meta/linalg/trange.hpp>
#include <tth/meta/linalg/transform.hpp>

class BoneContraints
{
  private:
    inline int32_t Read_(Stream &stream)
    {
        int32_t size = 0;
        int32_t err;
        size += stream.Read(&this->mBoneType, sizeof(this->mBoneType));
        err = this->mHingeAxis.Read(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = this->mAxisRange.Read(stream);
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
        size += stream.Write(&this->mBoneType, sizeof(this->mBoneType));
        err = this->mHingeAxis.Write(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = this->mAxisRange.Write(stream);
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
    int32_t mBoneType;
    class Vector3 mHingeAxis;
    class SArray<class TRange<float>, 3> mAxisRange;
    static constexpr bool IS_BLOCKED = true;
};

class Skeleton
{
  private:
    inline int32_t Read_(Stream &stream)
    {
        int32_t size = 0;
        int32_t err;
        err = this->mEntries.Read(stream);
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
        err = this->mEntries.Write(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        return size;
    }

  public:
    class Entry
    {
      private:
        inline int32_t Read_(Stream &stream)
        {
            int32_t size = 0;
            int32_t err;
            err = this->mJointName.Read(stream);
            if (err < 0)
            {
                return err;
            }
            size += err;
            err = this->mParentName.Read(stream);
            if (err < 0)
            {
                return err;
            }
            size += err;
            size += stream.Read(&this->mParentIndex, sizeof(this->mParentIndex));
            err = this->mMirrorBoneName.Read(stream);
            if (err < 0)
            {
                return err;
            }
            size += err;
            size += stream.Read(&this->mMirrorBoneIndex, sizeof(this->mMirrorBoneIndex));
            err = this->mLocalPos.Read(stream);
            if (err < 0)
            {
                return err;
            }
            size += err;
            err = this->mLocalQuat.Read(stream);
            if (err < 0)
            {
                return err;
            }
            size += err;
            err = this->mRestXform.Read(stream);
            if (err < 0)
            {
                return err;
            }
            size += err;
            err = this->mGlobalTranslationScale.Read(stream);
            if (err < 0)
            {
                return err;
            }
            size += err;
            err = this->mLocalTranslationScale.Read(stream);
            if (err < 0)
            {
                return err;
            }
            size += err;
            err = this->mAnimTranslationScale.Read(stream);
            if (err < 0)
            {
                return err;
            }
            size += err;
            err = this->mResourceGroupMembership.Read(stream);
            if (err < 0)
            {
                return err;
            }
            size += err;
            err = this->mConstraints.Read(stream);
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
            err = this->mJointName.Write(stream);
            if (err < 0)
            {
                return err;
            }
            size += err;
            err = this->mParentName.Write(stream);
            if (err < 0)
            {
                return err;
            }
            size += err;
            size += stream.Write(&this->mParentIndex, sizeof(this->mParentIndex));
            err = this->mMirrorBoneName.Write(stream);
            if (err < 0)
            {
                return err;
            }
            size += err;
            size += stream.Write(&this->mMirrorBoneIndex, sizeof(this->mMirrorBoneIndex));
            err = this->mLocalPos.Write(stream);
            if (err < 0)
            {
                return err;
            }
            size += err;
            err = this->mLocalQuat.Write(stream);
            if (err < 0)
            {
                return err;
            }
            size += err;
            err = this->mRestXform.Write(stream);
            if (err < 0)
            {
                return err;
            }
            size += err;
            err = this->mGlobalTranslationScale.Write(stream);
            if (err < 0)
            {
                return err;
            }
            size += err;
            err = this->mLocalTranslationScale.Write(stream);
            if (err < 0)
            {
                return err;
            }
            size += err;
            err = this->mAnimTranslationScale.Write(stream);
            if (err < 0)
            {
                return err;
            }
            size += err;
            err = this->mResourceGroupMembership.Write(stream);
            if (err < 0)
            {
                return err;
            }
            size += err;
            err = this->mConstraints.Write(stream);
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
        class Symbol mJointName;
        class Symbol mParentName;
        int32_t mParentIndex;
        class Symbol mMirrorBoneName;
        int32_t mMirrorBoneIndex;
        class Vector3 mLocalPos;
        class Quaternion mLocalQuat;
        class Transform mRestXform;
        class Vector3 mGlobalTranslationScale;
        class Vector3 mLocalTranslationScale;
        class Vector3 mAnimTranslationScale;
        class Map<class Symbol, float, struct std::less<class Symbol>> mResourceGroupMembership;
        class BoneContraints mConstraints;
        class Flags mFlags;
        static constexpr bool IS_BLOCKED = true;
    };
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
    class DCArray<class Entry> mEntries;
    static constexpr bool IS_BLOCKED = true;
};