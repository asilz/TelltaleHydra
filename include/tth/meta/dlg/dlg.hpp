#pragma once

#include <tth/meta/container/map.hpp>
#include <tth/meta/container/ptr.hpp>
#include <tth/meta/crc64/symbol.hpp>
#include <tth/meta/flags.hpp>
#include <tth/meta/string/string.hpp>

class JiraRecordManager
{
  private:
    inline int32_t Read_(Stream &stream)
    {
        int32_t size = 0;
        int32_t err;
        err = this->mRecords.Read(stream);
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
        err = this->mRecords.Write(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        return size;
    }

  public:
    int32_t Read(Stream &stream) { return Read_(stream); }
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
    int32_t Write(Stream &stream) const { return Write_(stream); }
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
    class Map<class String, class Ptr<class JiraRecord>, struct std::less<class String>> mRecords;
    static constexpr bool IS_BLOCKED = false;
};

class DlgObjIDOwner
{
  private:
    inline virtual int32_t Read_(Stream &stream)
    {
        int32_t size = 0;
        int32_t err;
        err = this->mDlgObjID.Read(stream);
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
        err = this->mDlgObjID.Write(stream);
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
    class DlgObjID mDlgObjID;
    static constexpr bool IS_BLOCKED = true;
};

class DlgObjID
{
  private:
    inline int32_t Read_(Stream &stream)
    {
        int32_t size = 0;
        int32_t err;
        err = this->mID.Read(stream);
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
        err = this->mID.Write(stream);
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
    class Symbol mID;
    static constexpr bool IS_BLOCKED = true;
};

class Dlg : public DlgObjIDOwner
{
  private:
    inline int32_t Read_(Stream &stream)
    {
        int32_t size = 0;
        int32_t err;
        err = DlgObjIDOwner::Read(stream, true);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = this->mName.Read(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        size += stream.Read(&this->mVersion, sizeof(this->mVersion));
        err = this->mDefFolderID.Read(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = this->mLangDB.Read(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        size += stream.Read(&this->mProjectID, sizeof(this->mProjectID));
        err = this->mResourceLocationID.Read(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        size += stream.Read(&this->mChronology, sizeof(this->mChronology));
        err = this->mFlags.Read(stream);
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
        err = this->mProdReportProps.Read(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = this->mJiraRecordManager.Read(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        size += stream.Read(&this->mbHasToolOnlyData, sizeof(this->mbHasToolOnlyData));
        return size;
    }
    inline int32_t Write_(Stream &stream) const
    {
        int32_t size = 0;
        int32_t err;
        err = DlgObjIDOwner::Write(stream, true);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = this->mName.Write(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        size += stream.Write(&this->mVersion, sizeof(this->mVersion));
        err = this->mDefFolderID.Write(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = this->mLangDB.Write(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        size += stream.Write(&this->mProjectID, sizeof(this->mProjectID));
        err = this->mResourceLocationID.Write(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        size += stream.Write(&this->mChronology, sizeof(this->mChronology));
        err = this->mFlags.Write(stream);
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
        err = this->mProdReportProps.Write(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = this->mJiraRecordManager.Write(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        size += stream.Write(&this->mbHasToolOnlyData, sizeof(this->mbHasToolOnlyData));
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
    class String mName;
    int32_t mVersion;
    class DlgObjID mDefFolderID;
    class LanguageDB mLangDB;
    uint32_t mProjectID;
    class Symbol mResourceLocationID;
    int32_t mChronology;
    class Flags mFlags;
    class DependencyLoader<1> mDependencies;
    class PropertySet mProdReportProps;
    class JiraRecordManager mJiraRecordManager;
    bool mbHasToolOnlyData;
    static constexpr bool IS_BLOCKED = true;
};

class DlgNodeText : public DlgNode
{
  private:
    inline virtual int32_t Read_(Stream &stream)
    {
        int32_t size = 0;
        int32_t err;
        err = DlgNode::Read(stream, true);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = this->mLangResProxy.Read(stream);
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
        err = DlgNode::Write(stream, true);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = this->mLangResProxy.Write(stream);
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
    class LanguageResProxy mLangResProxy;
    static constexpr bool IS_BLOCKED = true;
};
class DlgNodeStart : public DlgNode
{
  private:
    inline virtual int32_t Read_(Stream &stream)
    {
        int32_t size = 0;
        int32_t err;
        err = DlgNode::Read(stream, true);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = this->mProdReportProps.Read(stream);
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
        err = DlgNode::Write(stream, true);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = this->mProdReportProps.Write(stream);
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
    class PropertySet mProdReportProps;
    static constexpr bool IS_BLOCKED = true;
};
class DlgConditionalCase : public DlgChild
{
  private:
    inline virtual int32_t Read_(Stream &stream)
    {
        int32_t size = 0;
        int32_t err;
        err = DlgChild::Read(stream, true);
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
        err = DlgChild::Write(stream, true);
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
    static constexpr bool IS_BLOCKED = true;
};
class DlgNodeConditional : public DlgNode
{
  private:
    inline virtual int32_t Read_(Stream &stream)
    {
        int32_t size = 0;
        int32_t err;
        err = DlgNode::Read(stream, true);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = this->mCases.Read(stream);
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
        err = DlgNode::Write(stream, true);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = this->mCases.Write(stream);
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
    class DlgChildSetConditionalCase mCases;
    static constexpr bool IS_BLOCKED = true;
};
class DlgFolderChild : public DlgChild
{
  private:
    inline virtual int32_t Read_(Stream &stream)
    {
        int32_t size = 0;
        int32_t err;
        err = DlgChild::Read(stream, true);
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
        err = DlgChild::Write(stream, true);
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
    static constexpr bool IS_BLOCKED = true;
};
class DlgChildSetConditionalCase : public DlgChildSet
{
  private:
    inline virtual int32_t Read_(Stream &stream)
    {
        int32_t size = 0;
        int32_t err;
        err = DlgChildSet::Read(stream, true);
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
        err = DlgChildSet::Write(stream, true);
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
    static constexpr bool IS_BLOCKED = true;
};
class LanguageResProxy
{
  private:
    inline virtual int32_t Read_(Stream &stream)
    {
        int32_t size = 0;
        int32_t err;
        size += stream.Read(&this->mID, sizeof(this->mID));
        return size;
    }
    inline virtual int32_t Write_(Stream &stream) const
    {
        int32_t size = 0;
        int32_t err;
        size += stream.Write(&this->mID, sizeof(this->mID));
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
    uint32_t mID;
    static constexpr bool IS_BLOCKED = true;
};
class DlgNode : public DlgObjIDOwner, public DlgVisibilityConditionsOwner, public DlgObjectPropsOwner
{
  private:
    inline virtual int32_t Read_(Stream &stream)
    {
        int32_t size = 0;
        int32_t err;
        err = DlgObjIDOwner::Read(stream, true);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = DlgVisibilityConditionsOwner::Read(stream, true);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = DlgObjectPropsOwner::Read(stream, true);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = this->mPrev.Read(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = this->mNext.Read(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
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
        size += stream.Read(&this->mChainContextTypeID, sizeof(this->mChainContextTypeID));
        return size;
    }
    inline virtual int32_t Write_(Stream &stream) const
    {
        int32_t size = 0;
        int32_t err;
        err = DlgObjIDOwner::Write(stream, true);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = DlgVisibilityConditionsOwner::Write(stream, true);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = DlgObjectPropsOwner::Write(stream, true);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = this->mPrev.Write(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = this->mNext.Write(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
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
        size += stream.Write(&this->mChainContextTypeID, sizeof(this->mChainContextTypeID));
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
    class DlgNodeLink mPrev;
    class DlgNodeLink mNext;
    class Symbol mName;
    class Flags mFlags;
    int32_t mChainContextTypeID;
    static constexpr bool IS_BLOCKED = true;
};
class DlgDownstreamVisibilityConditions
{
  private:
    inline virtual int32_t Read_(Stream &stream)
    {
        int32_t size = 0;
        int32_t err;
        err = this->mNodeTypeFlags.Read(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        size += stream.Read(&this->mMaxNumNodeEvals, sizeof(this->mMaxNumNodeEvals));
        return size;
    }
    inline virtual int32_t Write_(Stream &stream) const
    {
        int32_t size = 0;
        int32_t err;
        err = this->mNodeTypeFlags.Write(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        size += stream.Write(&this->mMaxNumNodeEvals, sizeof(this->mMaxNumNodeEvals));
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
    class Flags mNodeTypeFlags;
    int32_t mMaxNumNodeEvals;
    static constexpr bool IS_BLOCKED = true;
};
class DlgVisibilityConditions
{
  private:
    inline virtual int32_t Read_(Stream &stream)
    {
        int32_t size = 0;
        int32_t err;
        size += stream.Read(&this->mbDiesOff, sizeof(this->mbDiesOff));
        err = this->mFlags.Read(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = this->mDownstreamVisCond.Read(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = this->mScriptVisCond.Read(stream);
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
        size += stream.Write(&this->mbDiesOff, sizeof(this->mbDiesOff));
        err = this->mFlags.Write(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = this->mDownstreamVisCond.Write(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = this->mScriptVisCond.Write(stream);
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
    bool mbDiesOff;
    class Flags mFlags;
    class DlgDownstreamVisibilityConditions mDownstreamVisCond;
    class String mScriptVisCond;
    static constexpr bool IS_BLOCKED = true;
};
class DlgVisibilityConditionsOwner
{
  private:
    inline virtual int32_t Read_(Stream &stream)
    {
        int32_t size = 0;
        int32_t err;
        err = this->mVisCond.Read(stream);
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
        err = this->mVisCond.Write(stream);
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
    class DlgVisibilityConditions mVisCond;
    static constexpr bool IS_BLOCKED = true;
};
class DlgNodeLink : public DlgObjIDOwner
{
  private:
    inline virtual int32_t Read_(Stream &stream)
    {
        int32_t size = 0;
        int32_t err;
        err = DlgObjIDOwner::Read(stream, true);
        if (err < 0)
        {
            return err;
        }
        size += err;
        size += stream.Read(&this->mRequiredCCType, sizeof(this->mRequiredCCType));
        return size;
    }
    inline virtual int32_t Write_(Stream &stream) const
    {
        int32_t size = 0;
        int32_t err;
        err = DlgObjIDOwner::Write(stream, true);
        if (err < 0)
        {
            return err;
        }
        size += err;
        size += stream.Write(&this->mRequiredCCType, sizeof(this->mRequiredCCType));
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
    int32_t mRequiredCCType;
    static constexpr bool IS_BLOCKED = true;
};
class DlgChainHead : public DlgObjIDOwner
{
  private:
    inline virtual int32_t Read_(Stream &stream)
    {
        int32_t size = 0;
        int32_t err;
        err = DlgObjIDOwner::Read(stream, true);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = this->mLink.Read(stream);
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
        err = DlgObjIDOwner::Write(stream, true);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = this->mLink.Write(stream);
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
    class DlgNodeLink mLink;
    static constexpr bool IS_BLOCKED = true;
};
class DlgChild : public DlgChainHead, public DlgVisibilityConditionsOwner, public DlgObjectPropsOwner
{
  private:
    inline virtual int32_t Read_(Stream &stream)
    {
        int32_t size = 0;
        int32_t err;
        err = DlgChainHead::Read(stream, true);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = this->mName.Read(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = DlgVisibilityConditionsOwner::Read(stream, true);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = DlgObjectPropsOwner::Read(stream, true);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = this->mParent.Read(stream);
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
        err = DlgChainHead::Write(stream, true);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = this->mName.Write(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = DlgVisibilityConditionsOwner::Write(stream, true);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = DlgObjectPropsOwner::Write(stream, true);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = this->mParent.Write(stream);
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
    class Symbol mName;
    class DlgNodeLink mParent;
    static constexpr bool IS_BLOCKED = true;
};
class DlgObjectProps
{
  private:
    inline virtual int32_t Read_(Stream &stream)
    {
        int32_t size = 0;
        int32_t err;
        err = this->mFlags.Read(stream);
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
        err = this->mFlags.Write(stream);
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
    class Flags mFlags;
    static constexpr bool IS_BLOCKED = true;
};
class DlgObjectPropsOwner
{
  private:
    inline virtual int32_t Read_(Stream &stream)
    {
        int32_t size = 0;
        int32_t err;
        err = this->mDlgObjectProps.Read(stream);
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
        err = this->mDlgObjectProps.Write(stream);
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
    class DlgObjectProps mDlgObjectProps;
    static constexpr bool IS_BLOCKED = true;
};
class DlgChildSet
{
  private:
    inline virtual int32_t Read_(Stream &stream)
    {
        int32_t size = 0;
        int32_t err;
        err = this->mChildren.Read(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = this->mParent.Read(stream);
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
        err = this->mChildren.Write(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = this->mParent.Write(stream);
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
    class DCArray<class Ptr<class DlgChild>> mChildren;
    class DlgNodeLink mParent;
    static constexpr bool IS_BLOCKED = false;
};

class DlgFolder : public DlgObjIDOwner, public DlgObjectPropsOwner, public DlgChildSet
{
  private:
    inline virtual int32_t Read_(Stream &stream)
    {
        int32_t size = 0;
        int32_t err;
        err = DlgObjIDOwner::Read(stream, true);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = DlgObjectPropsOwner::Read(stream, true);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = DlgChildSet::Read(stream, true);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = this->mName.Read(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = this->mProdReportProps.Read(stream);
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
        err = DlgObjIDOwner::Write(stream, true);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = DlgObjectPropsOwner::Write(stream, true);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = DlgChildSet::Write(stream, true);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = this->mName.Write(stream);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = this->mProdReportProps.Write(stream);
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
    class Symbol mName;
    class PropertySet mProdReportProps;
    static constexpr bool IS_BLOCKED = true;
};