#pragma once

#include <tth/meta/animation/animation.hpp>
#include <tth/meta/d3dmesh/d3dmesh.hpp>
#include <tth/meta/skeleton/skeleton.hpp>

namespace TTH
{

errno_t ExportAsset(char *resultPath, const Skeleton &skeleton, const Animation &animation, const D3DMesh &mesh);

};