

#include <math.h>
#include <tth/animation/animation.hpp>
#include <tth/flags.hpp>

namespace TTH
{

class CompressedSkeletonPoseKeys2 : public AnimationValueInterfaceBase
{
  public:
    struct Header
    {
        Vector3 mMinDeltaV;
        Vector3 mRangeDeltaV;
        Vector3 mMinDeltaQ;
        Vector3 mRangeDeltaQ;
        Vector3 mMinVector;
        Vector3 mRangeVector;
        float mRangeTime;
        uint32_t mBoneCount;
        uint64_t mSampleDataSize;
    };

    uint32_t mDataSize;
    uint8_t *mpData;

    ~CompressedSkeletonPoseKeys2() {}
};

class Animation::Impl
{
  private:
    int32_t mVersion;
    Flags mFlags;
    Symbol mName;
    float mLength;
    float mAdditiveMask;
    uint8_t mToolProps;
    int32_t mInterfaceCount;
    AnimationValueInterfaceBase *mValues;
    Flags *mInterfaceFlags;
    Symbol *mInterfaceSymbols;

  public:
    float GetDuration() const { return mLength; }

    size_t GetKeyframeCount(Symbol boneCRC) const {}

    size_t GetBoneCount() const
    {
        const CompressedSkeletonPoseKeys2 *cspk = nullptr;
        for (size_t i = 0; i < mInterfaceCount && cspk == nullptr; ++i)
        {
            cspk = dynamic_cast<const CompressedSkeletonPoseKeys2 *>(mValues + i);
        }
        if (cspk == nullptr)
        {
            return 0;
        }
        return (reinterpret_cast<const CompressedSkeletonPoseKeys2::Header *>(cspk->mpData))->mBoneCount;
    };

    const Symbol *GetBonesCRC64() const
    {
        CompressedSkeletonPoseKeys2 *cspk = nullptr;
        for (size_t i = 0; i < mInterfaceCount && cspk == nullptr; ++i)
        {
            cspk = dynamic_cast<CompressedSkeletonPoseKeys2 *>(mValues + i);
        }
        if (cspk == nullptr)
        {
            return nullptr;
        }
        return reinterpret_cast<const Symbol *>(cspk->mpData + (reinterpret_cast<const CompressedSkeletonPoseKeys2::Header *>(cspk->mpData))->mSampleDataSize);
    };

