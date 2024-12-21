#pragma once

#include <tth/meta/animation/animation.hpp>
#include <tth/meta/d3dmesh/d3dmesh.hpp>
#include <tth/meta/skeleton/skeleton.hpp>

namespace TTH
{

errno_t ExportAsset(const char *resultPath, const Skeleton &skeleton, const Animation *animations, const D3DMesh *meshes, size_t animationCount, size_t meshCount);

};