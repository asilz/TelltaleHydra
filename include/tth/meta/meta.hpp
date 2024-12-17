#pragma once

namespace TTH
{

enum MetaFlag
{
    MetaFlag_MetaSerializeDisable = 0x1,
    MetaFlag_MetaSerializeBlockingDisabled = 0x2,
    MetaFlag_PlaceInAddPropMenu = 0x4,
    MetaFlag_NoPanelCaption = 0x8,
    MetaFlag_BaseClass = 0x10,
    MetaFlag_EditorHide = 0x20,
    MetaFlag_EnumIntType = 0x40,
    MetaFlag_EnumStringType = 0x80,
    MetaFlag_ContainerType = 0x100,
    MetaFlag_ScriptEnum = 0x200,
    MetaFlag_Heap = 0x400,
    MetaFlag_ScriptTransient = 0x800,
    MetaFlag_SelectAgentType = 0x1000,
    MetaFlag_SkipObjectState = 0x2000,
    MetaFlag_NotCacheable = 0x4000,
    MetaFlag_EnumWrapperClass = 0x8000,
    MetaFlag_TempDescription = 0x10000,
    MetaFlag_Handle = 0x20000,
    MetaFlag_FlagType = 0x40000,
    MetaFlag_SelectFolderType = 0x80000,
    MetaFlag_Memberless = 0x100000,
    MetaFlag_RenderResource = 0x200000,
    MetaFlag_MetaSerializeNonBlockedVariableSize = 0x400002,
    MetaFlag_EmbeddedCacheableResource = 0x800000,
    MetaFlag_VirtualResource = 0x1000000,
    MetaFlag_DontAsyncLoad = 0x2000000,
    MetaFlag_IsNotMetaFile = 0x4000000,
    Internal_MetaFlag_Initialized = 0x20000000,
};

}