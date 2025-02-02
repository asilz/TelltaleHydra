#include <d3dmesh.hpp>
#include <tth/container/dcarray.hpp>
#include <tth/core/any.hpp>
#include <tth/flags.hpp>
#include <tth/handle.hpp>
#include <tth/prop/prop.hpp>

namespace TTH
{
class PropertySet::Impl
{
  public:
    int32_t Read(Stream &stream)
    {
        int32_t size = 0;
        int32_t err;

        err = stream.Read(this->mPropVersion);
        if (err < 0)
        {
            return err;
        }
        size += err;

        err = stream.Read(mPropertyFlags);
        if (err < 0)
        {
            return err;
        }
        size += err;

        uint32_t blockSize = 4;
        stream.Seek(4, stream.CUR);

        err = stream.Read(mParents);
        if (err < 0)
        {
            return err;
        }
        blockSize += err;

        blockSize += stream.Read(mGroupCount);
        this->mGroups = new TypeGroup[this->mGroupCount];
        for (uint32_t i = 0; i < this->mGroupCount; ++i) // TODO: Fix this piece of garbage
        {
            blockSize += stream.Read(this->mGroups[i].typeSymbol);
            blockSize += stream.Read(this->mGroups[i].pairCount);

            this->mGroups[i].pairs = new TypeGroup::NameValuePair[this->mGroups[i].pairCount];
            for (uint32_t j = 0; j < this->mGroups[i].pairCount; ++j)
            {
                blockSize += stream.Read(this->mGroups[i].pairs[j].nameHash);
                this->mGroups[i].pairs[j].value = Any(this->mGroups[i].typeSymbol);
                blockSize += stream.Read(this->mGroups[i].pairs[j].value);
            }
        }

        if (this->mPropertyFlags.mFlags & eHasEditorProps)
        {
            mEditorProp.Create();
            err = stream.Read(mEditorProp);
            if (err < 0)
            {
                return err;
            }
            blockSize += err;
        }

        return size + blockSize;
    }
    int32_t Write(Stream &stream) const
    {
        int32_t size = 0;
        int32_t err;
        size += stream.Write(this->mPropVersion);
        err = stream.Write(mPropertyFlags);
        if (err < 0)
        {
            return err;
        }
        size += err;
        return size;
    }

    enum PropertyFlags
    {
        eSceneProperties = 0x1,
        eChoreAgentProperties = 0x2,
        eChoreResourceProperties = 0x4,
        ePlaybackControllerProperties = 0x8,
        eRuntimeProperties = 0x10,
        eRuleProperty = 0x20,
        eActorAgentProperties = 0x40,
        eAgentProperties = 0x80,
        eScriptChangedAtRuntime = 0x100,
        eExcludeFromSaveGames = 0x200,
        eHasEditorProps = 0x400,
        eInDelayPostLoadQueue = 0x1000,
        eInDelayPostLoadQueueLocked = 0x2000,
        eInDelayPostLoadQueueDeleted = 0x4000,
        eReadOnly = 0x8000,
        ePropertyInterface = 0x10000,
        ePropertyCallbacksOnly = 0x20000,
        eCreateKeysInAlt = 0x40000,
        eTransientProperties = 0x80000,
        eDontValidate = 0x100000,
        eReferencedByLuaFunc = 0x200000,
        eLockedInCache = 0x400000,
        eEmbedded = 0x800000,
        eSynchronousCallbacks = 0x1000000,
        eOwnsHandleToSelf = 0x2000000,
        eMaterialProperties = 0x4000000,
        eMaterialRuntimeProperties = 0x8000000
    };

    struct TypeGroup
    {
        struct NameValuePair
        {
            uint64_t nameHash;
            Any value;
        };

        uint64_t typeSymbol;
        uint32_t pairCount;
        NameValuePair *pairs;

        TypeGroup() : typeSymbol(0), pairCount(0), pairs(nullptr) {}
        ~TypeGroup() { delete[] pairs; }
    };

    Impl() : mPropVersion(-1), mPropertyFlags(Flags()), mParents(DCArray<Handle<PropertySet>>()), mGroupCount(0), mGroups(nullptr) {}
    ~Impl()
    {
        delete[] mGroups;
        mEditorProp.Destory();
    }

    int32_t mPropVersion;
    Flags mPropertyFlags;
    // block
    DCArray<Handle<PropertySet>> mParents; // This is supposed to be a List
    uint32_t mGroupCount;
    TypeGroup *mGroups;
    PropertySet mEditorProp;

    static constexpr bool IS_BLOCKED = true;
};
errno_t PropertySet::Create()
{
    impl = new Impl();
    return 0;
}

void PropertySet::Destory() { delete impl; }

int32_t PropertySet::Read(Stream &stream) noexcept { return impl->Read(stream); }
int32_t PropertySet::Write(Stream &stream) const noexcept { return impl->Write(stream); }
}; // namespace TTH