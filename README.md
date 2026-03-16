# TelltaleHydra

## Building
### Windows
```
git clone https://github.com/asilz/TelltaleHydra.git --recurse-submodules
cd TelltaleHydra
mkdir build
cmake -B build -DCMAKE_CXX_COMPILER=cl -DCMAKE_C_COMPILER=cl -DCMAKE_BUILD_TYPE=Release -DUSE_STATIC_CRT=OFF -DBUILD_SHARED_LIBS=OFF
cmake --build build --config Release
```
### Executable
If you wish to build an executable (.exe), you should add the following to the bottom of the CMakeLists.txt in the root directory (called TelltaleHydra).
```
add_executable(my_executable)
target_sources(my_executable PRIVATE main.cpp)
target_link_libraries(my_executable hydra)
```
Then add a main.cpp file to the root directory (called TelltaleHydra). An example of a main.cpp file is
```
#include <cerrno>
#include <cstdio>
#include <tth/animation/animation.hpp>
#include <tth/convert/asset.hpp>
#include <tth/core/any.hpp>
#include <tth/core/log.hpp>
#include <tth/d3dmesh/d3dmesh.hpp>
#include <tth/skeleton/skeleton.hpp>

using namespace TTH;

int main(void)
{

    Stream stream = Stream("sk61_javier.skl", "rb");
    stream.SeekMetaHeaderEnd();
    Skeleton skeleton;
    skeleton.Create();
    stream.Read(skeleton, false);

    Animation animation[4];
    animation[0].Create();
    {
        Stream streamAnimation = Stream("sk61_javierStandA_toSit.anm", "rb");
        streamAnimation.SeekMetaHeaderEnd();
        streamAnimation.Read(animation[0], false);
    }
    animation[1].Create();
    {
        Stream streamAnimation = Stream("sk61_javierStandHoldBeer_toLeanPorchHoldBeer.anm", "rb");
        streamAnimation.SeekMetaHeaderEnd();
        streamAnimation.Read(animation[1], false);
    }
    animation[2].Create();
    {
        Stream streamAnimation = Stream("sk61_javierSupine_rubJaw.anm", "rb");
        streamAnimation.SeekMetaHeaderEnd();
        streamAnimation.Read(animation[2], false);
    }
    animation[3].Create();
    {
        Stream streamAnimation = Stream("sk61_javierSlide.anm", "rb");
        streamAnimation.SeekMetaHeaderEnd();
        streamAnimation.Read(animation[3], false);
    }

    D3DMesh mesh[4];
    mesh[0].Create();
    {
        Stream streamMesh = Stream("sk61_javier_bodyUpper.d3dmesh", "rb");
        streamMesh.SeekMetaHeaderEnd();
        streamMesh.Read(mesh[0], false);
    }

    mesh[1].Create();
    {
        Stream streamMesh = Stream("sk61_javier_bodyLower.d3dmesh", "rb");
        streamMesh.SeekMetaHeaderEnd();
        streamMesh.Read(mesh[1], false);
    }

    mesh[2].Create();
    {
        Stream streamMesh = Stream("sk61_javier_head.d3dmesh", "rb");
        streamMesh.SeekMetaHeaderEnd();
        streamMesh.Read(mesh[2], false);
    }

    mesh[3].Create();
    {
        Stream streamMesh = Stream("sk61_javier_eyesMouth.d3dmesh", "rb");
        streamMesh.SeekMetaHeaderEnd();
        streamMesh.Read(mesh[3], false);
    }

    errno_t err = ExportAsset("assimpTWD.glb", skeleton, animation, mesh, 4, 4);

    skeleton.Destroy();
    animation[0].Destroy();
    mesh[0].Destroy();
    animation[1].Destroy();
    mesh[1].Destroy();
    animation[2].Destroy();
    mesh[2].Destroy();
    animation[3].Destroy();
    mesh[3].Destroy();
    return 0;
}
```
And then rebuild
