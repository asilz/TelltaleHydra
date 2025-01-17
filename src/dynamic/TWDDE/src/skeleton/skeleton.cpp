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
    };

    DCArray<Entry> mEntries;

  public:
    Symbol GetBoneCRC64(size_t boneIndex) const
    {
        if (boneIndex < mEntries.size())
        {
            return mEntries[boneIndex].mJointName;
        }
        return 0;
    }
    const Vector3 *GetBoneLocalPosition(size_t boneIndex) const
    {
        if (boneIndex < mEntries.size())
        {
            return &mEntries[boneIndex].mLocalPos;
        }
        return nullptr;
    }
    const Quaternion *GetBoneLocalRotation(size_t boneIndex) const
    {
        if (boneIndex < mEntries.size())
        {
            return &mEntries[boneIndex].mLocalQuat;
        }
        return nullptr;
    }
    size_t GetBoneParentIndex(size_t boneIndex) const { return mEntries[boneIndex].mParentIndex; }
};

Symbol Skeleton::GetBoneCRC64(size_t boneIndex) const { return impl->GetBoneCRC64(boneIndex); }
const Vector3 *Skeleton::GetBoneLocalPosition(size_t boneIndex) const { return impl->GetBoneLocalPosition(boneIndex); }
const Quaternion *Skeleton::GetBoneLocalRotation(size_t boneIndex) const { return impl->GetBoneLocalRotation(boneIndex); }
size_t Skeleton::GetBoneParentIndex(size_t boneIndex) const { return impl->GetBoneParentIndex(boneIndex); }

Skeleton::Skeleton() { impl = new Impl; }
Skeleton::~Skeleton() { delete impl; }

}; // namespace TTH