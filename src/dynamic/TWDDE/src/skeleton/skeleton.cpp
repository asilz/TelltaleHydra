#include <map>
#include <tth/container/dcarray.hpp>
#include <tth/container/map.hpp>
#include <tth/container/sarray.hpp>
#include <tth/crypto/crc64.hpp>
#include <tth/flags.hpp>
#include <tth/skeleton/skeleton.hpp>
#include <tth/trange.hpp>
#include <vector>

namespace TTH
{
class BoneContraints
{
  public:
    int32_t mBoneType;
    Vector3 mHingeAxis;
    SArray<TRange<float>, 3> mAxisRange;

    int32_t Read(Stream &stream)
    {
        int32_t size = stream.Read(mBoneType);
        if (size < 0)
        {
            return size;
        }
        int32_t err = stream.Read(mHingeAxis);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Read(mAxisRange);
        if (err < 0)
        {
            return err;
        }
        size += err;
        return size;
    }
    int32_t Write(Stream &stream) const
    {
        int32_t size = stream.Write(mBoneType);
        if (size < 0)
        {
            return size;
        }
        int32_t err = stream.Write(mHingeAxis);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Write(mAxisRange);
        if (err < 0)
        {
            return err;
        }
        size += err;
        return size;
    }

    static constexpr bool IS_BLOCKED = true;
};

class Skeleton::Impl
{

    class Entry
    {
      public:
        Symbol mJointName;
        Symbol mParentName;
        int32_t mParentIndex;
        Symbol mMirrorBoneName;
        int32_t mMirrorBoneIndex;
        Vector3 mLocalPos;
        Quaternion mLocalQuat;
        Transform mRestXform;
        Vector3 mGlobalTranslationScale;
        Vector3 mLocalTranslationScale;
        Vector3 mAnimTranslationScale;
        Map<class Symbol, float, struct std::less<class Symbol>> mResourceGroupMembership;
        BoneContraints mConstraints;
        Flags mFlags;

        int32_t Read(Stream &stream) noexcept
        {
            int32_t size = 0;
            int32_t err;
            err = stream.Read(mJointName);
            if (err < 0)
            {
                return err;
            }
            size += err;
            err = stream.Read(mParentName);
            if (err < 0)
            {
                return err;
            }
            size += err;
            err = stream.Read(mParentIndex);
            if (err < 0)
            {
                return err;
            }
            size += err;
            err = stream.Read(mMirrorBoneName);
            if (err < 0)
            {
                return err;
            }
            size += err;
            err = stream.Read(mMirrorBoneIndex);
            if (err < 0)
            {
                return err;
            }
            size += err;
            err = stream.Read(mLocalPos);
            if (err < 0)
            {
                return err;
            }
            size += err;
            err = stream.Read(mLocalQuat);
            if (err < 0)
            {
                return err;
            }
            size += err;
            err = stream.Read(mRestXform);
            if (err < 0)
            {
                return err;
            }
            size += err;
            err = stream.Read(mGlobalTranslationScale);
            if (err < 0)
            {
                return err;
            }
            size += err;
            err = stream.Read(mLocalTranslationScale);
            if (err < 0)
            {
                return err;
            }
            size += err;
            err = stream.Read(mAnimTranslationScale);
            if (err < 0)
            {
                return err;
            }
            size += err;
            err = stream.Read(mResourceGroupMembership);
            if (err < 0)
            {
                return err;
            }
            size += err;
            err = stream.Read(mConstraints);
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

        int32_t Write(Stream &stream) const noexcept
        {
            int32_t size = 0;
            int32_t err;
            err = stream.Write(mJointName);
            if (err < 0)
            {
                return err;
            }
            size += err;
            err = stream.Write(mParentName);
            if (err < 0)
            {
                return err;
            }
            size += err;
            err = stream.Write(mParentIndex);
            if (err < 0)
            {
                return err;
            }
            size += err;
            err = stream.Write(mMirrorBoneName);
            if (err < 0)
            {
                return err;
            }
            size += err;
            err = stream.Write(mMirrorBoneIndex);
            if (err < 0)
            {
                return err;
            }
            size += err;
            err = stream.Write(mLocalPos);
            if (err < 0)
            {
                return err;
            }
            size += err;
            err = stream.Write(mLocalQuat);
            if (err < 0)
            {
                return err;
            }
            size += err;
            err = stream.Write(mRestXform);
            if (err < 0)
            {
                return err;
            }
            size += err;
            err = stream.Write(mGlobalTranslationScale);
            if (err < 0)
            {
                return err;
            }
            size += err;
            err = stream.Write(mLocalTranslationScale);
            if (err < 0)
            {
                return err;
            }
            size += err;
            err = stream.Write(mAnimTranslationScale);
            if (err < 0)
            {
                return err;
            }
            size += err;
            err = stream.Write(mResourceGroupMembership);
            if (err < 0)
            {
                return err;
            }
            size += err;
            err = stream.Write(mConstraints);
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

        static constexpr bool IS_BLOCKED = true;
    };

    DCArray<Entry> mEntries;

  public:
    Symbol GetBoneCRC64(size_t boneIndex) const noexcept
    {
        if (boneIndex < mEntries.size())
        {
            return mEntries[boneIndex].mJointName;
        }
        return 0;
    }
    const Vector3 *GetBoneLocalPosition(size_t boneIndex) const noexcept
    {
        if (boneIndex < mEntries.size())
        {
            return &mEntries[boneIndex].mLocalPos;
        }
        return nullptr;
    }
    const Quaternion *GetBoneLocalRotation(size_t boneIndex) const noexcept
    {
        if (boneIndex < mEntries.size())
        {
            return &mEntries[boneIndex].mLocalQuat;
        }
        return nullptr;
    }
    int32_t Read(Stream &stream) noexcept { return stream.Read(mEntries); }
    int32_t Write(Stream &stream) const noexcept { return stream.Write(mEntries); }

    int32_t GetBoneParentIndex(size_t boneIndex) const noexcept { return mEntries[boneIndex].mParentIndex; }

    size_t GetBoneCount() const noexcept { return mEntries.size(); }
};

Symbol Skeleton::GetBoneCRC64(size_t boneIndex) const noexcept { return impl->GetBoneCRC64(boneIndex); }
const Vector3 *Skeleton::GetBoneLocalPosition(size_t boneIndex) const noexcept { return impl->GetBoneLocalPosition(boneIndex); }
const Quaternion *Skeleton::GetBoneLocalRotation(size_t boneIndex) const noexcept { return impl->GetBoneLocalRotation(boneIndex); }
int32_t Skeleton::GetBoneParentIndex(size_t boneIndex) const noexcept { return impl->GetBoneParentIndex(boneIndex); }
size_t Skeleton::GetBoneCount() const noexcept { return impl->GetBoneCount(); }

int32_t Skeleton::Read(Stream &stream) noexcept { return impl->Read(stream); }
int32_t Skeleton::Write(Stream &stream) const noexcept { return impl->Write(stream); }

errno_t Skeleton::Create()
{
    impl = new Impl;
    return 0;
}
void Skeleton::Destroy()
{
    delete impl;
    impl = nullptr;
}

}; // namespace TTH