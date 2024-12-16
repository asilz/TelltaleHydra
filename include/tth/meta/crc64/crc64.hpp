#pragma once

#include <inttypes.h>

constexpr const char *CRC64_GetTypeName(uint64_t crc);
constexpr uint64_t CRC64_CaseInsensitive(uint64_t crc, const char *buf);