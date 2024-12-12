#include <tth/core/any.hpp>
#include <tth/core/log.hpp>
#include <tth/meta/container/dcarray.hpp>
#include <tth/meta/container/map.hpp>
#include <tth/meta/container/sarray.hpp>
#include <tth/meta/container/set.hpp>
#include <tth/meta/meta.hpp>

int main(void)
{
    TTH_LOG_INFO("hello\n");

    Any any = Any(2);

    float *a = any.GetTypePtr<float>();
    int *b = any.GetTypePtr<int>();

    return 0;
}