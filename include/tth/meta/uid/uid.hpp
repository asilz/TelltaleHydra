#include <tth/stream/stream.hpp>

namespace TTH
{
namespace UID
{
class Generator
{
  private:
    inline virtual int32_t Read_(Stream &stream) { return stream.Read(&this->miNextUniqueID, sizeof(this->miNextUniqueID)); }
    inline virtual int32_t Write_(Stream &stream) const { return stream.Write(&this->miNextUniqueID, sizeof(this->miNextUniqueID)); }

  public:
    virtual int32_t Read(Stream &stream)
    {
        int32_t err = stream.Seek(4, stream.CUR);
        if (err < 0)
        {
            return err;
        }
        return Generator::Read_(stream) + 4;
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
            return Generator::Read_(stream) + 4;
        }
        return Generator::Read_(stream);
    }
    virtual int32_t Write(Stream &stream) const
    {
        int32_t size = 0;
        size += stream.Write(&size, sizeof(size));
        size += Generator::Write_(stream);
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
        size += Generator::Write_(stream);
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
    virtual ~Generator() {}

    int32_t miNextUniqueID;
    static constexpr bool IS_BLOCKED = true;
};
class Owner
{
  private:
    inline virtual int32_t Read_(Stream &stream) { return stream.Read(&this->miUniqueID, sizeof(this->miUniqueID)); }
    inline virtual int32_t Write_(Stream &stream) const { return stream.Write(&this->miUniqueID, sizeof(this->miUniqueID)); }

  public:
    virtual int32_t Read(Stream &stream)
    {
        int32_t err = stream.Seek(4, stream.CUR);
        if (err < 0)
        {
            return err;
        }
        return Owner::Read_(stream) + 4;
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
            return Owner::Read_(stream) + 4;
        }
        return Owner::Read_(stream);
    }
    virtual int32_t Write(Stream &stream) const
    {
        int32_t size = 0;
        size += stream.Write(&size, sizeof(size));
        size += Owner::Write_(stream);
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
        size += Owner::Write_(stream);
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
    virtual ~Owner() {}

    int32_t miUniqueID;
    static constexpr bool IS_BLOCKED = true;
};
}; // namespace UID
}; // namespace TTH