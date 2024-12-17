#include <cerrno>
#include <cstdio>
#include <tth/convert/asset.hpp>
#include <tth/core/any.hpp>
#include <tth/core/log.hpp>
#include <tth/meta/animation/animation.hpp>
#include <tth/meta/container/dcarray.hpp>
#include <tth/meta/container/map.hpp>
#include <tth/meta/container/sarray.hpp>
#include <tth/meta/container/set.hpp>
#include <tth/meta/crc64/crc64.hpp>
#include <tth/meta/linalg/vector.hpp>
#include <tth/meta/meta.hpp>
#include <tth/meta/skeleton/skeleton.hpp>

int main(void)
{
    Stream stream = Stream("animation/sk61_javierAction_toStandA.anm", "rb");
    stream.SeekMetaHeaderEnd();

    Animation animation;
    animation.Read(stream, false);

    return 0;
}