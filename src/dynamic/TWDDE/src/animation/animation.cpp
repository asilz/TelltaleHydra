

#include <cassert>
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

    static constexpr uint64_t GetTypeCRC64() { return CRC64_CaseInsensitive("CompressedSkeletonPoseKeys2"); }

    int32_t Read(Stream &stream)
    {
        if (mpData != nullptr)
        {
            delete[] mpData;
        }

        int32_t size = stream.Read(mDataSize);
        mpData = new uint8_t[mDataSize];
        size += stream.Read(static_cast<void *>(mpData), mDataSize);
        return size;
    }
    int32_t Write(Stream &stream) const
    {
        int32_t size = stream.Write(mDataSize);
        size += stream.Write(static_cast<const void *>(mpData), mDataSize);
        return size;
    }

    static constexpr bool IS_BLOCKED = false;
    CompressedSkeletonPoseKeys2() : mDataSize(0), mpData(nullptr) {}
    ~CompressedSkeletonPoseKeys2()
    {
        if (mpData != nullptr)
        {
            delete[] mpData;
        }
    }
};

class Animation::Impl
{
  private:
    struct Value
    {
        uint64_t hash;
        uint16_t valueCount;
        uint16_t typeVersion;
    };

    int32_t mVersion;
    Flags mFlags;
    Symbol mName;
    float mLength;
    float mAdditiveMask;
    uint8_t mToolProps;
    int32_t mInterfaceCount;
    AnimationValueInterfaceBase **mValues;
    Flags *mInterfaceFlags;
    Symbol *mInterfaceSymbols;

  public:
    float GetDuration() const { return mLength; }

    size_t GetKeyframeCount(Symbol boneCRC) const { return 0; }

