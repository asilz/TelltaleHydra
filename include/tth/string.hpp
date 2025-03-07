#pragma once

#include <string>
#include <tth/crypto/crc64.hpp>
#include <tth/stream/stream.hpp>

namespace TTH
{
class String : public std::string
{
  public:
    int32_t Read(Stream &stream)
    {
        int32_t size;
        int32_t err = stream.Read(size);
        if (err < 0)
        {
            return err;
        }
        this->resize(size);
        err = stream.Read(static_cast<void *>(this->data()), size);
        if (err < 0)
        {
            return err;
        }
        size += err;
        return size;
    }
    int32_t Write(Stream &stream) const
    {
        int32_t size = this->size();
        int32_t err = stream.Write(size);
        if (err < 0)
        {
            return err;
        }
        size += err;

        err = stream.Write(static_cast<const void *>(this->data()), size - sizeof(int32_t));
        if (err < 0)
        {
            return err;
        }
        size += err;
        return size;
    }
    static constexpr bool IS_BLOCKED = true;
    static constexpr uint64_t GetTypeCRC64() { return CRC64_CaseInsensitive("String"); }
};
}; // namespace TTH