#pragma once

#include <cstdint>

constexpr const char *CRC64_GetTypeName(uint64_t crc);
uint64_t CRC64_CaseInsensitive(uint64_t crc, const char *buf);