    size_t GetBoneCount() const
    {
        const CompressedSkeletonPoseKeys2 *cspk = nullptr;
        for (int32_t i = 0; i < mInterfaceCount && cspk == nullptr; ++i)
        {
            cspk = dynamic_cast<const CompressedSkeletonPoseKeys2 *>(mValues[i]);
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
        for (int32_t i = 0; i < mInterfaceCount && cspk == nullptr; ++i)
        {
            cspk = dynamic_cast<CompressedSkeletonPoseKeys2 *>(mValues[i]);
        }
        if (cspk == nullptr)
        {
            return nullptr;
        }
        return reinterpret_cast<const Symbol *>(cspk->mpData + sizeof(CompressedSkeletonPoseKeys2::Header) + sizeof(int64_t) +
                                                (reinterpret_cast<const CompressedSkeletonPoseKeys2::Header *>(cspk->mpData))->mSampleDataSize);
    };

    errno_t GetKeyframes(KeyframedValue<Vector3> *translations, KeyframedValue<Quaternion> *rotations) const noexcept
    {
        CompressedSkeletonPoseKeys2 *cspk = nullptr;
        for (int32_t i = 0; i < mInterfaceCount && cspk == nullptr; ++i)
        {
            cspk = dynamic_cast<CompressedSkeletonPoseKeys2 *>(mValues[i]);
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
                    if (translations[(*headerData >> 0x10) & 0xfff].mSamples.size() > 0)
                    {
                        Vector3 *previous = &translations[(*headerData >> 0x10) & 0xfff].mSamples[translations[(*headerData >> 0x10) & 0xfff].mSamples.size() - 1].mValue;
                        delV[stagedDelV].x += previous->x;
                        delV[stagedDelV].y += previous->y;
                        delV[stagedDelV].z += previous->z;
                    }
                    translations[(*headerData >> 0x10) & 0xfff].mSamples.emplace_back((float)(*headerData & 0xffff) * 1.525902e-05f * header.mRangeTime, false, 0, delV[stagedDelV]);
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
                    translations[(*headerData >> 0x10) & 0xfff].mSamples.emplace_back((float)(*headerData & 0xffff) * 1.525902e-05f * header.mRangeTime, false, 0, absV[stagedAbsV]);
                    ++stagedAbsV;
                }
            }
            else // Quaternion
            {
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
                    if (rotations[(*headerData >> 0x10) & 0xfff].mSamples.size() > 0)
                    {
                        delQ[stagedDelQ] = delQ[stagedDelQ] * rotations[(*headerData >> 0x10) & 0xfff].mSamples[rotations[(*headerData >> 0x10) & 0xfff].mSamples.size() - 1].mValue;
                    }
                    rotations[(*headerData >> 0x10) & 0xfff].mSamples.emplace_back((float)(*headerData & 0xffff) * 1.525902e-05f * header.mRangeTime, false, 0, delQ[stagedDelQ]);
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
                    rotations[(*headerData >> 0x10) & 0xfff].mSamples.emplace_back((float)(*headerData & 0xffff) * 1.525902e-05f * header.mRangeTime, false, 0,
                                                                                   Quaternion{.x = *(((float *)absQ + (axisOrder)) + 4 * stagedAbsQ),
                                                                                              .y = *(((float *)absQ + (axisOrder ^ 1)) + 4 * stagedAbsQ),
                                                                                              .z = *(((float *)absQ + (axisOrder ^ 2)) + 4 * stagedAbsQ),
                                                                                              .w = *(((float *)absQ + (axisOrder ^ 3)) + 4 * stagedAbsQ)});

                    ++stagedAbsQ;
                }
            }
        }

        return 0;
    };

    uint32_t GetVersionCRC32() const { return 0; };

    int32_t Read(Stream &stream)
    {
        int32_t size = 0;
        int32_t err = stream.Read(mVersion);
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
        err = stream.Read(mName);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Read(mLength);
        if (err < 0)
        {
            return err;
        }
        size += err;

        err = stream.Read(mAdditiveMask);
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

        err = stream.Seek(4, stream.CUR);
        if (err < 0)
        {
            return err;
        }

        err = stream.Read(mInterfaceCount);
        if (err < 0)
        {
            return err;
        }
        size += err;

        int32_t dataBufferSize;
        err = stream.Read(dataBufferSize);
        if (err < 0)
        {
            return err;
        }
        size += err;

        int32_t animValueTypes;
        err = stream.Read(animValueTypes);
        if (err < 0)
        {
            return err;
        }
        size += err;

        Value animValue;
        mValues = new AnimationValueInterfaceBase *[mInterfaceCount];

        size_t currentInterfaceIndex = 0;
        for (int32_t i = 0; i < animValueTypes; ++i)
        {
            size += stream.Read(animValue.hash);
            size += stream.Read(animValue.valueCount);
            size += stream.Read(animValue.typeVersion);

            switch (animValue.hash)
            {
            case CompressedSkeletonPoseKeys2::GetTypeCRC64():
                while (animValue.valueCount--)
                {
                    mValues[currentInterfaceIndex++] = new CompressedSkeletonPoseKeys2;
                }
                break;
            case KeyframedValue<Transform>::GetTypeCRC64():
                while (animValue.valueCount--)
                {
                    mValues[currentInterfaceIndex++] = new KeyframedValue<Transform>;
                }
                break;
            case KeyframedValue<float>::GetTypeCRC64():
                while (animValue.valueCount--)
                {
                    mValues[currentInterfaceIndex++] = new KeyframedValue<float>;
                }
                break;
            case KeyframedValue<bool>::GetTypeCRC64():
                while (animValue.valueCount--)
                {
                    mValues[currentInterfaceIndex++] = new KeyframedValue<bool>;
                }
                break;
            default:
                assert(0);
                break;
            }
        }

        for (int32_t i = 0; i < mInterfaceCount; ++i)
        {
            size += stream.Read(*(mValues[i]), false);
        }

        mInterfaceFlags = new Flags[mInterfaceCount];
        for (int32_t i = 0; i < mInterfaceCount; ++i)
        {
            size += stream.Read(mInterfaceFlags[i]);
        }

        uint16_t isNotInterfaceSymbols;
        size += stream.Read(isNotInterfaceSymbols);
        if (isNotInterfaceSymbols)
        {
            mInterfaceSymbols = nullptr;
        }
        else
        {
            mInterfaceSymbols = new Symbol[mInterfaceCount];
            for (int32_t i = 0; i < mInterfaceCount; ++i)
            {
                size += stream.Read(mInterfaceSymbols[i]);
            }
        }

        return size;
    }
    int32_t Write(Stream &stream) const { return 0; }

    Impl() : mVersion(-1), mFlags(0), mName(Symbol(0)), mLength(0.0f), mAdditiveMask(0.0f), mToolProps(0), mInterfaceCount(0), mValues(nullptr), mInterfaceFlags(nullptr), mInterfaceSymbols(nullptr) {}
    ~Impl()
    {
        for (int32_t i = 0; i < mInterfaceCount; ++i)
        {
            delete mValues[i];
        }
        delete[] mValues;
        delete[] mInterfaceFlags;
        delete[] mInterfaceSymbols;
    }
};

float Animation::GetDuration() const noexcept { return impl->GetDuration(); }
size_t Animation::GetKeyframeCount(Symbol boneCRC) const noexcept { return impl->GetKeyframeCount(boneCRC); }
size_t Animation::GetBoneCount() const noexcept { return impl->GetBoneCount(); };
const Symbol *Animation::GetBonesCRC64() const noexcept { return impl->GetBonesCRC64(); };
errno_t Animation::GetKeyframes(KeyframedValue<Vector3> *translations, KeyframedValue<Quaternion> *rotations) const noexcept { return impl->GetKeyframes(translations, rotations); };
uint32_t Animation::GetVersionCRC32() const noexcept { return 0; };
int32_t Animation::Read(Stream &stream) { return impl->Read(stream); }
int32_t Animation::Write(Stream &stream) const { return impl->Write(stream); }

errno_t Animation::Create()
{
    impl = new Impl();
    return 0;
}
void Animation::Destroy()
{
    delete impl;
    impl = nullptr;
}
}; // namespace TTH