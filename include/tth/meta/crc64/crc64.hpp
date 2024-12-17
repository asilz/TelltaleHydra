#pragma once

#include <cstdint>

namespace TTH
{

constexpr const char *CRC64_GetTypeName(uint64_t crc);
uint64_t CRC64_CaseInsensitive(uint64_t crc, const char *buf);

} // namespace TTH