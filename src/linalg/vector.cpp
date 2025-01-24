#include <tth/linalg/vector.hpp>

namespace TTH
{
int32_t Vector4::Read(Stream &stream)
{
    int32_t size = stream.Read(x);
    size += stream.Read(y);
    size += stream.Read(z);
    size += stream.Read(w);
    return size;
}

int32_t Vector4::Write(Stream &stream) const
{
    int32_t size = stream.Write(x);
    size += stream.Write(y);
    size += stream.Write(z);
    size += stream.Write(w);
    return size;
}
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

int32_t Vector2::Read(Stream &stream)
{
    int32_t size = stream.Read(x);
    size += stream.Read(y);
    return size;
}

int32_t Vector2::Write(Stream &stream) const
{
    int32_t size = stream.Write(x);
    size += stream.Write(y);
    return size;
}
}; // namespace TTH