#include <tth/meta/enum/enumbase.hpp>
#include <tth/meta/linalg/vector.hpp>
#include <tth/meta/string/string.hpp>

namespace TTH
{

class EnlightenModule
{
  private:
    inline int32_t Read_(Stream &stream)
    {
        int32_t size = 0;
        int32_t err;
        return size;
    }
    inline int32_t Write_(Stream &stream) const
    {
        int32_t size = 0;
        int32_t err;
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
    static constexpr bool IS_BLOCKED = false;

    struct EnumeProbeResolution : public EnumBase
    {
      private:
        inline int32_t Read_(Stream &stream)
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
        inline int32_t Write_(Stream &stream) const
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
        int32_t mVal;
        static constexpr bool IS_BLOCKED = true;
    };

    struct EnumeQuality : public EnumBase
    {
      private:
        inline int32_t Read_(Stream &stream)
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
        inline int32_t Write_(Stream &stream) const
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
        int32_t mVal;
        static constexpr bool IS_BLOCKED = true;
    };

    struct EnumeDistributedBuildSystem : public EnumBase
    {
      private:
        inline int32_t Read_(Stream &stream)
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
        inline int32_t Write_(Stream &stream) const
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
        int32_t mVal;
        static constexpr bool IS_BLOCKED = false;
    };
    struct EnumeSceneOptimisationMode : public EnumBase
    {
      private:
        inline int32_t Read_(Stream &stream)
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
        inline int32_t Write_(Stream &stream) const
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
        int32_t mVal;
        static constexpr bool IS_BLOCKED = false;
    };
    struct EnumeBackfaceType : public EnumBase
    {
      private:
        inline int32_t Read_(Stream &stream)
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
        inline int32_t Write_(Stream &stream) const
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
        int32_t mVal;
        static constexpr bool IS_BLOCKED = false;
    };
    struct EnumeAutoUVSimplificationMode : public EnumBase
    {
      private:
        inline int32_t Read_(Stream &stream)
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
        inline int32_t Write_(Stream &stream) const
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
        int32_t mVal;
        static constexpr bool IS_BLOCKED = false;
    };
    struct EnumeProbeSampleMethod : public EnumBase
    {
      private:
        inline int32_t Read_(Stream &stream)
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
        inline int32_t Write_(Stream &stream) const
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
        int32_t mVal;
        static constexpr bool IS_BLOCKED = false;
    };
    struct EnumeDisplayQuality : public EnumBase
    {
      private:
        inline int32_t Read_(Stream &stream)
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
        inline int32_t Write_(Stream &stream) const
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
        int32_t mVal;
        static constexpr bool IS_BLOCKED = false;
    };
    struct EnumeRadiositySampleRate : public EnumBase
    {
      private:
        inline int32_t Read_(Stream &stream)
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
        inline int32_t Write_(Stream &stream) const
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
        int32_t mVal;
        static constexpr bool IS_BLOCKED = false;
    };
    struct EnumeUpdateMethodWithDefault : public EnumBase
    {
      private:
        inline int32_t Read_(Stream &stream)
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
        inline int32_t Write_(Stream &stream) const
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
        int32_t mVal;
        static constexpr bool IS_BLOCKED = false;
    };
    struct EnumeProbeResolutionWithDefault : public EnumBase
    {
      private:
        inline int32_t Read_(Stream &stream)
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
        inline int32_t Write_(Stream &stream) const
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
        int32_t mVal;
        static constexpr bool IS_BLOCKED = false;
    };
    struct EnumeAgentUsage : public EnumBase
    {
      private:
        inline int32_t Read_(Stream &stream)
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
        inline int32_t Write_(Stream &stream) const
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
        int32_t mVal;
        static constexpr bool IS_BLOCKED = false;
    };

    struct EnlightenSystemSettings
    {
      private:
        inline int32_t Read_(Stream &stream)
        {
            int32_t size = 0;
            int32_t err;
            err = this->mDefaultQuality.Read(stream);
            if (err < 0)
            {
                return err;
            }
            size += err;
            err = this->mAdaptiveProbeResolution.Read(stream);
            if (err < 0)
            {
                return err;
            }
            size += err;
            size += stream.Read(&this->mDisableEnlighten, sizeof(this->mDisableEnlighten));
            return size;
        }
        inline int32_t Write_(Stream &stream) const
        {
            int32_t size = 0;
            int32_t err;
            err = this->mDefaultQuality.Write(stream);
            if (err < 0)
            {
                return err;
            }
            size += err;
            err = this->mAdaptiveProbeResolution.Write(stream);
            if (err < 0)
            {
                return err;
            }
            size += err;
            size += stream.Write(&this->mDisableEnlighten, sizeof(this->mDisableEnlighten));
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
        struct EnumeQuality mDefaultQuality;
        struct EnumeProbeResolution mAdaptiveProbeResolution;
        bool mDisableEnlighten;
        static constexpr bool IS_BLOCKED = true;
    };

    struct EnlightenCubemapSettings
    {
      private:
        inline int32_t Read_(Stream &stream)
        {
            int32_t size = 0;
            int32_t err;
            size += stream.Read(&this->mFaceWidth, sizeof(this->mFaceWidth));
            err = this->mBoxOrigin.Read(stream);
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
            size += stream.Write(&this->mFaceWidth, sizeof(this->mFaceWidth));
            err = this->mBoxOrigin.Write(stream);
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
        int32_t mFaceWidth;
        class Vector3 mBoxOrigin;
        static constexpr bool IS_BLOCKED = true;
    };
    struct EnlightenAdaptiveProbeVolumeSettings
    {
      private:
        inline int32_t Read_(Stream &stream)
        {
            int32_t size = 0;
            int32_t err;
            err = this->mQuality.Read(stream);
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
            err = this->mQuality.Write(stream);
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
        struct EnumeQuality mQuality;
        static constexpr bool IS_BLOCKED = true;
    };
    struct EnlightenAutoProbeVolumeSettings
    {
      private:
        inline int32_t Read_(Stream &stream)
        {
            int32_t size = 0;
            int32_t err;
            err = this->mQuality.Read(stream);
            if (err < 0)
            {
                return err;
            }
            size += err;
            size += stream.Read(&this->mMinProbeSetSize, sizeof(this->mMinProbeSetSize));
            size += stream.Read(&this->mMergingThreshold, sizeof(this->mMergingThreshold));
            size += stream.Read(&this->mMinProbeSpacing, sizeof(this->mMinProbeSpacing));
            size += stream.Read(&this->mMaxProbeSpacing, sizeof(this->mMaxProbeSpacing));
            return size;
        }
        inline int32_t Write_(Stream &stream) const
        {
            int32_t size = 0;
            int32_t err;
            err = this->mQuality.Write(stream);
            if (err < 0)
            {
                return err;
            }
            size += err;
            size += stream.Write(&this->mMinProbeSetSize, sizeof(this->mMinProbeSetSize));
            size += stream.Write(&this->mMergingThreshold, sizeof(this->mMergingThreshold));
            size += stream.Write(&this->mMinProbeSpacing, sizeof(this->mMinProbeSpacing));
            size += stream.Write(&this->mMaxProbeSpacing, sizeof(this->mMaxProbeSpacing));
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
        struct EnumeQuality mQuality;
        int32_t mMinProbeSetSize;
        float mMergingThreshold;
        int32_t mMinProbeSpacing;
        int32_t mMaxProbeSpacing;
        static constexpr bool IS_BLOCKED = true;
    };
    struct EnlightenProbeVolumeSettings
    {
      private:
        inline int32_t Read_(Stream &stream)
        {
            int32_t size = 0;
            int32_t err;
            err = this->mQuality.Read(stream);
            if (err < 0)
            {
                return err;
            }
            size += err;
            err = this->mLightmapType.Read(stream);
            if (err < 0)
            {
                return err;
            }
            size += err;
            err = this->mResolution.Read(stream);
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
            err = this->mQuality.Write(stream);
            if (err < 0)
            {
                return err;
            }
            size += err;
            err = this->mLightmapType.Write(stream);
            if (err < 0)
            {
                return err;
            }
            size += err;
            err = this->mResolution.Write(stream);
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
        struct EnumeQuality mQuality;
        class String mLightmapType;
        class Vector3 mResolution;
        static constexpr bool IS_BLOCKED = true;
    };
    struct EnlightenLightSettings
    {
      private:
        inline int32_t Read_(Stream &stream)
        {
            int32_t size = 0;
            int32_t err;
            size += stream.Read(&this->mEnlightenSaturation, sizeof(this->mEnlightenSaturation));
            size += stream.Read(&this->mEnlightenOnly, sizeof(this->mEnlightenOnly));
            size += stream.Read(&this->mCastDynamicEnlightenShadows, sizeof(this->mCastDynamicEnlightenShadows));
            return size;
        }
        inline int32_t Write_(Stream &stream) const
        {
            int32_t size = 0;
            int32_t err;
            size += stream.Write(&this->mEnlightenSaturation, sizeof(this->mEnlightenSaturation));
            size += stream.Write(&this->mEnlightenOnly, sizeof(this->mEnlightenOnly));
            size += stream.Write(&this->mCastDynamicEnlightenShadows, sizeof(this->mCastDynamicEnlightenShadows));
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
        float mEnlightenSaturation;
        bool mEnlightenOnly;
        bool mCastDynamicEnlightenShadows;
        static constexpr bool IS_BLOCKED = true;
    };

    struct EnumeQualityWithDefault : public EnumBase
    {
      private:
        inline int32_t Read_(Stream &stream)
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
        inline int32_t Write_(Stream &stream) const
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
        int32_t mVal;
        static constexpr bool IS_BLOCKED = true;
    };
    struct EnumeUpdateMethod : public EnumBase
    {
      private:
        inline int32_t Read_(Stream &stream)
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
        inline int32_t Write_(Stream &stream) const
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
        int32_t mVal;
        static constexpr bool IS_BLOCKED = true;
    };
    struct EnumeInstanceType : public EnumBase
    {
      private:
        inline int32_t Read_(Stream &stream)
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
        inline int32_t Write_(Stream &stream) const
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
        int32_t mVal;
        static constexpr bool IS_BLOCKED = true;
    };
    struct EnumeSimplifyMode : public EnumBase
    {
      private:
        inline int32_t Read_(Stream &stream)
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
        inline int32_t Write_(Stream &stream) const
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
        int32_t mVal;
        static constexpr bool IS_BLOCKED = false;
    };
    struct EnlightenPrimitiveSettings
    {
      private:
        inline int32_t Read_(Stream &stream)
        {
            int32_t size = 0;
            int32_t err;
            err = this->mSystemId.Read(stream);
            if (err < 0)
            {
                return err;
            }
            size += err;
            err = this->mEnlightenLightingMode.Read(stream);
            if (err < 0)
            {
                return err;
            }
            size += err;
            err = this->mEnlightenUpdateMethod.Read(stream);
            if (err < 0)
            {
                return err;
            }
            size += err;
            err = this->mEnlightenQuality.Read(stream);
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
            err = this->mSystemId.Write(stream);
            if (err < 0)
            {
                return err;
            }
            size += err;
            err = this->mEnlightenLightingMode.Write(stream);
            if (err < 0)
            {
                return err;
            }
            size += err;
            err = this->mEnlightenUpdateMethod.Write(stream);
            if (err < 0)
            {
                return err;
            }
            size += err;
            err = this->mEnlightenQuality.Write(stream);
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
        class String mSystemId;
        struct EnumeInstanceType mEnlightenLightingMode;
        struct EnumeUpdateMethod mEnlightenUpdateMethod;
        struct EnumeQualityWithDefault mEnlightenQuality;
        static constexpr bool IS_BLOCKED = true;
    };
    struct EnlightenMeshSettings
    {
        struct AutoUVSettings
        {
          private:
            inline int32_t Read_(Stream &stream)
            {
                int32_t size = 0;
                int32_t err;
                err = this->mSimplificationMode.Read(stream);
                if (err < 0)
                {
                    return err;
                }
                size += err;
                size += stream.Read(&this->mMaxDistance, sizeof(this->mMaxDistance));
                size += stream.Read(&this->mMaxInitialNormalDeviation, sizeof(this->mMaxInitialNormalDeviation));
                size += stream.Read(&this->mMaxGeneralNormalDeviation, sizeof(this->mMaxGeneralNormalDeviation));
                size += stream.Read(&this->mExpansionFactor, sizeof(this->mExpansionFactor));
                size += stream.Read(&this->mSignificantAreaRatio, sizeof(this->mSignificantAreaRatio));
                return size;
            }
            inline int32_t Write_(Stream &stream) const
            {
                int32_t size = 0;
                int32_t err;
                err = this->mSimplificationMode.Write(stream);
                if (err < 0)
                {
                    return err;
                }
                size += err;
                size += stream.Write(&this->mMaxDistance, sizeof(this->mMaxDistance));
                size += stream.Write(&this->mMaxInitialNormalDeviation, sizeof(this->mMaxInitialNormalDeviation));
                size += stream.Write(&this->mMaxGeneralNormalDeviation, sizeof(this->mMaxGeneralNormalDeviation));
                size += stream.Write(&this->mExpansionFactor, sizeof(this->mExpansionFactor));
                size += stream.Write(&this->mSignificantAreaRatio, sizeof(this->mSignificantAreaRatio));
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
            struct ::EnlightenModule::EnumeSimplifyMode mSimplificationMode;
            float mMaxDistance;
            float mMaxInitialNormalDeviation;
            float mMaxGeneralNormalDeviation;
            float mExpansionFactor;
            float mSignificantAreaRatio;
            static constexpr bool IS_BLOCKED = false;
        };

      private:
        inline int32_t Read_(Stream &stream)
        {
            int32_t size = 0;
            int32_t err;
            err = this->mEnlightenLightingMode.Read(stream);
            if (err < 0)
            {
                return err;
            }
            size += err;
            err = this->mAutoUVSettings.Read(stream);
            if (err < 0)
            {
                return err;
            }
            size += err;
            err = this->mEnlightenQuality.Read(stream);
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
            err = this->mEnlightenLightingMode.Write(stream);
            if (err < 0)
            {
                return err;
            }
            size += err;
            err = this->mAutoUVSettings.Write(stream);
            if (err < 0)
            {
                return err;
            }
            size += err;
            err = this->mEnlightenQuality.Write(stream);
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
        struct ::EnlightenModule::EnumeInstanceType mEnlightenLightingMode;
        struct AutoUVSettings mAutoUVSettings;
        struct ::EnlightenModule::EnumeQuality mEnlightenQuality;
        static constexpr bool IS_BLOCKED = false;
    };
};

} // namespace TTH