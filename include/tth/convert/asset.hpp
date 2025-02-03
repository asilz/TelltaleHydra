#pragma once

#include <tth/animation/animation.hpp>
#include <tth/d3dmesh/d3dmesh.hpp>
#include <tth/skeleton/skeleton.hpp>

namespace TTH
{

errno_t ExportAsset(const char *resultPath, Skeleton skeleton, Animation *animations, D3DMesh *meshes, size_t animationCount, size_t meshCount);

};