#pragma once

#include <cstdio>

namespace TTH
{

#ifndef TTE_LOG_LEVEL
#define TTE_LOG_LEVEL 3
#endif

#if TTE_LOG_LEVEL > 2
#define TTH_LOG_INFO(...) printf(__VA_ARGS__);
#else
#define TTH_LOG_INFO(...)
#endif

#if TTE_LOG_LEVEL > 1
#define TTH_LOG_WARNING(...) printf(__VA_ARGS__);
#else
#define TTH_LOG_WARNING(...)
#endif

#if TTE_LOG_LEVEL > 0
#define TTH_LOG_ERROR(...) printf(__VA_ARGS__);
#else
#define TTH_LOG_ERROR(...)
#endif

} // namespace TTH