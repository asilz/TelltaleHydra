#include <tth/meta/container/dcarray.hpp>
#include <tth/meta/string/string.hpp>

namespace TTH
{

class InputMapper
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
        err = this->mMappedEvents.Read(stream);
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
        err = this->mMappedEvents.Write(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        return size;
    }

  public:
    class EventMapping
    {
      private:
        inline virtual int32_t Read_(Stream &stream)
        {
            int32_t size = 0;
            int32_t err;
            size += stream.Read(&this->mInputCode, sizeof(this->mInputCode));
            size += stream.Read(&this->mEvent, sizeof(this->mEvent));
            err = this->mScriptFunction.Read(stream);
            if (err < 0)
            {
                return err;
            }
            size += err;
            size += stream.Read(&this->mControllerIndexOverride, sizeof(this->mControllerIndexOverride));
            return size;
        }
        inline virtual int32_t Write_(Stream &stream) const
        {
            int32_t size = 0;
            int32_t err;
            size += stream.Write(&this->mInputCode, sizeof(this->mInputCode));
            size += stream.Write(&this->mEvent, sizeof(this->mEvent));
            err = this->mScriptFunction.Write(stream);
            if (err < 0)
            {
                return err;
            }
            size += err;
            size += stream.Write(&this->mControllerIndexOverride, sizeof(this->mControllerIndexOverride));
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
        int32_t mInputCode;
        int32_t mEvent;
        class String mScriptFunction;
        int32_t mControllerIndexOverride;
        static constexpr bool IS_BLOCKED = true;
    };

    class RawEvent
    {
      private:
        inline virtual int32_t Read_(Stream &stream)
        {
            int32_t size = 0;
            int32_t err;
            size += stream.Read(&this->mKey, sizeof(this->mKey));
            size += stream.Read(&this->mType, sizeof(this->mType));
            size += stream.Read(&this->mX, sizeof(this->mX));
            size += stream.Read(&this->mY, sizeof(this->mY));
            size += stream.Read(&this->mController, sizeof(this->mController));
            err = this->mIMAPFilter.Read(stream);
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
            size += stream.Write(&this->mKey, sizeof(this->mKey));
            size += stream.Write(&this->mType, sizeof(this->mType));
            size += stream.Write(&this->mX, sizeof(this->mX));
            size += stream.Write(&this->mY, sizeof(this->mY));
            size += stream.Write(&this->mController, sizeof(this->mController));
            err = this->mIMAPFilter.Write(stream);
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
        int32_t mKey;
        int32_t mType;
        float mX;
        float mY;
        int32_t mController;
        class DCArray<class InputMapper *> mIMAPFilter; // DArray
        static constexpr bool IS_BLOCKED = false;
    };

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
    class DCArray<class InputMapper::EventMapping> mMappedEvents;
    static constexpr bool IS_BLOCKED = true;
};

} // namespace TTH