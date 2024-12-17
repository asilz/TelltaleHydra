#include <assert.h>
#include <tth/stream/stream.hpp>

namespace TTH
{

uint32_t Stream::Read(void *buf, size_t size) { return fread(buf, 1, size, stream); }

uint32_t Stream::Write(const void *buf, size_t size) { return fwrite(buf, 1, size, stream); }

errno_t Stream::Seek(int64_t offset, int whence)
{
    assert(offset < 16576512 && offset > -16576512);
    return fseek(stream, offset, whence);
}

size_t Stream::tell() { return ftell(stream); }

Stream::Stream(const char *path, const char *mode) : stream(fopen(path, mode)) {}

Stream::~Stream() { fclose(stream); }

errno_t Stream::SeekMetaHeaderEnd()
{
    errno_t err = this->Seek(16, this->SET);
    if (err < 0)
    {
        return err;
    }
    uint32_t entryCount;
    this->Read(&entryCount, sizeof(entryCount));

    return this->Seek(entryCount * 12, this->CUR);
}
} // namespace TTH