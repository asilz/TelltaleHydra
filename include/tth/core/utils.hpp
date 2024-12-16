#pragma once

#define TTH_STRINGIFY_(T) #T

template <typename T> const char *GetTypeName() { return TTH_STRINGIFY_(T); } // TODO: Fix this