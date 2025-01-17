#include <tth/linalg/vector.hpp>

namespace TTH
{
int32_t Vector3::Read(Stream &stream)
{
    int32_t size = stream.Read(x);
    size += stream.Read(y);
    size += stream.Read(z);
    return size;
}

int32_t Vector3::Write(Stream &stream) const
{
    int32_t size = stream.Write(x);
    size += stream.Write(y);
    size += stream.Write(z);
    return size;
}
}; // namespace TTH