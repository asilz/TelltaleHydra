#include <d3dmesh/d3dmesh.hpp>
#include <tth/container/dcarray.hpp>
#include <tth/core/any.hpp>
#include <tth/crypto/crc64.hpp>
#include <tth/d3dmesh/d3dmesh.hpp>
#include <tth/flags.hpp>
#include <tth/handle.hpp>
#include <tth/stream/stream.hpp>
#include <tth/string.hpp>
#include <tth/toolprops.hpp>

namespace TTH
{

class D3DMesh::Impl
{
  public:
    int32_t Read(Stream &stream)
    {
        int32_t size = 0;
        int32_t err;
        err = stream.Read(mName);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Read(mVersion);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Read(mToolProps);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Read(mLightmapGlobalScale);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Read(mLightmapTexCoordVersion);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Read(mLODParamCRC);
        if (err < 0)
        {
            return err;
        }
        size += err;

        err = stream.Read(mAsyncResourceCount);
        if (err < 0)
        {
            return err;
        }
        size += err;

        mAsyncResources = new AsyncResource[mAsyncResourceCount];
        for (uint32_t i = 0; i < mAsyncResourceCount; ++i)
        {
            size += stream.Read(mAsyncResources[i].nameHash);
            size += stream.Read(mAsyncResources[i].typeHash);
            mAsyncResources[i].resource = Any(mAsyncResources[i].typeHash.mCRC64);
            size += stream.Read(mAsyncResources[i].resource);
        }

        err = stream.Read(unknown);
        if (err < 0)
        {
            return err;
        }
        size += err;

        char isOcclusionMeshData;
        err = stream.Read(isOcclusionMeshData);
        if (err < 0)
        {
            return err;
        }
        size += err;

        if (isOcclusionMeshData == '1')
        {
            this->mpOcclusionMeshData = new T3OcclusionMeshData();
            size += stream.Read(*mpOcclusionMeshData, true);
        }
        else
        {
            this->mpOcclusionMeshData = nullptr;
        }

        err = stream.Read(mMeshData);
        if (err < 0)
        {
            return err;
        }
        size += err;

        size_t startOfAsync = stream.tell();
        stream.Seek(0, stream.END);
        this->asyncSize = stream.tell() - startOfAsync;
        stream.Seek(startOfAsync, stream.SET);

        this->async = new uint8_t[this->asyncSize];
        size += stream.Read((void *)async, this->asyncSize);

        return size;
    }
    int32_t Write(Stream &stream) const
    {
        int32_t size = 0;
        int32_t err;
        err = stream.Write(mName);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Write(mVersion);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Write(mToolProps);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Write(mLightmapGlobalScale);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Write(mLightmapTexCoordVersion);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Write(mLODParamCRC);
        if (err < 0)
        {
            return err;
        }
        size += err;
        return size;
    }

    struct AsyncResource
    {
        Symbol nameHash;
        Symbol typeHash;
        Any resource;

        AsyncResource() : nameHash(Symbol()), typeHash(Symbol()), resource(Any()) {}
    };

    class String mName;
    int32_t mVersion;
    class ToolProps mToolProps;
    float mLightmapGlobalScale;
    int32_t mLightmapTexCoordVersion;
    uint64_t mLODParamCRC;

    uint32_t mAsyncResourceCount;
    AsyncResource *mAsyncResources;
    int32_t unknown;
    T3OcclusionMeshData *mpOcclusionMeshData;
    T3MeshData mMeshData;
    size_t asyncSize;
    uint8_t *async;

    Impl()
        : mVersion(-1), mToolProps(false), mLightmapGlobalScale(-1.0f), mLightmapTexCoordVersion(-1), mLODParamCRC(0), mAsyncResourceCount(0), mAsyncResources(nullptr), unknown(-1),
          mpOcclusionMeshData(nullptr), asyncSize(0), async(nullptr)
    {
    }

    ~Impl()
    {
        delete[] mAsyncResources;
        delete mpOcclusionMeshData;
        delete[] async;
    }

    static constexpr bool IS_BLOCKED = true;
};

errno_t D3DMesh::Create()
{
    impl = new Impl();
    return 0;
}
void D3DMesh::Destroy() { delete impl; }

int32_t D3DMesh::Read(Stream &stream) noexcept { return impl->Read(stream); }
int32_t D3DMesh::Write(Stream &stream) const noexcept { return impl->Write(stream); }

size_t D3DMesh::GetLODCount() const noexcept { return impl->mMeshData.mLODs.size(); }
size_t D3DMesh::GetBatchCount(size_t LODIndex) const noexcept { return impl->mMeshData.mLODs[LODIndex].mBatches[0].size(); }
size_t D3DMesh::GetVertexCount() const noexcept { return impl->mMeshData.mVertexCount; }
size_t D3DMesh::GetVertexCount(size_t LODIndex, size_t batchIndex) const noexcept
{
    return impl->mMeshData.mLODs[LODIndex].mBatches[0][batchIndex].mMaxVertIndex - impl->mMeshData.mLODs[LODIndex].mBatches[0][batchIndex].mMaxVertIndex;
}

}; // namespace TTH