    errno_t GetKeyframes(KeyframedValue<Transform> *output) const
    {
        CompressedSkeletonPoseKeys2 *cspk = nullptr;
        for (size_t i = 0; i < mInterfaceCount && cspk == nullptr; ++i)
        {
            cspk = dynamic_cast<CompressedSkeletonPoseKeys2 *>(mValues + i);
        }
        if (cspk == nullptr)
        {
            return TTH_TYPE_NOT_FOUND;
        }

        CompressedSkeletonPoseKeys2::Header header = *(CompressedSkeletonPoseKeys2::Header *)(cspk->mpData); // TODO: undefined behaviour? Should probably fix
        const uint8_t *cspkBuf = cspk->mpData + sizeof(header) + sizeof(int64_t);

        header.mRangeVector.x *= 9.536752e-07f;
        header.mRangeVector.y *= 2.384186e-07f;
        header.mRangeVector.z *= 2.384186e-07f;

        header.mRangeDeltaV.x *= 0.0009775171f;
        header.mRangeDeltaV.y *= 0.0004885198f;
        header.mRangeDeltaV.z *= 0.0004885198f;

        header.mRangeDeltaQ.x *= 0.0009775171f;
        header.mRangeDeltaQ.y *= 0.0004885198f;
        header.mRangeDeltaQ.z *= 0.0004885198f;

        size_t stagedDelQ = 4;
        size_t stagedAbsQ = 4;
        size_t stagedDelV = 4;
        size_t stagedAbsV = 4;
        Quaternion delQ[4];
        Quaternion absQ[4];
        Vector3 delV[4];
        Vector3 absV[4];

        for (const uint32_t *headerData = (uint32_t *)(cspkBuf + header.mSampleDataSize + header.mBoneCount * sizeof(uint64_t)); headerData < (uint32_t *)(cspk->mpData + cspk->mDataSize);
             ++headerData)
        {
            if ((*headerData & 0x40000000) == 0) // Vector
            {
                output[(*headerData >> 0x10) & 0xfff].mSamples.emplace_back(KeyframedValue<Transform>::Sample{(float)(*headerData & 0xffff) * 1.525902e-05 * header.mRangeTime, false, 0,
                                                                                                              Transform{Quaternion{0.0f, 0.0f, 0.0f, 1.0f}, Vector3{0.0f, 0.0f, 0.0f}}});
                if ((int32_t)*headerData < 0)
                {
                    if (stagedDelV > 3)
                    {
                        for (uint32_t i = 0; i < 4; ++i)
                        {
                            delV[i].x = (float)(((uint32_t *)cspkBuf)[i] & 0x3ff) * header.mRangeDeltaV.x + header.mMinDeltaV.x;
                            delV[i].y = (float)(((uint32_t *)cspkBuf)[i] >> 10 & 0x7ff) * header.mRangeDeltaV.y + header.mMinDeltaV.y;
                            delV[i].z = (float)(((uint32_t *)cspkBuf)[i] >> 21) * header.mRangeDeltaV.z + header.mMinDeltaV.z;
                        }
                        cspkBuf += 4 * sizeof(uint32_t);
                        stagedDelV = 0;
                    }

                    if (output[(*headerData >> 0x10) & 0xfff].mSamples[output[(*headerData >> 0x10) & 0xfff].mSamples.size() - 1].mTime ==
                        (float)(*headerData & 0xffff) * 1.525902e-05 * header.mRangeTime)
                    {
                        if (output[(*headerData >> 0x10) & 0xfff].mSamples.size() > 0)
                        {
                            Vector3 *previous = &output[(*headerData >> 0x10) & 0xfff].mSamples[output[(*headerData >> 0x10) & 0xfff].mSamples.size() - 2].mValue.mTrans;

                            delV[stagedDelV].x += previous->x;
                            delV[stagedDelV].y += previous->y;
                            delV[stagedDelV].z += previous->z;
                        }
                        output[(*headerData >> 0x10) & 0xfff].mSamples[output[(*headerData >> 0x10) & 0xfff].mSamples.size() - 1].mValue.mTrans = delV[stagedDelV];
                    }

                    if (output[(*headerData >> 0x10) & 0xfff].mSamples.size())
                        assimpAnimation.mChannels[(*headerData >> 0x10) & 0xfff]->mPositionKeys[assimpAnimation.mChannels[(*headerData >> 0x10) & 0xfff]->mNumPositionKeys - 1].mValue =
                            delV[stagedDelV];
                    ++stagedDelV;
                }
                else
                {
                    if (stagedAbsV > 3)
                    {
                        for (uint32_t i = 0; i < 4; ++i)
                        {
                            absV[i].x = (float)(((((uint32_t *)cspkBuf)[4 + i] & 0x3ff) << 10) | (((uint32_t *)cspkBuf)[i] & 0x3ff)) * header.mRangeVector.x + header.mMinVector.x;
                            absV[i].y = (float)(((((uint32_t *)cspkBuf)[4 + i] >> 10 & 0x7ff) << 11) | (((uint32_t *)cspkBuf)[i] >> 10 & 0x7ff)) * header.mRangeVector.y + header.mMinVector.y;
                            absV[i].z = (float)(((((uint32_t *)cspkBuf)[4 + i] >> 21) << 11) | (((uint32_t *)cspkBuf)[i] >> 21)) * header.mRangeVector.z + header.mMinVector.z;
                        }
                        cspkBuf += 8 * sizeof(uint32_t);
                        stagedAbsV = 0;
                    }
                    assimpAnimation.mChannels[(*headerData >> 0x10) & 0xfff]->mPositionKeys[assimpAnimation.mChannels[(*headerData >> 0x10) & 0xfff]->mNumPositionKeys - 1].mValue = absV[stagedAbsV];
                    ++stagedAbsV;
                }
            }
            else // Quaternion
            {
                assert(assimpAnimation.mChannels[(*headerData >> 0x10) & 0xfff]->mNumRotationKeys <= maxFrameCount);
                assimpAnimation.mChannels[(*headerData >> 0x10) & 0xfff]->mRotationKeys[++assimpAnimation.mChannels[(*headerData >> 0x10) & 0xfff]->mNumRotationKeys - 1].mTime =
                    (float)(*headerData & 0xffff) * 1.525902e-05 * header.mRangeTime;
                if ((int32_t)*headerData < 0)
                {
                    if (stagedDelQ > 3)
                    {
                        for (uint32_t i = 0; i < 4; ++i)
                        {
                            delQ[i].x = (float)(((uint32_t *)cspkBuf)[i] & 0x3ff) * header.mRangeDeltaQ.x + header.mMinDeltaQ.x;
                            delQ[i].y = (float)(((uint32_t *)cspkBuf)[i] >> 10 & 0x7ff) * header.mRangeDeltaQ.y + header.mMinDeltaQ.y;
                            delQ[i].z = (float)(((uint32_t *)cspkBuf)[i] >> 21) * header.mRangeDeltaQ.z + header.mMinDeltaQ.z;
                            delQ[i].w = ((1.0 - delQ[i].x * delQ[i].x) - delQ[i].y * delQ[i].y) - delQ[i].z * delQ[i].z;

                            if (delQ[i].w > 0.0f)
                            {
                                delQ[i].w = sqrtf(delQ[i].w);
                            }
                            else
                            {
                                delQ[i].w = 0.0f;
                            }
                        }
                        cspkBuf += 4 * sizeof(uint32_t);
                        stagedDelQ = 0;
                    }
                    if (assimpAnimation.mChannels[(*headerData >> 0x10) & 0xfff]->mNumRotationKeys > 1)
                    {
                        aiQuaternionMultiply(
                            delQ + stagedDelQ,
                            &assimpAnimation.mChannels[(*headerData >> 0x10) & 0xfff]->mRotationKeys[assimpAnimation.mChannels[(*headerData >> 0x10) & 0xfff]->mNumRotationKeys - 2].mValue);
                    }
                    assimpAnimation.mChannels[(*headerData >> 0x10) & 0xfff]->mRotationKeys[assimpAnimation.mChannels[(*headerData >> 0x10) & 0xfff]->mNumRotationKeys - 1].mValue = delQ[stagedDelQ];
                    ++stagedDelQ;
                }
                else
                {
                    if (stagedAbsQ > 3)
                    {
                        for (uint32_t i = 0; i < 4; ++i)
                        {
                            absQ[i].x = (float)(((((uint32_t *)cspkBuf)[4 + i] & 0x3ff) << 10) | (((uint32_t *)cspkBuf)[i] & 0x3ff)) * 1.3487e-06 - 0.7071068;
                            absQ[i].y = (float)(((((uint32_t *)cspkBuf)[4 + i] >> 10 & 0x7ff) << 11) | (((uint32_t *)cspkBuf)[i] >> 10 & 0x7ff)) * 3.371749e-07 - 0.7071068;
                            absQ[i].z = (float)(((((uint32_t *)cspkBuf)[4 + i] >> 21) << 11) | (((uint32_t *)cspkBuf)[i] >> 21)) * 3.371749e-07 - 0.7071068;
                            absQ[i].w = ((1.0 - absQ[i].x * absQ[i].x) - absQ[i].y * absQ[i].y) - absQ[i].z * absQ[i].z;
                            if (absQ[i].w > 0.0f)
                            {
                                absQ[i].w = sqrtf(absQ[i].w);
                            }
                            else
                            {
                                absQ[i].w = 0.0f;
                            }
                        }
                        cspkBuf += 8 * sizeof(uint32_t);
                        stagedAbsQ = 0;
                    }
                    uint32_t axisOrder = *headerData >> 0x1c & 3;
                    assimpAnimation.mChannels[(*headerData >> 0x10) & 0xfff]->mRotationKeys[assimpAnimation.mChannels[(*headerData >> 0x10) & 0xfff]->mNumRotationKeys - 1].mValue.x =
                        *(((float *)absQ + (axisOrder ^ 1)) + 4 * stagedAbsQ);
                    assimpAnimation.mChannels[(*headerData >> 0x10) & 0xfff]->mRotationKeys[assimpAnimation.mChannels[(*headerData >> 0x10) & 0xfff]->mNumRotationKeys - 1].mValue.y =
                        *(((float *)absQ + (axisOrder ^ 2)) + 4 * stagedAbsQ);
                    assimpAnimation.mChannels[(*headerData >> 0x10) & 0xfff]->mRotationKeys[assimpAnimation.mChannels[(*headerData >> 0x10) & 0xfff]->mNumRotationKeys - 1].mValue.z =
                        *(((float *)absQ + (axisOrder ^ 3)) + 4 * stagedAbsQ);
                    assimpAnimation.mChannels[(*headerData >> 0x10) & 0xfff]->mRotationKeys[assimpAnimation.mChannels[(*headerData >> 0x10) & 0xfff]->mNumRotationKeys - 1].mValue.w =
                        *(((float *)absQ + (axisOrder)) + 4 * stagedAbsQ);
                    ++stagedAbsQ;
                }
            }
        }
    };

    uint32_t GetVersionCRC32() const { return 0; };

    Impl() : mVersion(-1), mFlags(0), mName(Symbol(0)), mLength(0.0f), mAdditiveMask(0.0f), mToolProps(0), mInterfaceCount(0), mValues(nullptr), mInterfaceFlags(nullptr), mInterfaceSymbols(nullptr) {}
};

float Animation::GetDuration() const { return impl->GetDuration(); }
size_t Animation::GetKeyframeCount(Symbol boneCRC) const { return impl->GetKeyframeCount(boneCRC); }
size_t Animation::GetBoneCount() const { return impl->GetBoneCount(); };
const Symbol *Animation::GetBonesCRC64() const { return impl->GetBonesCRC64(); };
errno_t Animation::GetKeyframes(KeyframedValue<Transform> *output) const { return impl->GetKeyframes(output); };
uint32_t Animation::GetVersionCRC32() const { return 0; };

Animation::Animation() { impl = new Impl(); }
Animation::~Animation() { delete impl; }
}; // namespace TTH