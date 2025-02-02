#include <d3dmesh.hpp>

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
        err = stream.Read(mLightmapUVGenerationType);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Read(mLightmapTexelAreaPerSurfaceArea);
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
        err = stream.Read(mLightmapTextureWidth);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Read(mLightmapTextureHeight);
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
        err = stream.Write(mLightmapUVGenerationType);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Write(mLightmapTexelAreaPerSurfaceArea);
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
        err = stream.Write(mLightmapTextureWidth);
        if (err < 0)
        {
            return err;
        }
        size += err;
        err = stream.Write(mLightmapTextureHeight);
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
    T3MeshData mMeshData;
    class ToolProps mToolProps;
    int32_t mLightmapUVGenerationType;
    float mLightmapTexelAreaPerSurfaceArea;
    float mLightmapGlobalScale;
    int32_t mLightmapTexCoordVersion;
    uint32_t mLightmapTextureWidth;
    uint32_t mLightmapTextureHeight;

    uint32_t mAsyncResourceCount;
    AsyncResource *mAsyncResources;
    int32_t unknown;
    size_t asyncSize;
    uint8_t *async;

    static constexpr bool IS_BLOCKED = true;

    Impl()
        : mVersion(-1), mLightmapUVGenerationType(-1), mLightmapTexelAreaPerSurfaceArea(-1.0f), mLightmapGlobalScale(-1.0f), mLightmapTexCoordVersion(-1), mLightmapTextureWidth(0),
          mLightmapTextureHeight(0), mAsyncResourceCount(0), mAsyncResources(nullptr), unknown(-1)
    {
    }

    ~Impl()
    {
        delete[] mAsyncResources;
        delete[] async;
    }

    size_t GetVertexCount(size_t LODIndex, size_t batchIndex) const noexcept
    {
        return mMeshData.mLODs[LODIndex].mBatches[0][batchIndex].mMaxVertIndex - mMeshData.mLODs[LODIndex].mBatches[0][batchIndex].mMinVertIndex + 1;
    }
    size_t GetVertexCount() const noexcept { return mMeshData.mVertexCount; }
    size_t GetBatchCount(size_t LODIndex) const noexcept { return mMeshData.mLODs[LODIndex].mBatches[0].size(); }
    size_t GetLODCount() const noexcept { return mMeshData.mLODs.size(); }
    size_t GetVertexBufferCount() const noexcept { return mMeshData.mVertexStates[0].mVertexBufferCount; }

    size_t GetVertexBufferAttributeCount(size_t bufferIndex) const noexcept
    {
        size_t result = 0;
        for (uint32_t i = 0; i < mMeshData.mVertexStates[0].mAttributeCount; ++i)
        {
            if (mMeshData.mVertexStates[0].mAttributes[i].mBufferIndex == bufferIndex)
            {
                ++result;
            }
        }
        return result;
    }

    const void *GetVertexBuffer(size_t bufferIndex, size_t LODIndex, size_t batchIndex, AttributeDescription *descriptions) const noexcept
    {
        const uint8_t *ptr = async;
        for (uint32_t i = 0; i < mMeshData.mVertexStates[0].mIndexBufferCount; ++i)
        {
            ptr += mMeshData.mVertexStates[0].mpIndexBuffer[i].mStride * mMeshData.mVertexStates[0].mpIndexBuffer[i].mCount;
        }
        for (size_t i = 0; i < bufferIndex; ++i)
        {
            ptr += mMeshData.mVertexStates[0].mpVertexBuffer[i].mStride * mMeshData.mVertexStates[0].mpVertexBuffer[i].mCount;
        }
        size_t descriptionsIndex = 0;
        for (uint32_t i = 0; i < mMeshData.mVertexStates[0].mAttributeCount; ++i)
        {
            if (mMeshData.mVertexStates[0].mAttributes[i].mBufferIndex == bufferIndex)
            {
                descriptions[descriptionsIndex].attribute = static_cast<GFXPlatformVertexAttribute>(mMeshData.mVertexStates[0].mAttributes[i].mAttribute);
                descriptions[descriptionsIndex].format = static_cast<GFXPlatformFormat>(mMeshData.mVertexStates[0].mAttributes[i].mFormat);
                descriptions[descriptionsIndex].offset = mMeshData.mVertexStates[0].mAttributes[i].mBufferOffset;
                ++descriptionsIndex;
            }
        }
        return static_cast<const void *>(ptr + mMeshData.mVertexStates[0].mpVertexBuffer[bufferIndex].mStride * mMeshData.mLODs[LODIndex].mBatches[0][batchIndex].mMinVertIndex);
    }
    const void *GetIndices(GFXPlatformFormat &format, size_t LODIndex, size_t batchIndex) const noexcept
    {
        const uint8_t *ptr = async;
        for (uint32_t i = 0; i < mMeshData.mVertexStates[0].mIndexBufferCount; ++i)
        {
            if (mMeshData.mVertexStates[0].mpIndexBuffer[i].mBufferUsage == 0x2)
            {
                format = static_cast<GFXPlatformFormat>(mMeshData.mVertexStates[0].mpIndexBuffer[i].mBufferFormat);
                return static_cast<const void *>(ptr + mMeshData.mLODs[LODIndex].mBatches[0][batchIndex].mStartIndex);
            }
            ptr += mMeshData.mVertexStates[0].mpIndexBuffer[i].mStride * mMeshData.mVertexStates[0].mpIndexBuffer[i].mCount;
        }
        format = GFXPlatformFormat::eGFXPlatformFormat_None;
        return nullptr;
    }

    size_t GetIndexCount(size_t LODIndex, size_t batchIndex) const noexcept { return mMeshData.mLODs[LODIndex].mBatches[0][batchIndex].mNumIndices; }

    const Vector3 *GetPositionScale() const noexcept { return &mMeshData.mPositionScale; }
    const Vector3 *GetPositionOffset() const noexcept { return &mMeshData.mPositionOffset; }
    uint64_t GetBoneName(size_t LODIndex, size_t boneIndex) const noexcept { return mMeshData.mLODs[0].mBones[boneIndex].mCRC64; }
    size_t GetBoneCount(size_t LODIndex) const noexcept { return mMeshData.mLODs[0].mBones.size(); }
    size_t GetIndexCount() const noexcept { return mMeshData.mVertexStates[0].mpIndexBuffer[0].mCount; }
};

