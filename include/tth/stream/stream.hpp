#pragma once

#include <cstdio>
#include <tth/core/errno.hpp>

/* Stream wrapper */
class Stream
{
  private:
    FILE *stream;

  public:
    static constexpr int SET = 0;
    static constexpr int CUR = 1;
    static constexpr int END = 2;

    errno_t SeekMetaHeaderEnd(); // TODO: Remove this and implement channel thing
    uint32_t Read(void *buf, size_t size);
    uint32_t Write(const void *buf, size_t size);
    size_t tell();
    errno_t Seek(int64_t offset, int whence);
    Stream(const char *path, const char *mode);
    ~Stream();
};
