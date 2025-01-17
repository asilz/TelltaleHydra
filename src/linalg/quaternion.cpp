#include <tth/linalg/quaternion.hpp>

namespace TTH
{
int32_t Quaternion::Read(Stream &stream)
{
    int32_t size = stream.Read(x);
    size += stream.Read(y);
    size += stream.Read(z);
    size += stream.Read(w);
    return size;
}

int32_t Quaternion::Write(Stream &stream) const
{
    int32_t size = stream.Write(x);
    size += stream.Write(y);
    size += stream.Write(z);
    size += stream.Write(w);
    return size;
}
}; // namespace TTH