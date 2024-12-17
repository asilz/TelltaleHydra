#pragma once

#include <cstdint>

#define TTH_ERRNO_BASE (INT16_MAX + 1)

/* The datatypes stored within telltale files can vary depending on hashes, if a datatype that a function expected to be found wasn't found, the function will return this error code */
#define TTH_TYPE_NOT_FOUND TTH_ERRNO_BASE

typedef int_least32_t errno_t;