errno_t D3DMesh::Create()
{
    impl = new Impl;
    return 0;
}

void D3DMesh::Destroy() { delete impl; }

int32_t D3DMesh::Read(Stream &stream) noexcept { return impl->Read(stream); }
int32_t D3DMesh::Write(Stream &stream) const noexcept { return impl->Write(stream); }

size_t D3DMesh::GetLODCount() const noexcept { return impl->GetLODCount(); }
size_t D3DMesh::GetBatchCount(size_t LODIndex) const noexcept { return impl->GetBatchCount(LODIndex); }
size_t D3DMesh::GetVertexCount() const noexcept { return impl->GetVertexCount(); }
size_t D3DMesh::GetVertexCount(size_t LODIndex, size_t batchIndex) const noexcept { return impl->GetVertexCount(LODIndex, batchIndex); }
size_t D3DMesh::GetIndexCount(size_t LODIndex, size_t batchIndex) const noexcept { return impl->GetIndexCount(LODIndex, batchIndex); }
size_t D3DMesh::GetIndexCount() const noexcept { return impl->GetIndexCount(); }
size_t D3DMesh::GetVertexBufferCount() const noexcept { return impl->GetVertexBufferCount(); }

const void *D3DMesh::GetVertexBuffer(size_t bufferIndex, size_t LODIndex, size_t batchIndex, AttributeDescription descriptions[32]) const noexcept
{
    return impl->GetVertexBuffer(bufferIndex, LODIndex, batchIndex, descriptions);
}
size_t D3DMesh::GetVertexBufferAttributeCount(size_t bufferIndex) const noexcept { return impl->GetVertexBufferAttributeCount(bufferIndex); }

const void *D3DMesh::GetIndices(GFXPlatformFormat &format, size_t LODIndex, size_t batchIndex) const noexcept { return impl->GetIndices(format, LODIndex, batchIndex); }

const Vector3 *D3DMesh::GetPositionScale() const noexcept { return impl->GetPositionScale(); }
const Vector3 *D3DMesh::GetPositionOffset() const noexcept { return impl->GetPositionOffset(); }
uint64_t D3DMesh::GetBoneName(size_t LODIndex, size_t boneIndex) const noexcept { return impl->GetBoneName(LODIndex, boneIndex); }
size_t D3DMesh::GetBoneCount(size_t LODIndex) const noexcept { return impl->GetBoneCount(LODIndex); }

}; // namespace TTH