#pragma once

namespace TTH
{

#define TTH_STRINGIFY_(a) #a

template <typename T> const char *GetTypeName() { return TTH_STRINGIFY_(T); } // TODO: Fix this

}; // namespace TTH