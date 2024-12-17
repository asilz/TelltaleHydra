#pragma once

namespace TTH
{

class Chore
{
  private:
    inline virtual int32_t Read_(Stream &stream)
    {
        int32_t size = 0;
        int32_t err;
        err = this->mName.Read(stream);
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
        size += stream.Read(&this->mLength, sizeof(this->mLength));
        size += stream.Read(&this->mNumResources, sizeof(this->mNumResources));
        size += stream.Read(&this->mNumAgents, sizeof(this->mNumAgents));
        err = this->mEditorProps.Read(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = this->mChoreSceneFile.Read(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        size += stream.Read(&this->mRenderDelay, sizeof(this->mRenderDelay));
        err = this->mSynchronizedToLocalization.Read(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = this->mDependencies.Read(stream);
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
        err = this->mWalkPaths.Read(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        return size;
    }
    inline virtual int32_t Write_(Stream &stream) const
    {
        int32_t size = 0;
        int32_t err;
        err = this->mName.Write(stream);
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
        size += stream.Write(&this->mLength, sizeof(this->mLength));
        size += stream.Write(&this->mNumResources, sizeof(this->mNumResources));
        size += stream.Write(&this->mNumAgents, sizeof(this->mNumAgents));
        err = this->mEditorProps.Write(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = this->mChoreSceneFile.Write(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        size += stream.Write(&this->mRenderDelay, sizeof(this->mRenderDelay));
        err = this->mSynchronizedToLocalization.Write(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = this->mDependencies.Write(stream);
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
        err = this->mWalkPaths.Write(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        return size;
    }

  public:
    virtual int32_t Read(Stream &stream)
    {
        int32_t err = stream.Seek(4, stream.CUR);
        if (err < 0)
        {
            return err;
        }
        return Read_(stream) + 4;
    }
    virtual int32_t Read(Stream &stream, bool blocked)
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
    virtual int32_t Write(Stream &stream) const
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
    virtual int32_t Write(Stream &stream, bool blocked) const
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
    class String mName;
    class Flags mFlags;
    float mLength;
    int32_t mNumResources;
    int32_t mNumAgents;
    class PropertySet mEditorProps;
    class String mChoreSceneFile;
    int32_t mRenderDelay;
    class LocalizeInfo mSynchronizedToLocalization;
    class DependencyLoader<1> mDependencies;
    class ToolProps mToolProps;
    class Map<class Symbol, class WalkPath, struct std::less<class Symbol>> mWalkPaths;
    static constexpr bool IS_BLOCKED = true;

    struct EnumExtentsMode : public EnumBase
    {
      private:
        inline virtual int32_t Read_(Stream &stream)
        {
            int32_t size = 0;
            int32_t err;
            size += stream.Read(&this->mVal, sizeof(this->mVal));
            err = EnumBase::Read(stream, true);
            if (err < 0)
            {
                return err;
            }
            size += err;
            return size;
        }
        inline virtual int32_t Write_(Stream &stream) const
        {
            int32_t size = 0;
            int32_t err;
            size += stream.Write(&this->mVal, sizeof(this->mVal));
            err = EnumBase::Read(stream, true);
            if (err < 0)
            {
                return err;
            }
            size += err;
            return size;
        }

      public:
        virtual int32_t Read(Stream &stream) { return Read_(stream); }
        virtual int32_t Read(Stream &stream, bool blocked)
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
        virtual int32_t Write(Stream &stream) const { return Write_(stream); }
        virtual int32_t Write(Stream &stream, bool blocked) const
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
        int32_t mVal;
        static constexpr bool IS_BLOCKED = false;
    };
};

} // namespace TTH