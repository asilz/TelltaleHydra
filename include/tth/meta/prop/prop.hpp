#pragma once

#include <tth/meta/container/dcarray.hpp>
#include <tth/meta/flags.hpp>

namespace TTH
{

class PropertySet
{
  private:
    inline int32_t Read_(Stream &stream)
    {
        int32_t size = 0;
        int32_t err;
        size += stream.Read(&this->mPropVersion, sizeof(this->mPropVersion));
        err = this->mPropertyFlags.Read(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;

        uint32_t blockSize = 4;
        stream.Seek(4, stream.CUR);

        err = this->mParents.Read(stream);
        if (err < 0)
        {
            return err;
        }
        blockSize += err;

        blockSize += stream.Read(&this->mGroupCount, sizeof(this->mGroupCount));
        this->mGroups = new TypeGroup[this->mGroupCount];
        for (uint32_t i = 0; i < this->mGroupCount; ++i) // TODO: Fix this piece of garbage
        {
            blockSize += stream.Read(&this->mGroups[i].typeSymbol, sizeof(this->mGroups[i].typeSymbol));
            blockSize += stream.Read(&this->mGroups[i].pairCount, sizeof(this->mGroups[i].pairCount));

            this->mGroups[i].pairs = new TypeGroup::NameValuePair[this->mGroups[i].pairCount];
            for (uint32_t j = 0; j < this->mGroups[i].pairCount; ++j)
            {
                blockSize += stream.Read(&this->mGroups[i].pairs[j].nameHash, sizeof(this->mGroups[i].pairs[j].nameHash));
                this->mGroups[i].pairs[j].value = Any(this->mGroups[i].typeSymbol);
                blockSize += this->mGroups[i].pairs[j].value.Read(stream);
            }
        }

        if (this->mPropertyFlags.mFlags & eHasEditorProps)
        {
            this->mEditorProp = new PropertySet;
            err = this->mEditorProp->Read(stream);
            if (err < 0)
            {
                return err;
            }
            blockSize += err;
        }

        return size + blockSize;
    }
    inline int32_t Write_(Stream &stream) const
    {
        int32_t size = 0;
        int32_t err;
        size += stream.Write(&this->mPropVersion, sizeof(this->mPropVersion));
        err = this->mPropertyFlags.Write(stream);
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
        ~TypeGroup() { delete pairs; }
    };

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

    PropertySet() : mPropVersion(-1), mPropertyFlags(Flags()), mParents(DCArray<Handle<PropertySet>>()), mGroupCount(0), mGroups(nullptr), mEditorProp(nullptr) {}
    ~PropertySet()
    {
        delete[] mGroups;
        delete mEditorProp;
    }

    int32_t mPropVersion;
    Flags mPropertyFlags;
    // block
    DCArray<Handle<PropertySet>> mParents; // This is supposed to be a List
    uint32_t mGroupCount;
    TypeGroup *mGroups;
    PropertySet *mEditorProp;

    static constexpr bool IS_BLOCKED = true;
};

} // namespace TTH