#include <tth/linalg/transform.hpp>

namespace TTH
{
int32_t Transform::Read(Stream &stream)
{
    int32_t size = stream.Read(mRot);
    size += stream.Read(mTrans);
    return size;
}

int32_t Transform::Write(Stream &stream) const
{
    int32_t size = stream.Write(mRot);
    size += stream.Write(mTrans);
    return size;
}
}; // namespace TTH