#pragma once

#include <tth/animation/animation.hpp>
#include <tth/skeleton/skeleton.hpp>

namespace TTH
{

errno_t ExportAsset(const char *resultPath, Skeleton skeleton, Animation *animations, size_t animationCount, size_t meshCount);

};