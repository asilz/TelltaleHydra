#include <tth/core/any.hpp>
#include <tth/meta/animation/animation.hpp>
#include <tth/meta/bitset/base.hpp>
#include <tth/meta/container/dcarray.hpp>
#include <tth/meta/container/map.hpp>
#include <tth/meta/container/sarray.hpp>
#include <tth/meta/container/set.hpp>
#include <tth/meta/d3dmesh/d3dmesh.hpp>
#include <tth/meta/handle/handle.hpp>
#include <tth/meta/linalg/quaternion.hpp>
#include <tth/meta/linalg/trange.hpp>
#include <tth/meta/linalg/transform.hpp>
#include <tth/meta/linalg/vector.hpp>
#include <tth/meta/prop/prop.hpp>
#include <tth/meta/skeleton/skeleton.hpp>
#include <tth/meta/t3texture/color.hpp>
#include <tth/meta/t3texture/swizzle.hpp>
#include <tth/meta/t3texture/t3texture.hpp>
#include <tth/meta/uid/uid.hpp>

namespace TTH
{

typedef int64_t int64;
typedef int32_t int32;
typedef int16_t int16;
typedef int8_t int8;

typedef uint64_t uint64;
typedef uint32_t uint32;
typedef uint16_t uint16;
typedef uint8_t uint8;

typedef uint64_t unsigned__int64;
typedef int64_t __int64;

Any::Any(uint64_t hash) : obj_(nullptr), dtor_(nullptr), copy_(nullptr), read_(nullptr), write_(nullptr), typeName_(nullptr)
{
    switch (hash)
    {
    case 0x004F023463D89FB0:
        SetType<Symbol>();
        break;
    case 0x00A87B9875C485DB:
        // SetType<DCArray<LanguageResLocal>>();
        break;
    case 0x00ACFF947A409DDB:
        // SetType<Mover>();
        break;
    case 0x011F7E31FB297D7D:
        // SetType<DCArray<DlgNodeExchange::Entry>>();
        break;
    case 0x01C9A459992D55F3:
        // SetType<DlgLineCollection>();
        break;
    case 0x02167D60A7BF23E6:
        // SetType<SingleValue<LocationInfo>>();
        break;
    case 0x026495DD43D2BE66:
        // SetType<KeyframedValue<Handle<Chore>>>();
        break;
    case 0x02A9ACE31B9DB46D:
        // SetType<DCArray<KeyframedValue<Color>::Sample>>();
        break;
    case 0x02C723D77F0C4B32:
        // SetType<Handle<AudioData>>();
        break;
    case 0x0371D30CA437BCDC:
        // SetType<CompressedKeys<CompressedPathBlockingValue::CompressedPathInfoKey>>();
        break;
    case 0x037E2FEE893983C9:
        // SetType<ZTestFunction>();
        break;
    case 0x03FBA4982FDC6B40:
        // SetType<KeyframedValue<CompressedPathBlockingValue::CompressedPathInfoKey>>();
        break;
    case 0x042F3CD4FE3D6D0D:
        // SetType<Map<Symbol, bool, less<Symbol>>>();
        break;
    case 0x043F7B983EEE556E:
        // SetType<SingleValue<SoundEventName<2>>>();
        break;
    case 0x046D4F1EB16A8ABF:
        // SetType<AnimatedValueInterface<Handle<T3Texture>>>();
        break;
    case 0x04C03CA073E34563:
        // SetType<HingeJointKey>();
        break;
    case 0x04D13C680B64ADC3:
        SetType<DCArray<unsigned short>>();
        break;
    case 0x04EE8AB98C0E7346:
        // SetType<SingleValue<PhonemeKey>>();
        break;
    case 0x0589F045B23AB6B4:
        // SetType<EnumEmitterTriggerEnable>();
        break;
    case 0x05DB112DDD243EBE:
        // SetType<MeshSceneLightmapData>();
        break;
    case 0x05F2FC89653F5C5C:
        // SetType<SoundBusSystem::BusDescription>();
        break;
    case 0x062CC3BE86D4A0DB:
        // SetType<SingleValue<Handle<WalkBoxes>>>();
        break;
    case 0x0633339B0EBD064B:
        // SetType<T3LightSceneInternalData>();
        break;
    case 0x0684B3A160B2AED9:
        // SetType<SingleQuaternionValue>();
        break;
    case 0x06B7A28E6C2D93DD:
        // SetType<EnumHBAOBlurQuality>();
        break;
    case 0x06D503EAE2AF659D:
        // SetType<List<ActingPaletteGroup::ActingPaletteTransition>>();
        break;
    case 0x07053D1D5732E4D5:
        // SetType<ScriptEnum : QTE_Type>();
        break;
    case 0x0760518169BE7C9C:
        // SetType<FootSteps::FootstepBank>();
        break;
    case 0x07A995E0FEEEDA3E:
        // SetType<Handle<ResourceBundle>>();
        break;
    case 0x08222B402EF42B3E:
        // SetType<Footsteps2::FootstepBank>();
        break;
    case 0x089A910EC95E5128:
        // SetType<AnimatedValueInterface<Handle<Font>>>();
        break;
    case 0x096F88556B81A6AF:
        // SetType<DlgObjectPropsOwner>();
        break;
    case 0x09C26EAAD53BEC47:
        // SetType<List<Handle<PropertySet>>>();
        break;
    case 0x0A034C9344F17FCE:
        // SetType<KeyframedValue<ScriptEnum>>();
        break;
    case 0x0A09E83894C80579:
        // SetType<Map<String, Handle<PropertySet>, less<String>>>();
        break;
    case 0x0AD7EF65B5C2FB8B:
        // SetType<Handle<StyleIdleTransitionsRes>>();
        break;
    case 0x0B350ED3E60A3A82:
        // SetType<Handle<LightProbeData>>();
        break;
    case 0x0B47B28F9B66367C:
        // SetType<CompressedKeys<Handle<Dlg>>>();
        break;
    case 0x0B8BD6449DCB3262:
        // SetType<Map<int, Ptr<DialogText>, less<int>>>();
        break;
    case 0x0BA8280CE6EE5023:
        // SetType<Handle<BlendMode>>();
        break;
    case 0x0C1E84D6FF72CE80:
        // SetType<SingleValue<Transform>>();
        break;
    case 0x0C2208A6B83FF0D0:
        // SetType<EnumParticleGeometryType>();
        break;
    case 0x0C6B16504DB34467:
        // SetType<DCArray<Ptr<AnimationValueInterfaceBase>>>();
        break;
    case 0x0CA5396FBDF99B4D:
        // SetType<save>();
        break;
    case 0x0CBCC5585D066C26:
        // SetType<DCArray<KeyframedValue<Handle<Font>>::Sample>>();
        break;
    case 0x0D4BF6E9059B7ABD:
        // SetType<DlgChildSetChoice>();
        break;
    case 0x0D5642485492311F:
        // SetType<ChoreAgent::Attachment>();
        break;
    case 0x0DC7D8AA2CCF1332:
        // SetType<T3OverlayObjectData_Sprite>();
        break;
    case 0x0E030A302425D453:
        // SetType<EnlightenModule::EnlightenCubemapSettings>();
        break;
    case 0x0E0D50B11C5F3071:
        // SetType<EnvironmentLight>();
        break;
    case 0x0E6BD8C1195FF49F:
        SetType<Map<String, Map<String, String, std::less<String>>, std::less<String>>>();
        break;
    case 0x0EE94831CBA42B32:
        SetType<DCArray<KeyframedValue<Vector2>::Sample>>();
        break;
    case 0x0F43F2EB7185E296:
        // SetType<DCArray<Ptr<ActingPaletteClass>>>();
        break;
    case 0x0FA0200E101BA5B8:
        // SetType<Map<Symbol, PreloadPackage::ResourceSeenTimes, less<Symbol>>>();
        break;
    case 0x0FDC0365EABBD69E:
        // SetType<NavCam::EnumMode>();
        break;
    case 0x1019453EB19C1ABD:
        SetType<KeyframedValue<Quaternion>>();
        break;
    case 0x101E4BF52A9999AC:
        SetType<long>();
        break;
    case 0x106930CCC0A67F81:
        // SetType<DCArray<Guide>>();
        break;
    case 0x108A4BDBA5C4323C:
        // SetType<CompressedKeys<Vector3>>();
        break;
    case 0x11044749232970C0:
        SetType<uint64>();
        break;
    case 0x112AFB1D97DE426F:
        // SetType<EnumParticlePropModifier>();
        break;
    case 0x113E7D20ABCD8F82:
        // SetType<List<Vector3>>();
        break;
    case 0x114113B10EEE5F5C:
        // SetType<T3MeshPropertyEntry>();
        break;
    case 0x114636E822613A22:
        // SetType<LogicGroup>();
        break;
    case 0x11C0B2FA0E373C72:
        // SetType<T3VertexBufferSample<T3NormalSampleData, T3HeapAllocator>>();
        break;
    case 0x12CD3F0920AE1380:
        // SetType<Handle<LanguageDatabase>>();
        break;
    case 0x13058734F0A0B42F:
        // SetType<DCArray<Handle<Chore>>>();
        break;
    case 0x135C8F048CAB3B1A:
        // SetType<DCArray<T3MeshMaterialOverride>>();
        break;
    case 0x13701CC75D2E8F76:
        // SetType<KeyframedValue<Handle<SoundData>>>();
        break;
    case 0x1373B90F4631D050:
        // SetType<GFXPlatformAttributeParams>();
        break;
    case 0x137C0EA853FDD598:
        // SetType<DlgChoice>();
        break;
    case 0x13998D6F0BDE3491:
        // SetType<DlgNodeChoices>();
        break;
    case 0x13AEBBF796CAED1B:
        // SetType<estore>();
        break;
    case 0x13C9CDF379EF28E0:
        SetType<Map<int, PropertySet, std::less<int>>>();
        break;
    case 0x14405BB0FDAEF3F3:
        // SetType<EnumT3LightEnvShadowType>();
        break;
    case 0x14AD5AB2AA65AA14:
        // SetType<T3MaterialSwizzleParams>();
        break;
    case 0x14B01C37623D58CB:
        SetType<DCArray<Handle<T3Texture>>>();
        break;
    case 0x14E382987D757E47:
        SetType<KeyframedValue<Symbol>>();
        break;
    case 0x15623933D3FDB46F:
        // SetType<EnlightenModule::EnumeBackfaceType>();
        break;
    case 0x169DBBF7BC9DAE98:
        // SetType<preloadpackagerts>();
        break;
    case 0x16F70EA63ACE4D1F:
        // SetType<SoundData>();
        break;
    case 0x177AAECBE81EC7CF:
        // SetType<Handle<SoundEventData>>();
        break;
    case 0x178C1A035ED26487:
        // SetType<IdleSlotDefaults>();
        break;
    case 0x1793F7CC87414A9C:
        SetType<DCArray<T3MaterialNestedMaterial>>();
        break;
    case 0x17A22BCB7F71DA7C:
        // SetType<AnimatedValueInterface<Handle<SoundBusSnapshot::Snapshot>>>();
        break;
    case 0x17C3DEFAAB9829B0:
        // SetType<EnlightenModule::EnlightenProbeVolumeSettings>();
        break;
    case 0x18525353197DDC4E:
        // SetType<EnumRenderTAAJitterType>();
        break;
    case 0x18A8A7AE07018B8D:
        // SetType<DlgNodeIdle>();
        break;
    case 0x18B7A88B80875CBE:
        // SetType<PhonemeTable>();
        break;
    case 0x18F3EC40E3993F23:
        // SetType<DCArray<KeyframedValue<Handle<Chore>>::Sample>>();
        break;
    case 0x193947C951B51053:
        // SetType<CompressedVertexPositionKeys>();
        break;
    case 0x1966C52FAEA296B5:
        // SetType<AnimatedValueInterface<Handle<SoundAmbience::AmbienceDefinition>>>();
        break;
    case 0x196A1BF777E8C2F8:
        // SetType<ActingPaletteGroup::EnumIdleTransition>();
        break;
    case 0x19F654ED32A2C708:
        // SetType<EnumT3MaterialLODFullyRough>();
        break;
    case 0x1AFF8E5E688E0117:
        // SetType<EnlightenModule::EnumeSimplifyMode>();
        break;
    case 0x1B3355ECACF8ED7C:
        // SetType<Handle<Dlg>>();
        break;
    case 0x1B3A715D9339AF5F:
        // SetType<CompressedKeys<Handle<T3Texture>>>();
        break;
    case 0x1BBD9C16A1D7261C:
        SetType<unsigned short>();
        break;
    case 0x1BE31F84BB675B71:
        // SetType<DCArray<RenderObject_Mesh::MeshInstance>>();
        break;
    case 0x1C0688FD6A78C6D1:
        // SetType<ScriptEnum : ReticleActions>();
        break;
    case 0x1C085FBA0B240337:
        // SetType<DCArray<T3MeshEffectPreload>>();
        break;
    case 0x1C7C457A2166B727:
        // SetType<EnumRenderMaskTest>();
        break;
    case 0x1CA3A30A80E58244:
        // SetType<Handle<ParticleSprite>>();
        break;
    case 0x1CCDC5D367F7A6B7:
        // SetType<Handle<T3OverlayData>>();
        break;
    case 0x1CF4C103D0290F37:
        SetType<unsigned char>();
        break;
    case 0x1D0BCFF71E6BC2E1:
        SetType<DCArray<Handle<PropertySet>>>();
        break;
    case 0x1D6B01580F1491E6:
        // SetType<HandleLock<Animation>>();
        break;
    case 0x1DDC6104AA9DFDC0:
        SetType<DCArray<T3MaterialPreShader>>();
        break;
    case 0x1DF7C31EA25EAE57:
        // SetType<KeyframedValue<Handle<SoundBusSnapshot::SnapshotSuite>>>();
        break;
    case 0x1E0A2AD219F12B54:
        // SetType<DCArray<KeyframedValue<SoundEventName<0>>::Sample>>();
        break;
    case 0x1E66E396A35F93F9:
        // SetType<ScriptEnum : MenuVerticalAlignment>();
        break;
    case 0x1E7032DDDA683211:
        // SetType<DCArray<T3MeshEffectPreloadDynamicFeatures>>();
        break;
    case 0x1E89F50D0F33E645:
        // SetType<FileNameBase>();
        break;
    case 0x1EEF71B2306B5B6C:
        SetType<uint16>();
        break;
    case 0x1EF9BD7B68F3F685:
        // SetType<DCArray<KeyframedValue<Handle<SoundBusSnapshot::Snapshot>>::Sample>>();
        break;
    case 0x1FA626CC4ACF634E:
        // SetType<DArray<InputMapper *__ptr64>>();
        break;
    case 0x1FC8525B23714149:
        // SetType<DlgNodeLink>();
        break;
    case 0x200159CE1F32968E:
        SetType<T3MaterialRequirements>();
        break;
    case 0x20D348E9BF150EC0:
        // SetType<ParticleInverseKinematics>();
        break;
    case 0x2118E867B2A12F9B:
        // SetType<t3bullet>();
        break;
    case 0x21436B2755503C3B:
        // SetType<DlgNodeCriteria>();
        break;
    case 0x222F4DE92A59200C:
        // SetType<Map<String, Set<Symbol, less<Symbol>>, StringCompareCaseInsensitive>>();
        break;
    case 0x2247C0C4758DF684:
        // SetType<AnimationConstraintParameters>();
        break;
    case 0x227F68CE26A32BDE:
        // SetType<landb>();
        break;
    case 0x228199A2E37BD10E:
        // SetType<Map<String, ClipResourceFilter, StringCompareCaseInsensitive>>();
        break;
    case 0x22889D9245104640:
        // SetType<DCArray<KeyframedValue<Handle<SoundReverbDefinition>>::Sample>>();
        break;
    case 0x229EF3B04212AEDC:
        // SetType<HandleLock<Scene>>();
        break;
    case 0x230136B8537EB13B:
        // SetType<CompressedKeys<Handle<D3DMesh>>>();
        break;
    case 0x2309FB51D434529C:
        SetType<BitSetBase<8>>();
        break;
    case 0x238A520C4A924AA6:
        // SetType<EventLoggerEvent>();
        break;
    case 0x2396FCD59456C981:
        // SetType<Map<String, PhonemeTable::PhonemeEntry, less<String>>>();
        break;
    case 0x239A652F3374B09C:
        // SetType<EnumTonemapType>();
        break;
    case 0x23A058ACA47378FE:
        // SetType<TransitionMap>();
        break;
    case 0x24032A7AD8BB721D:
        // SetType<EventStoragePage>();
        break;
    case 0x24642A39023F0F34:
        SetType<DCArray<String>>();
        break;
    case 0x2491B84DAED1E76B:
        SetType<DCArray<T3MaterialPassData>>();
        break;
    case 0x24A03076F08204F4:
        // SetType<FlagsT3LightEnvGroupSet>();
        break;
    case 0x24A2B5D932321226:
        // SetType<PhysicsObject>();
        break;
    case 0x24C2C71A33271C9A:
        // SetType<bank>();
        break;
    case 0x24EEF50A57B5AF8C:
        // SetType<SingleValue<Handle<Font>>>();
        break;
    case 0x252A0706975C73F3:
        // SetType<CompressedKeys<Handle<SoundEventSnapshotData>>>();
        break;
    case 0x2531E6EFFDD55834:
        // SetType<T3MeshEffectPreloadEntry>();
        break;
    case 0x253CC17FE053535F:
        // SetType<KeyframedValue<SoundEventName<2>>>();
        break;
    case 0x254EDC517B59BB47:
        // SetType<BlendMode>();
        break;
    case 0x255105CE38A142D8:
        // SetType<SingleValue<AnimOrChore>>();
        break;
    case 0x25D9654A81DC862E:
        // SetType<DCArray<SaveGame::AgentInfo>>();
        break;
    case 0x26591AF0C98AD8F6:
        // SetType<DlgCondition>();
        break;
    case 0x267B345697B6BB64:
        // SetType<BGM_HeadTurn_Value>();
        break;
    case 0x268E0B3FC19A48AE:
        SetType<int64>();
        break;
    case 0x26D936F7FF759D39:
        // SetType<Skeleton>();
        break;
    case 0x272F79595869A6EA:
        // SetType<KeyframedValue<Handle<WalkBoxes>>>();
        break;
    case 0x27A5B3261A805C7E:
        // SetType<T3MeshBatch>();
        break;
    case 0x2800315188BB867A:
        // SetType<Map<Symbol, WalkPath, less<Symbol>>>();
        break;
    case 0x2874DABB8036B62A:
        // SetType<DCArray<T3OverlayObjectData_Text>>();
        break;
    case 0x2889E11388057333:
        // SetType<DialogResource>();
        break;
    case 0x28B6294866D5C910:
        // SetType<Handle<TransitionMap>>();
        break;
    case 0x2913E82ADFBF4CAD:
        // SetType<List<int>>();
        break;
    case 0x29653DC4D2D86302:
        SetType<int16>();
        break;
    case 0x2A2E93F6AF788919:
        // SetType<bussnapshot>();
        break;
    case 0x2A5AAF50752FFED9:
        // SetType<DlgNodeChore>();
        break;
    case 0x2ABB7B45E2D0C5FE:
        // SetType<ParticleSprite>();
        break;
    case 0x2B1181164B35FCD3:
        // SetType<PreloadPackage::ResourceSeenTimes>();
        break;
    case 0x2B1A694F2F80DEEC:
        // SetType<AnimatedValueInterface<Handle<D3DMesh>>>();
        break;
    case 0x2B764A50099A3FEF:
        SetType<Map<String, Set<Symbol, std::less<Symbol>>, std::less<String>>>();
        break;
    case 0x2B7B462F08600B16:
        // SetType<DialogItem::EnumPlaybackMode>();
        break;
    case 0x2BDB4B5DC519BBFA:
        // SetType<List<Map<String, String, less<String>>>>();
        break;
    case 0x2BF8E79FDA2D294E:
        // SetType<ParticleSprite::Animation>();
        break;
    case 0x2C85F7D8B8F8342F:
        // SetType<DCArray<bool>>();
        break;
    case 0x2CC6C64673C9E079:
        // SetType<PlaybackController>();
        break;
    case 0x2D0EC64E3F776C29:
        // SetType<LanguageDatabase>();
        break;
    case 0x2D407BA0D7989A79:
        // SetType<StyleGuideRef>();
        break;
    case 0x2E6219643954DD42:
        // SetType<AnimatedValueInterface<LocationInfo>>();
        break;
    case 0x2E6C72D65DBFCA59:
        // SetType<acol>();
        break;
    case 0x2E6FE36F92E0E957:
        // SetType<ChoreResource::Block>();
        break;
    case 0x2E8076F05492665C:
        SetType<DCArray<float>>();
        break;
    case 0x2EE70BCF1B707D98:
        // SetType<DlgNodeJump>();
        break;
    case 0x2EFDDB0CE55AB6A6:
        SetType<DCArray<KeyframedValue<bool>::Sample>>();
        break;
    case 0x2F038E9A0FA4C428:
        // SetType<DlgNodeStats::DlgChildSetCohort>();
        break;
    case 0x2F35F13012C086E4:
        // SetType<AnimatedValueInterface<CompressedPathBlockingValue::CompressedPathInfoKey>>();
        break;
    case 0x2F887206C5AEF2E0:
        // SetType<BlendCameraResource>();
        break;
    case 0x2F99EAAB8A379140:
        // SetType<ScriptEnum : UseableType>();
        break;
    case 0x2FD428E74998C3F7:
        SetType<Set<String, std::less<String>>>();
        break;
    case 0x2FE13A670E3B9412:
        // SetType<AnimatedValueInterface<Handle<SoundEventSnapshotData>>>();
        break;
    case 0x3007758840388E30:
        // SetType<DlgNodeExit>();
        break;
    case 0x3057C880E751D8C5:
        SetType<Handle<Animation>>();
        break;
    case 0x30694ADB68E78E3D:
        // SetType<DCArray<ProjectDatabaseIDPair>>();
        break;
    case 0x30732A2C440A6C8A:
        // SetType<DlgChildSetChoicesChildPre>();
        break;
    case 0x3091E66640DF1B17:
        // SetType<DlgChoicesChildPost>();
        break;
    case 0x31D14C7B4F174A77:
        // SetType<SoundBusSystem::BusHolder>();
        break;
    case 0x321F5964C733F819:
        // SetType<LightInstance>();
        break;
    case 0x3273A62083938947:
        // SetType<SingleValue<Handle<SoundData>>>();
        break;
    case 0x32E8B2BE4942CDFA:
        // SetType<List<String>>();
        break;
    case 0x32EA71CFB4CA38E9:
        // SetType<WalkBoxes>();
        break;
    case 0x32FFF7F8AAED5859:
        // SetType<DCArray<Handle<Rules>>>();
        break;
    case 0x330C2B0399D56A72:
        // SetType<ScriptEnum : AIAgentState>();
        break;
    case 0x336AA0370832E993:
        // SetType<DCArray<KeyframedValue<AnimOrChore>::Sample>>();
        break;
    case 0x336ADB075A965645:
        // SetType<Rect>();
        break;
    case 0x338E4BAD4D941F67:
        // SetType<VoiceData>();
        break;
    case 0x33A1F0CB9E5BBC70:
        // SetType<CameraSelect>();
        break;
    case 0x33AF1F0B2F1338FE:
        // SetType<EnlightenModule::EnumeDisplayQuality>();
        break;
    case 0x33C56D9E4438FCD9:
        SetType<Map<Symbol, int, std::less<Symbol>>>();
        break;
    case 0x3421FA8D08F00332:
        // SetType<DCArray<ParticlePropConnect>>();
        break;
    case 0x3428AF89D69602D2:
        // SetType<DCArray<Ptr<ActingPalette>>>();
        break;
    case 0x3437131536412935:
        // SetType<ChorecorderParameters>();
        break;
    case 0x3481D0ADE22D8993:
        // SetType<DCArray<T3OverlayObjectData_Sprite>>();
        break;
    case 0x34ACE6F6E8E7EEB0:
        // SetType<DCArray<T3LightSceneInternalData::LightmapPage>>();
        break;
    case 0x352F2D7C4C36636E:
        // SetType<InverseKinematics>();
        break;
    case 0x354F33392303495F:
        // SetType<trans>();
        break;
    case 0x35640331B161F506:
        // SetType<DlgObjectPropsMap>();
        break;
    case 0x3593E489074C37F6:
        // SetType<Map<String, ChorecorderParameters, less<String>>>();
        break;
    case 0x35C40A55D80F186B:
        SetType<DCArray<KeyframedValue<unsigned__int64>::Sample>>();
        break;
    case 0x36050B3A56AE750F:
        // SetType<HandleLock<Skeleton>>();
        break;
    case 0x365952B07C0CE60D:
        // SetType<DlgNodeCriteria::EnumTestT>();
        break;
    case 0x36D2E9352E9EED3E:
        // SetType<DCArray<LogicGroup>>();
        break;
    case 0x36E367B48AD63274:
        // SetType<DlgNodeSequence>();
        break;
    case 0x36FC875F02FC9118:
        // SetType<DCArray<SoundAmbience::EventContext>>();
        break;
    case 0x36FFAE9C29F1BC0E:
        // SetType<DCArray<KeyframedValue<Handle<PhonemeTable>>::Sample>>();
        break;
    case 0x374927061B784594:
        SetType<DCArray<Vector3>>();
        break;
    case 0x37B8C02CC0B488BE:
        // SetType<Handle<EventStorage>>();
        break;
    case 0x383AEB196C60831B:
        // SetType<LocationInfo>();
        break;
    case 0x387E6B9CA558AC8D:
        // SetType<Handle<PropertySet>>();
        break;
    case 0x394C43AF4FF52C94:
        SetType<Vector3>();
        break;
    case 0x396E225045FA7F39:
        // SetType<Map<String, AgentMap::AgentMapEntry, less<String>>>();
        break;
    case 0x3A0F993D2100A5C3:
        // SetType<DlgNodeStats>();
        break;
    case 0x3A195525E24AFC93:
        SetType<uint8>();
        break;
    case 0x3A63217C2BB535F3:
        // SetType<SoundEventNameBase>();
        break;
    case 0x3A7B60443850419E:
        // SetType<CompressedKeys<String>>();
        break;
    case 0x3AAEB61240D3CFBA:
        // SetType<EventStorage>();
        break;
    case 0x3AE7EAFC7629AF12:
        // SetType<Map<String, LocomotionDB::AnimationInfo, less<String>>>();
        break;
    case 0x3AFD7D3DAFBD6437:
        // SetType<EnumEmittersEnableType>();
        break;
    case 0x3B160BC2AD5CB101:
        SetType<T3MeshLOD>();
        break;
    case 0x3B19CEFBA080E62C:
        // SetType<EnumEmitterSpriteAnimationSelection>();
        break;
    case 0x3B220A6965863962:
        // SetType<DlgNodeMarker>();
        break;
    case 0x3B965660D71DE2A7:
        SetType<DCArray<T3OcclusionMeshBatch>>();
        break;
    case 0x3BC3CB16F9AA0F31:
        // SetType<List<Handle<T3Texture>>>();
        break;
    case 0x3BE17704E64CEBDA:
        // SetType<LanguageRes>();
        break;
    case 0x3C17F9BB2C4EE061:
        // SetType<DCArray<KeyframedValue<Handle<WalkBoxes>>::Sample>>();
        break;
    case 0x3C64522734434AF4:
        // SetType<TetrahedralMeshData>();
        break;
    case 0x3C7DD6F435A58C09:
        // SetType<AnimatedValueInterface<Handle<SoundBusSnapshot::SnapshotSuite>>>();
        break;
    case 0x3D2DBF388BFDE0A4:
        // SetType<CompressedPhonemeKeys>();
        break;
    case 0x3D7530F2FB48C1D4:
        // SetType<T3MaterialStaticParameter>();
        break;
    case 0x3DB436EBD6D0A77F:
        SetType<KeyframedValue<unsigned__int64>>();
        break;
    case 0x3DCB405F9B7183E6:
        // SetType<DCArray<KeyframedValue<T3VertexBufferSample<T3PositionSampleData, T3HeapAllocator>>::Sample>>();
        break;
    case 0x3DCF1CF6F50A83A1:
        // SetType<ScriptEnum : ReticleDisplayMode>();
        break;
    case 0x3DE8FE133A5A0DB7:
        SetType<DCArray<T3MaterialParameter>>();
        break;
    case 0x3E249E7E6F38CCE2:
        SetType<T3Texture>();
        break;
    case 0x3E597A1F6499DBFD:
        SetType<T3MeshTextureIndices>();
        break;
    case 0x3E9F3EC23C34F712:
        // SetType<DCArray<T3MeshPropertyEntry>>();
        break;
    case 0x3EE075753B1F4572:
        // SetType<ChoreResource>();
        break;
    case 0x3EF0D736FB3D9B51:
        // SetType<T3LightCinematicRigLOD>();
        break;
    case 0x3F0A750283637C54:
        // SetType<Map<Symbol, Handle<SoundBusSnapshot::Snapshot>, less<Symbol>>>();
        break;
    case 0x3F17824B51361CB2:
        // SetType<List<DCArray<String>>>();
        break;
    case 0x3F299CC72969591F:
        // SetType<SingleValue<Handle<Scene>>>();
        break;
    case 0x3F9231D57F64F520:
        // SetType<Handle<Font>>();
        break;
    case 0x3FD6C82DBDBCA912:
        // SetType<RenderObjectInterface>();
        break;
    case 0x40E50DFBE6B6A8A7:
        // SetType<DlgSystemSettings>();
        break;
    case 0x410FD9DEAF2A7A16:
        // SetType<KeyframedValue<SoundEventName<1>>>();
        break;
    case 0x411D4FB22E6FB323:
        // SetType<AnimatedValueInterface<Vector4>>();
        break;
    case 0x4169719CDC054982:
        // SetType<LanguageLookupMap>();
        break;
    case 0x4170C88101407B66:
        // SetType<EnumHBAODeinterleaving>();
        break;
    case 0x4175FE7ABFC543AA:
        // SetType<EnlightenModule::EnlightenAdaptiveProbeVolumeSettings>();
        break;
    case 0x4252D2F4AC275D24:
        SetType<DCArray<Symbol>>();
        break;
    case 0x42722660D93932DF:
        // SetType<d3dtx>();
        break;
    case 0x4309CCAC7CF5071B:
        // SetType<epage>();
        break;
    case 0x43896B984C95FFF2:
        // SetType<List<List<PropertySet>>>();
        break;
    case 0x43E294A64B4064E0:
        // SetType<SingleValue<SoundEventName<0>>>();
        break;
    case 0x4402A3529CE6846F:
        // SetType<CompressedKeys<unsigned__int64>>();
        break;
    case 0x44236D53DBFE4C7D:
        // SetType<SingleValue<float>>();
        break;
    case 0x4492C4CEA3C7D14D:
        SetType<KeyframedValue<int>>();
        break;
    case 0x44DF88DF0BB2C808:
        // SetType<SoundEventName<2>>();
        break;
    case 0x45420F3D44ED112D:
        // SetType<ScriptEnum : GamepadButton>();
        break;
    case 0x45780D6E44155DCF:
        // SetType<KeyframedValue<Handle<SoundEventData>>>();
        break;
    case 0x45D149740D9B1DF0:
        // SetType<ActingPaletteGroup>();
        break;
    case 0x46DE57E6E6C4DF4A:
        // SetType<Handle<SaveGame>>();
        break;
    case 0x471A8A4511F0CCA6:
        // SetType<Handle<WalkBoxes>>();
        break;
    case 0x47957E5358BA925A:
        // SetType<EnlightenModule::EnumeUpdateMethod>();
        break;
    case 0x47DF64BF502BB7DA:
        // SetType<Map<Symbol, FootSteps::FootstepBank, less<Symbol>>>();
        break;
    case 0x4835DE9C54850524:
        // SetType<Map<String, StyleGuideRef, less<String>>>();
        break;
    case 0x48588668F74FED9F:
        SetType<UID::Owner>();
        break;
    case 0x487D0696C99D7761:
        // SetType<EnumEmitterBoneSelection>();
        break;
    case 0x48F9824E42292AB6:
        // SetType<CompressedKeys<Polar>>();
        break;
    case 0x494C82BF598CAA78:
        // SetType<CompressedKeys<Handle<PhonemeTable>>>();
        break;
    case 0x495617D7C61A60FD:
        // SetType<DCArray<WalkBoxes::Tri>>();
        break;
    case 0x4971BB8B0C356B27:
        // SetType<Rules>();
        break;
    case 0x49FCF5BDD5993666:
        // SetType<DCArray<PreloadPackage::RuntimeDataDialog::DialogResourceInfo>>();
        break;
    case 0x4A36C85D3C0FEF77:
        // SetType<AnimatedValueInterface<Handle<Dlg>>>();
        break;
    case 0x4AFBD4652719A0E1:
        // SetType<ik>();
        break;
    case 0x4B26A2CA30DE3F32:
        SetType<uint32>();
        break;
    case 0x4B5C5357547E165F:
        // SetType<Map<int, Ptr<DialogLine>, less<int>>>();
        break;
    case 0x4B81E6ACDEA8500A:
        // SetType<CompressedVertexNormalKeys>();
        break;
    case 0x4BAAC446D7EBBE7C:
        // SetType<SingleValue<CompressedPathBlockingValue::CompressedPathInfoKey>>();
        break;
    case 0x4BBFF0D25B0EE9B2:
        // SetType<T3VertexBufferSample<T3PositionSampleData, T3HeapAllocator>>();
        break;
    case 0x4BD04E27E6716EA0:
        SetType<UID::Generator>();
        break;
    case 0x4C199A98E11DF819:
        SetType<BitSetBase<2>>();
        break;
    case 0x4C19FCA5E018EBB8:
        // SetType<AnimatedValueInterface<unsigned__int64>>();
        break;
    case 0x4CC03BEF63487679:
        SetType<Map<int, Symbol, std::less<int>>>();
        break;
    case 0x4D797D8C9D925179:
        // SetType<PhysicsData>();
        break;
    case 0x4DC6F34A18FB8B3E:
        // SetType<TextAlignmentType>();
        break;
    case 0x4DD3BB0BF90864B7:
        // SetType<DlgNodeStats::Cohort>();
        break;
    case 0x4E0FD348B672CF78:
        // SetType<DCArray<KeyframedValue<Handle<SoundAmbience::AmbienceDefinition>>::Sample>>();
        break;
    case 0x4E118F54149F62A6:
        // SetType<Selectable>();
        break;
    case 0x4E5257DAB0661351:
        // SetType<ScriptEnum : ControllerButtons>();
        break;
    case 0x4E64C42552E25C53:
        // SetType<PreloadPackage::RuntimeDataScene>();
        break;
    case 0x4E7FBFE5553E38EB:
        // SetType<locreg>();
        break;
    case 0x4F122FBDBA526BBF:
        // SetType<PathBase>();
        break;
    case 0x4F1B64D81FC60325:
        SetType<Map<String, String, std::less<String>>>();
        break;
    case 0x4F370A28A5E8152B:
        // SetType<SArray<unsignedint, 3>>();
        break;
    case 0x4F5348AAD96B21B6:
        // SetType<Chore::EnumExtentsMode>();
        break;
    case 0x4F6D302E7708C977:
        // SetType<ContainerInterface>();
        break;
    case 0x4FC0A74CE6DAD33E:
        // SetType<Handle<LocomotionDB>>();
        break;
    case 0x5000C70516FF6369:
        // SetType<amap>();
        break;
    case 0x5016B7228F97D967:
        // SetType<BlendGraph>();
        break;
    case 0x5035C3ACDCC297D3:
        SetType<DCArray<T3MaterialRuntimeProperty>>();
        break;
    case 0x508B8F3DE7AADAD2:
        // SetType<EnumParticlePropDriver>();
        break;
    case 0x50B02BA98CAEB2F0:
        // SetType<CompressedKeys<PhonemeKey>>();
        break;
    case 0x51011D3DBFA81072:
        // SetType<T3OverlaySpriteParams>();
        break;
    case 0x5139E7E487766AF8:
        // SetType<T3LightProbeInternalData::QualityEntry>();
        break;
    case 0x5183CFAAB69784D5:
        // SetType<Meta::DependentResource>();
        break;
    case 0x524D5D17BCDD3CE2:
        // SetType<ScriptEnum : LightComposerLightSourceQuadrant>();
        break;
    case 0x52A09151F1C3F2C7:
        SetType<Handle<T3Texture>>();
        break;
    case 0x533E28DB4F24152B:
        // SetType<EnlightenModule::EnumeQuality>();
        break;
    case 0x53423D0EDF9278D3:
        // SetType<ScriptEnum : AIDummyPos>();
        break;
    case 0x5353B1FC8FC624C7:
        // SetType<MovieCaptureInfo>();
        break;
    case 0x53A0B3AA86983895:
        // SetType<TRect<float>>();
        break;
    case 0x53B1524DA203616E:
        // SetType<ActorAgentMapper>();
        break;
    case 0x540181F155761548:
        SetType<DCArray<Handle<D3DMesh>>>();
        break;
    case 0x54268116A226A267:
        // SetType<List<Handle<Scene>>>();
        break;
    case 0x5472BFB3E281088F:
        // SetType<EnlightenModule::EnumeProbeSampleMethod>();
        break;
    case 0x552D6026F0D9CDD8:
        // SetType<AnimatedValueInterface<Transform>>();
        break;
    case 0x5531D898F735D354:
        // SetType<EnumHBAOResolution>();
        break;
    case 0x5549D9EFE67060E1:
        // SetType<Rule>();
        break;
    case 0x559AE24458E0D573:
        // SetType<EnumT3LightEnvShadowQuality>();
        break;
    case 0x55A38D1B5562A6F3:
        // SetType<SkeletonInstance>();
        break;
    case 0x55AD5FD7B7CF097A:
        // SetType<DCArray<KeyframedValue<Polar>::Sample>>();
        break;
    case 0x55D6BA6E0B33DB18:
        // SetType<DCArray<KeyframedValue<PhonemeKey>::Sample>>();
        break;
    case 0x56DB012C6E040C77:
        // SetType<DArray<int>>();
        break;
    case 0x570C0DE6C831EC23:
        // SetType<StringFilter>();
        break;
    case 0x575309577CA53FD3:
        // SetType<DCArray<DlgNodeInstanceParallel::ElemInstanceData>>();
        break;
    case 0x580897C10167B2E0:
        // SetType<KeyframedValueSteppedString>();
        break;
    case 0x58253DE205454089:
        // SetType<SoundEventName<0>>();
        break;
    case 0x584619F1AE300EEA:
        SetType<T3Texture::RegionStreamHeader>();
        break;
    case 0x585829C336CB2FA5:
        // SetType<CompressedSkeletonPoseKeys>();
        break;
    case 0x586DF4E458014768:
        // SetType<AnimatedValueInterface<int>>();
        break;
    case 0x5896A6FD1866FD93:
        // SetType<Handle<Rules>>();
        break;
    case 0x58FFE612BE51E727:
        // SetType<ptable>();
        break;
    case 0x593F9647E67E405D:
        // SetType<EnlightenModule::EnlightenSystemSettings>();
        break;
    case 0x599C62C7A01A35E3:
        // SetType<Procedural_LookAt::Constraint>();
        break;
    case 0x59A72EC50742FCD0:
        SetType<Map<String, PropertySet, std::less<String>>>();
        break;
    case 0x59D13F814FD13B69:
        SetType<CompressedSkeletonPoseKeys2>();
        break;
    case 0x59F6BEC43DCEDCA4:
        SetType<KeyframedValue<Vector2>>();
        break;
    case 0x59FA44B05D07FB9A:
        // SetType<DlgConditionalCase>();
        break;
    case 0x5A21B47B07AE5F3A:
        // SetType<CompressedPathBlockingValue::CompressedPathInfoKey>();
        break;
    case 0x5A28394291AC4B54:
        // SetType<skl>();
        break;
    case 0x5A4EA6259BAD5C4B:
        // SetType<StyleGuide>();
        break;
    case 0x5A52F0EF7B012233:
        // SetType<KeyframedValue<Polar>>();
        break;
    case 0x5A907691E82FECD5:
        // SetType<DCArray<HandleLock<Scene>>>();
        break;
    case 0x5AA107762678E76C:
        SetType<DCArray<KeyframedValue<Vector4>::Sample>>();
        break;
    case 0x5AB7A3011948922B:
        SetType<KeyframedValue<Handle<D3DMesh>>>();
        break;
    case 0x5B2B9A5E74916816:
        // SetType<SingleValue<Handle<SoundBusSnapshot::SnapshotSuite>>>();
        break;
    case 0x5B50C09B7CD0CCF3:
        SetType<BinaryBuffer>();
        break;
    case 0x5BA42D3DE8EF60AB:
        // SetType<AnimatedValueInterface<PhonemeKey>>();
        break;
    case 0x5C4D98899648138E:
        // SetType<CompressedKeys<Symbol>>();
        break;
    case 0x5C62C369F193C3A0:
        // SetType<AnimatedValueInterface<Handle<Scene>>>();
        break;
    case 0x5D043364452053FE:
        // SetType<SoundReverbPreset>();
        break;
    case 0x5D199F8AC4F57196:
        SetType<Map<Symbol, float, std::less<Symbol>>>();
        break;
    case 0x5D39DE4AC5468B6E:
        // SetType<KeyframedValue<LocationInfo>>();
        break;
    case 0x5D3E9FC6FA9369BF:
        SetType<KeyframedValue<Transform>>();
        break;
    case 0x5D4EFA69722CE03A:
        // SetType<AnimatedValueInterface<Polar>>();
        break;
    case 0x5DAEEE1F30D32952:
        // SetType<DCArray<T3ToonGradientRegion>>();
        break;
    case 0x5DBB10F7184DA54B:
        // SetType<EnumT3LightEnvType>();
        break;
    case 0x5DC78F79FC4B8DF7:
        SetType<double>();
        break;
    case 0x5E61265E357AFC4C:
        // SetType<sprite>();
        break;
    case 0x5E68A39907A4BE48:
        // SetType<CinematicLightRig>();
        break;
    case 0x5E94AE2504A2DA08:
        // SetType<EnumeTangentModes>();
        break;
    case 0x5EEA36B36DB856E9:
        // SetType<AnimatedValueInterface<Handle<SoundReverbDefinition>>>();
        break;
    case 0x5F247AEF6E83EF25:
        // SetType<AgentMap>();
        break;
    case 0x5F637A07408DBC60:
        // SetType<LanguageResLocal>();
        break;
    case 0x5F76C68DB5A05134:
        // SetType<BlendGraphManager>();
        break;
    case 0x5F92F79D3FDCAC13:
        // SetType<SingleVector3Value>();
        break;
    case 0x5FA519AB4F3689E7:
        // SetType<DCArray<T3MaterialTransform2D>>();
        break;
    case 0x5FF1D56859B6478E:
        // SetType<DlgConditionInput>();
        break;
    case 0x600C633971977C27:
        // SetType<SingleValue<SoundEventName<1>>>();
        break;
    case 0x606C515AC74B48C2:
        // SetType<EnlightenModule::EnumeAgentUsage>();
        break;
    case 0x60D71CA7E7F3D272:
        // SetType<RenderObject_PostMaterial>();
        break;
    case 0x60D8FA0B4245E96B:
        // SetType<EnumEmitterParticleCountType>();
        break;
    case 0x6113F397D5F03347:
        // SetType<SkeletonPoseValue::Sample>();
        break;
    case 0x61C5765C788DC9F4:
        // SetType<Map<int, Ptr<DialogItem>, less<int>>>();
        break;
    case 0x61D00957E63D7435:
        // SetType<Handle<VoiceData>>();
        break;
    case 0x620211ED1DF8D233:
        // SetType<CompressedKeys<Transform>>();
        break;
    case 0x62045DC19ADEF8FB:
        // SetType<Handle<ParticleProperties>>();
        break;
    case 0x62C9E560C8DCEC67:
        // SetType<Quaternion>();
        break;
    case 0x62E12E4195FD62D1:
        // SetType<KeyframedValue<SoundEventName<0>>>();
        break;
    case 0x631987AF82113CFC:
        // SetType<ScriptEnum : LightComposerCameraZone>();
        break;
    case 0x632FB17165B867C2:
        // SetType<T3OcclusionMeshData>();
        break;
    case 0x634167EE598932B9:
        SetType<Transform>();
        break;
    case 0x63EA9D46465510F6:
        // SetType<Map<unsignedlong, Font::GlyphInfo, less<unsignedlong>>>();
        break;
    case 0x641290F53D772AA0:
        // SetType<AnimatedValueInterface<Vector2>>();
        break;
    case 0x6424EE88F6D2ACEC:
        // SetType<T3MaterialPassData>();
        break;
    case 0x644ECB516BD073C4:
        // SetType<look>();
        break;
    case 0x645625BA2CB6235F:
        // SetType<EnumParticleAffectorType>();
        break;
    case 0x65739F9F4ED9BCD6:
        // SetType<List<Color>>();
        break;
    case 0x65BE4D3CABB2822B:
        // SetType<BlendEntry>();
        break;
    case 0x65C0587D94DC7E70:
        // SetType<EnumEmitterConstraintType>();
        break;
    case 0x65C63A60CC086F5A:
        // SetType<PathTo>();
        break;
    case 0x65FCA07EBA43311B:
        // SetType<Map<unsignedint, Font::GlyphInfo, less<unsignedint>>>();
        break;
    case 0x6643AF6DCCCC81A9:
        // SetType<Handle<Chore>>();
        break;
    case 0x668DE2C55BFAB966:
        // SetType<Map<Symbol, DCArray<LanguageResLocal>, less<Symbol>>>();
        break;
    case 0x66FAE2CA87A8B228:
        // SetType<EnumT3DetailShadingType>();
        break;
    case 0x6708DDFD39E39EB8:
        SetType<DCArray<T3MeshLocalTransformEntry>>();
        break;
    case 0x67104C20C9691329:
        // SetType<KeyframedValue<Handle<Dlg>>>();
        break;
    case 0x673D28039395A91A:
        SetType<SArray<TRange<float>, 3>>();
        break;
    case 0x673D6BC4E630EA46:
        // SetType<Handle<PhonemeTable>>();
        break;
    case 0x67600F19A2762290:
        // SetType<EnumMeshDebugRenderType>();
        break;
    case 0x681AF06EDA9AF05D:
        // SetType<DlgChildSetChoicesChildPost>();
        break;
    case 0x68CD2023740B9FB6:
        // SetType<Handle<SoundEventSnapshotData>>();
        break;
    case 0x68FCF5B6A0D4663A:
        // SetType<CompressedKeys<Handle<PropertySet>>>();
        break;
    case 0x691645DFF205619A:
        SetType<BitSetBase<4>>();
        break;
    case 0x6917635899F0EF5B:
        // SetType<DCArray<KeyframedValue<Handle<Scene>>::Sample>>();
        break;
    case 0x69CC70C207E837F3:
        // SetType<EnumT3LightEnvLODBehavior>();
        break;
    case 0x69DEAEC62B811B75:
        // SetType<DCArray<PreloadPackage::RuntimeDataDialog::DlgObjIdAndStartNodeOffset>>();
        break;
    case 0x6A096DD746A73FF0:
        // SetType<DebugString>();
        break;
    case 0x6B070125830EF084:
        SetType<KeyframedValue<float>>();
        break;
    case 0x6B41C56C3F991BF7:
        // SetType<cameraselectresource>();
        break;
    case 0x6B62F90BD5F79321:
        SetType<SArray<unsigned char, 32>>();
        break;
    case 0x6B77C806C0E23EA1:
        // SetType<SingleValue<Vector3>>();
        break;
    case 0x6BB83C914E70CF53:
        // SetType<FileName<SoundEventBankDummy>>();
        break;
    case 0x6C1B0BA38A23328D:
        // SetType<AnimatedValueInterface<float>>();
        break;
    case 0x6C8D05D6EB869AD0:
        // SetType<DCArray<EventStorage::PageEntry>>();
        break;
    case 0x6D4051136C21FB5B:
        SetType<T3MeshData>();
        break;
    case 0x6DCC6CB4CF833225:
        // SetType<HandleObjectInfo>();
        break;
    case 0x6DCCD180EF5DB842:
        // SetType<T3RenderStateBlock>();
        break;
    case 0x6F17E5736E879C8C:
        SetType<DCArray<unsigned int>>();
        break;
    case 0x6F2E039E6740E40E:
        // SetType<ScriptEnum : LightComposerNodeLocation>();
        break;
    case 0x6F727FA52828A910:
        // SetType<Handle<SoundReverbDefinition>>();
        break;
    case 0x6FD491DEF336185E:
        // SetType<DlgNodeCancelChoices>();
        break;
    case 0x6FEB39335B7CC2BA:
        // SetType<List<PropertySet>>();
        break;
    case 0x707D175FE1B5F859:
        // SetType<DlgNodeSequence::Element>();
        break;
    case 0x70A82513EF128B90:
        // SetType<WalkPath>();
        break;
    case 0x70CAD06EDCFEBCB4:
        // SetType<Map<MetaClassDescriptionconst *__ptr64, int, less<MetaClassDescriptionconst *__ptr64>>>();
        break;
    case 0x72B05EE52AB65857:
        // SetType<Chore>();
        break;
    case 0x72CD1B7B793305EA:
        // SetType<SkeletonPose>();
        break;
    case 0x72D57A55D36D2C57:
        SetType<KeyframedValue<String>>();
        break;
    case 0x72FBCDA2FD2C6314:
        // SetType<anm>();
        break;
    case 0x73AC7A77C69A13A9:
        SetType<DCArray<T3MeshEffectPreloadEntry>>();
        break;
    case 0x73CD313F2A6634FF:
        // SetType<Set<String, StringCompareCaseInsensitive>>();
        break;
    case 0x73E09E0F84717F0A:
        SetType<Handle<D3DMesh>>();
        break;
    case 0x73E6A067ABDBD2D9:
        // SetType<ScriptEnum : BlendTypes>();
        break;
    case 0x746B85A804E2AE3A:
        // SetType<Handle<ResourceGroupInfo>>();
        break;
    case 0x746B9BB09CE91202:
        // SetType<HermiteCurvePathSegment>();
        break;
    case 0x74959B5BA49B660E:
        SetType<DCArray<T3MeshMaterial>>();
        break;
    case 0x74A5F683AFAC29ED:
        // SetType<EnlightenModule::EnlightenMeshSettings::AutoUVSettings>();
        break;
    case 0x7533FAA271BCAF4B:
        // SetType<AgentState>();
        break;
    case 0x75361C1381F026A1:
        // SetType<DCArray<KeyframedValue<SoundEventName<2>>::Sample>>();
        break;
    case 0x75769C9923F19ECA:
        // SetType<SingleValue<Polar>>();
        break;
    case 0x75D673493AED55BC:
        // SetType<poiblocking>();
        break;
    case 0x75D9082D642E1791:
        SetType<BoundingBox>();
        break;
    case 0x75E3A1B073B8BB2F:
        // SetType<List<HandleLock<Scene>>>();
        break;
    case 0x75ECF0E2FCF2E91B:
        // SetType<BitSetBase<6>>();
        break;
    case 0x762110F462C81422:
        // SetType<DCArray<KeyframedValue<ScriptEnum>::Sample>>();
        break;
    case 0x764A963C6BAC44EA:
        SetType<T3MeshEffectPreloadDynamicFeatures>();
        break;
    case 0x76592B0CF8E8A12F:
        SetType<DCArray<T3MeshBoneEntry>>();
        break;
    case 0x766BB06D64BF383B:
        // SetType<MeshSceneEnlightenData>();
        break;
    case 0x773ECCCE0DD2EDAD:
        // SetType<EnumRenderLightmapUVGenerationType>();
        break;
    case 0x774CFA08CA715D06:
        SetType<Animation>();
        break;
    case 0x77752EC5B9F72F50:
        // SetType<Localization::Language>();
        break;
    case 0x7864EA122E854260:
        SetType<HandleBase>();
        break;
    case 0x789758CB1A8D6628:
        // SetType<DlgNodeConditional>();
        break;
    case 0x78C24585666591D2:
        // SetType<Map<unsignedlong, LanguageRes, less<unsignedlong>>>();
        break;
    case 0x794CE6477AD312C6:
        // SetType<Matrix4>();
        break;
    case 0x79AC7384BA26F801:
        // SetType<CompressedKeys<float>>();
        break;
    case 0x79E85A8EA53E63DE:
        // SetType<dlog>();
        break;
    case 0x7A3099E94F6D0010:
        // SetType<SingleValue<Handle<SoundAmbience::AmbienceDefinition>>>();
        break;
    case 0x7A54490338F7688B:
        // SetType<EnlightenModule::EnumeInstanceType>();
        break;
    case 0x7A8562DB047D102C:
        // SetType<KeyframedValueInterface>();
        break;
    case 0x7A90614607315516:
        // SetType<AnimatedValueInterface<Handle<PropertySet>>>();
        break;
    case 0x7AA1E420099D0EB9:
        // SetType<particle>();
        break;
    case 0x7B6B9766211625BF:
        // SetType<EnlightenModule::EnumeUpdateMethodWithDefault>();
        break;
    case 0x7BBCA244E61F1A07:
        SetType<Vector2>();
        break;
    case 0x7BC15620354C0704:
        // SetType<KeyframedValue<Handle<Font>>>();
        break;
    case 0x7BD8BBB0C473B1B8:
        // SetType<DlgNodeWait>();
        break;
    case 0x7C3B4835AC024C7E:
        // SetType<PhonemeKey>();
        break;
    case 0x7CACEEBCD26D075C:
        SetType<int32>();
        break;
    case 0x7CBA2F7647F0AE16:
        // SetType<Handle<Rule>>();
        break;
    case 0x7CF961832ED64527:
        SetType<KeyframedValue<Vector4>>();
        break;
    case 0x7D0AE6CA0E07BD29:
        // SetType<DArray<bool>>();
        break;
    case 0x7D5B490DEF40D9C2:
        // SetType<Handle<AnimOrChore>>();
        break;
    case 0x7DFFEEAAEC61CE08:
        // SetType<EnumEmitterColorType>();
        break;
    case 0x7E3D4347720BF477:
        // SetType<ResourceGroups>();
        break;
    case 0x7E69BFAB6FFA19EC:
        SetType<T3MeshEffectPreload>();
        break;
    case 0x7ED5149ED891D304:
        // SetType<LipSync2>();
        break;
    case 0x7EDCD6DB33A5DC53:
        // SetType<RecordingUtils::EnumRecordingStatus>();
        break;
    case 0x7F7A0E1D5BB715F4:
        // SetType<CompressedKeys<int>>();
        break;
    case 0x7FC56832C53FD39C:
        // SetType<DCArray<KeyframedValue<T3VertexBufferSample<T3NormalSampleData, T3HeapAllocator>>::Sample>>();
        break;
    case 0x807F39F9A39D8998:
        // SetType<Map<PreloadPackage::ResourceKey, PreloadPackage::ResourceSeenTimes, less<PreloadPackage::ResourceKey>>>();
        break;
    case 0x808E66877691132B:
        // SetType<CompressedKeys<ScriptEnum>>();
        break;
    case 0x8090795CD87B5B38:
        SetType<DCArray<T3MaterialStaticParameter>>();
        break;
    case 0x809DA55341AB9E70:
        // SetType<SoundEventData>();
        break;
    case 0x80B6CC288DA51483:
        // SetType<SoundBusSnapshot::SnapshotSuite>();
        break;
    case 0x80F1EBB9FABAC892:
        // SetType<SingleValue<int>>();
        break;
    case 0x813ECC5708C35999:
        // SetType<DCArray<SkeletonPoseValue::Sample>>();
        break;
    case 0x81C39B4E937FC726:
        // SetType<Map<Symbol, TransitionMap::TransitionMapInfo, less<Symbol>>>();
        break;
    case 0x81FA12B1E2409F18:
        // SetType<T3MaterialCompiledData>();
        break;
    case 0x823DB9F90B846250:
        SetType<Handle<Skeleton>>();
        break;
    case 0x826B8E99FDBE2397:
        // SetType<EnumEmitterSpawnShape>();
        break;
    case 0x828001AD1111D929:
        // SetType<SingleValue<T3VertexBufferSample<T3PositionSampleData, T3HeapAllocator>>>();
        break;
    case 0x82D163B740475ACD:
        // SetType<EnumHBAOQualityLevel>();
        break;
    case 0x82E3C1E7C757BBB5:
        // SetType<EnumT3MaterialSwizzleType>();
        break;
    case 0x83AFDE994EFEA3D9:
        // SetType<Handle<ActorAgentMapper>>();
        break;
    case 0x83F92DB3ED618AC1:
        // SetType<DCArray<PreloadPackage::ResourceKey>>();
        break;
    case 0x84283CB979D71641:
        SetType<Flags>();
        break;
    case 0x849BD029B8FB3C04:
        // SetType<ActorAgentBinding>();
        break;
    case 0x852A87571E57CCF8:
        SetType<Sphere>();
        break;
    case 0x853C6A11208F77EF:
        // SetType<DCArray<MeshSceneLightmapData::Entry>>();
        break;
    case 0x858C44125C5F73D9:
        // SetType<DCArray<KeyframedValue<Handle<SoundData>>::Sample>>();
        break;
    case 0x85CB35E50E5A49CA:
        // SetType<PreloadPackage::RuntimeDataDialog>();
        break;
    case 0x85D954F4C0C69E97:
        // SetType<DlgNodeExchange>();
        break;
    case 0x85FF27A5CB393B95:
        // SetType<lang>();
        break;
    case 0x862D2C86A17B7074:
        // SetType<SceneInstData>();
        break;
    case 0x864794AA58A0278B:
        // SetType<Map<String, AnimOrChore, less<String>>>();
        break;
    case 0x86877501EAEBB05D:
        // SetType<SingleValue<String>>();
        break;
    case 0x86BB9E63D621E93A:
        // SetType<AssetCollection>();
        break;
    case 0x86C465FE6C9DBC7A:
        // SetType<DCArray<KeyframedValue<Handle<SoundEventSnapshotData>>::Sample>>();
        break;
    case 0x86CB40E8A4CBC02D:
        // SetType<AnimatedValueInterface<Symbol>>();
        break;
    case 0x86DD6FDD80394AB3:
        SetType<BoneContraints>();
        break;
    case 0x8758F70880295F9B:
        // SetType<Handle<SoundAmbience::AmbienceDefinition>>();
        break;
    case 0x878A3470E047E140:
        // SetType<Map<int, Ptr<DialogDialog>, less<int>>>();
        break;
    case 0x87B6B95067DB12F9:
        // SetType<DlgChildSetConditionalCase>();
        break;
    case 0x87E0E880D7D2DFC1:
        // SetType<DlgObjID>();
        break;
    case 0x880F40C15BF127CC:
        // SetType<InputMapper::RawEvent>();
        break;
    case 0x881C335AC79F7149:
        SetType<DCArray<Color>>();
        break;
    case 0x885A35D99A8D1A4D:
        SetType<Set<Symbol, std::less<Symbol>>>();
        break;
    case 0x88E2A4048B7CAC53:
        SetType<AnimationValueInterfaceBase>();
        break;
    case 0x890FBC61216787A2:
        // SetType<ScriptEnum : StruggleType>();
        break;
    case 0x890FE2DA04AADE49:
        SetType<Map<String, float, std::less<String>>>();
        break;
    case 0x8911CDF45ADA55C7:
        // SetType<CompressedKeys<SoundEventName<0>>>();
        break;
    case 0x89161F76F17740BA:
        // SetType<T3LightSceneInternalData::QualityEntry>();
        break;
    case 0x8940087148BF4C61:
        // SetType<DlgNode>();
        break;
    case 0x897A64EEBA89CB81:
        // SetType<EnumParticleSortMode>();
        break;
    case 0x89B98A5E91B73118:
        // SetType<List<Handle<D3DMesh>>>();
        break;
    case 0x89DB7A1D44D121E0:
        // SetType<Map<String, Ptr<JiraRecord>, less<String>>>();
        break;
    case 0x8A5F6779E068540B:
        // SetType<CinematicLight>();
        break;
    case 0x8A62816F311682F5:
        // SetType<Map<int, Ptr<DialogExchange>, less<int>>>();
        break;
    case 0x8A6F9FEE5DA74241:
        // SetType<Map<int, LanguageResource, less<int>>>();
        break;
    case 0x8ACE27FDA34B2606:
        // SetType<Handle<SoundBusSnapshot::SnapshotSuite>>();
        break;
    case 0x8AD17AD4CB809956:
        SetType<Map<String, bool, std::less<String>>>();
        break;
    case 0x8AEB6B64F5F95861:
        // SetType<Map<Symbol, Footsteps2::FootstepBank, less<Symbol>>>();
        break;
    case 0x8AEC41470104B6E7:
        // SetType<DCArray<KeyframedValue<SoundEventName<1>>::Sample>>();
        break;
    case 0x8B1BEC7A8664079A:
        // SetType<aam>();
        break;
    case 0x8B5F43130CAB9935:
        // SetType<CompressedKeys<Handle<SoundBusSnapshot::SnapshotSuite>>>();
        break;
    case 0x8B9A601312D0C170:
        // SetType<AnimatedValueInterface<ScriptEnum>>();
        break;
    case 0x8BE6399AE3073DD3:
        // SetType<Procedural_LookAt::EnumLookAtComputeStage>();
        break;
    case 0x8C0CD13A87BA8D95:
        SetType<BitSetBase<9>>();
        break;
    case 0x8D1A8F0E83A1E29D:
        // SetType<LanguageDB>();
        break;
    case 0x8D25F96848DE1765:
        // SetType<SkeletonPoseValue>();
        break;
    case 0x8D53D2745D07232B:
        // SetType<DlgObjIDOwner>();
        break;
    case 0x8D76811F807928A2:
        // SetType<SoundBankWaveMap>();
        break;
    case 0x8D953B4CE053F7AC:
        SetType<DCArray<int>>();
        break;
    case 0x8E0C950E1D3BF60C:
        SetType<Map<String, int, std::less<String>>>();
        break;
    case 0x8E4726F9B542D02F:
        // SetType<bundle>();
        break;
    case 0x8E88FBB78405598C:
        // SetType<EnumPlatformType>();
        break;
    case 0x8EEA3302024628B7:
        // SetType<EnlightenModule::EnlightenMeshSettings>();
        break;
    case 0x8EFB0961ECAFBCC7:
        // SetType<CompressedKeys<AnimOrChore>>();
        break;
    case 0x8F11614B53249632:
        // SetType<Map<DlgObjID, int, DlgObjIDLess>>();
        break;
    case 0x8F2D7CA196304667:
        // SetType<EnumEmitterSpriteAnimationType>();
        break;
    case 0x8F40C634A937DD2A:
        // SetType<AnimatedValueInterface<Handle<SoundEventData>>>();
        break;
    case 0x9004C5587575D6C0:
        SetType<bool>();
        break;
    case 0x900DB52347B506E5:
        // SetType<Agent>();
        break;
    case 0x90AECEC9208A96B6:
        SetType<Map<String, DCArray<String>, std::less<String>>>();
        break;
    case 0x91220203C6648B2A:
        // SetType<DlgNodeStart>();
        break;
    case 0x915709E72A07B3ED:
        // SetType<DlgChildSet>();
        break;
    case 0x918069BEE7BDA403:
        SetType<AnimatedValueInterface<Quaternion>>();
        break;
    case 0x91E8421A820D689C:
        // SetType<Meta::AgentResourceContext>();
        break;
    case 0x93008E1D006FB6E0:
        // SetType<ScriptEnum : AIPatrolType>();
        break;
    case 0x9352BA2255605A10:
        SetType<Map<Symbol, Symbol, std::less<Symbol>>>();
        break;
    case 0x937F5D487A0988E3:
        // SetType<T3SamplerStateBlock>();
        break;
    case 0x9395A07A617964C9:
        // SetType<Handle<StyleGuide>>();
        break;
    case 0x9397970E4D4168B9:
        // SetType<ParticleProperties>();
        break;
    case 0x93FD7A72DFF5E058:
        // SetType<DCArray<LanguageLookupMap::DlgIDSet>>();
        break;
    case 0x94991C29CD442F79:
        // SetType<EnumDOFQualityLevel>();
        break;
    case 0x94C4526CF9F79AC5:
        // SetType<DateStamp>();
        break;
    case 0x94D45772A1FF48C0:
        // SetType<AnimatedValueInterface<T3VertexBufferSample<T3NormalSampleData, T3HeapAllocator>>>();
        break;
    case 0x95112BCCF1AFDB66:
        // SetType<CompressedKeys<Handle<SoundAmbience::AmbienceDefinition>>>();
        break;
    case 0x954B47E44A5FFA6E:
        SetType<AnimatedValueInterface<bool>>();
        break;
    case 0x954F8FF8B3F40B36:
        // SetType<reverb>();
        break;
    case 0x95A97D3178992D3C:
        // SetType<Map<Symbol, Localization::Language, less<Symbol>>>();
        break;
    case 0x96214C23CC241657:
        // SetType<Handle<StyleGuideRef>>();
        break;
    case 0x9646F3B778897027:
        // SetType<AnimatedValueInterface<SoundEventName<0>>>();
        break;
    case 0x96C27FFE888A31BA:
        // SetType<DlgNodeParallel::PElement>();
        break;
    case 0x96EA4DA540CA16F4:
        // SetType<RenderObject_Text2>();
        break;
    case 0x9746954D9C0478DD:
        // SetType<KeyframedValue<T3VertexBufferSample<T3NormalSampleData, T3HeapAllocator>>>();
        break;
    case 0x977F2FCE90AA72BB:
        // SetType<LinkedList<Scene::AgentInfo, 0>>();
        break;
    case 0x97BA9139CCC1CF26:
        // SetType<DlgNodeParallel>();
        break;
    case 0x984AF9732DDDDA16:
        // SetType<LinkedBallTwistJointKey>();
        break;
    case 0x984C0D6D48F69A9D:
        SetType<DCArray<Vector2>>();
        break;
    case 0x98A19836CF4CCB7D:
        SetType<D3DMesh>();
        break;
    case 0x98A7496918F17715:
        // SetType<bankwavemap>();
        break;
    case 0x995FC5C3CB87E5F8:
        // SetType<PhysicsObject::EnumePhysicsBoundingVolumeType>();
        break;
    case 0x998E73C393F6A122:
        // SetType<PhonemeTable::PhonemeEntry>();
        break;
    case 0x99B7E7B82012690C:
        // SetType<EnlightenModule::EnumeProbeResolution>();
        break;
    case 0x99D7C52EA7F0F97D:
        SetType<int>();
        break;
    case 0x9A3A4A9E63375381:
        // SetType<Font>();
        break;
    case 0x9A80BEF7E55274B6:
        // SetType<CompressedKeys<Vector4>>();
        break;
    case 0x9A946F2A83FC7658:
        // SetType<CompressedKeys<Quaternion>>();
        break;
    case 0x9B20C35CA1E12BD5:
        // SetType<EnumRenderAntialiasType>();
        break;
    case 0x9B3EE0F7AEE83B13:
        // SetType<Map<SoundFootsteps::EnumMaterial, SoundEventName<0>, less<SoundFootsteps::EnumMaterial>>>();
        break;
    case 0x9B52B73BB2BFE113:
        SetType<DCArray<T3MeshLOD>>();
        break;
    case 0x9BAEBE80F400BAA8:
        // SetType<LocomotionDB>();
        break;
    case 0x9C7EB5CBCB3A7C7E:
        // SetType<Ptr<PtrBase>>();
        break;
    case 0x9CEAD8A38E5C4258:
        SetType<T3MeshLocalTransformEntry>();
        break;
    case 0x9CFA106A1AD61711:
        SetType<DCArray<T3MaterialTexture>>();
        break;
    case 0x9D25F5E686CCDF56:
        // SetType<SingleValue<Handle<D3DMesh>>>();
        break;
    case 0x9D2D91124150CFFB:
        // SetType<JiraRecordManager>();
        break;
    case 0x9D52A3E9C5186D6F:
        // SetType<EnumBokehQualityLevel>();
        break;
    case 0x9DEC4BBA95CEDB28:
        // SetType<DCArray<ChoreResource::Block>>();
        break;
    case 0x9E2BF42C54C646B1:
        // SetType<DCArray<KeyframedValue<LocationInfo>::Sample>>();
        break;
    case 0x9EB1467F36B078EB:
        SetType<Map<Symbol, Map<Symbol, Set<Symbol, std::less<Symbol>>, std::less<Symbol>>, std::less<Symbol>>>();
        break;
    case 0x9EE5E31EF2F71F0E:
        // SetType<Handle<Scene>>();
        break;
    case 0x9F60B383C5B65967:
        // SetType<ScriptEnum : DialogMode>();
        break;
    case 0x9FAB8543532BE4A7:
        // SetType<DlgNodeSequence::DlgChildSetElement>();
        break;
    case 0x9FC197BAD88CCF6D:
        // SetType<DlgObjectPropsMap::GroupDefinition>();
        break;
    case 0x9FD30C6E5D0260E5:
        // SetType<llm>();
        break;
    case 0xA000ECC5490A2A94:
        // SetType<EnumT3LightEnvMobility>();
        break;
    case 0xA062BDC063405146:
        // SetType<PointOfInterestBlocking>();
        break;
    case 0xA06BF34A7666964F:
        // SetType<LipSync>();
        break;
    case 0xA084DFBDCD7D1FE7:
        // SetType<CompressedKeys<T3VertexBufferSample<T3NormalSampleData, T3HeapAllocator>>>();
        break;
    case 0xA0C46F5EEAF99112:
        // SetType<audiobus>();
        break;
    case 0xA0E41C8DB5CA9B1C:
        // SetType<SkeletonPoseValue::BoneEntry>();
        break;
    case 0xA0EDBE204F68C863:
        // SetType<SingleValue<Handle<Dlg>>>();
        break;
    case 0xA10F60E34D2DA3B0:
        // SetType<LightProbeData>();
        break;
    case 0xA14B12F2880C71F0:
        // SetType<Handle<PreloadPackage::RuntimeDataDialog>>();
        break;
    case 0xA1975655F1C71142:
        // SetType<DCArray<Handle<Scene>>>();
        break;
    case 0xA1B5E14F4AF83C27:
        SetType<T3GFXBuffer>();
        break;
    case 0xA2048C57716AD85F:
        SetType<DCArray<T3Texture>>();
        break;
    case 0xA2435650D27ACF90:
        // SetType<EnlightenModule::EnumeSceneOptimisationMode>();
        break;
    case 0xA33B55750C7BF243:
        SetType<Map<int, int, std::less<int>>>();
        break;
    case 0xA34E655ED1345F8B:
        // SetType<WalkAnimator>();
        break;
    case 0xA35C247B710DFF99:
        SetType<DCArray<KeyframedValue<Handle<PropertySet>>::Sample>>();
        break;
    case 0xA36BC2EB0A5B26AF:
        // SetType<ProceduralEyes>();
        break;
    case 0xA3A998B26DBC4FBB:
        // SetType<DCArray<ResourceBundle::ResourceInfo>>();
        break;
    case 0xA406267E2A2F22D9:
        SetType<T3MeshBoneEntry>();
        break;
    case 0xA47918A7D3C3A67A:
        // SetType<Handle<PhysicsObject>>();
        break;
    case 0xA4811058F13AB197:
        // SetType<SoundEventBankDummy>();
        break;
    case 0xA4ECFBE186FB1452:
        // SetType<T3OverlayData>();
        break;
    case 0xA5190A70F8F74C4C:
        SetType<DCArray<KeyframedValue<Transform>::Sample>>();
        break;
    case 0xA56C05706DC70A8B:
        // SetType<SingleValue<Handle<SoundBusSnapshot::Snapshot>>>();
        break;
    case 0xA5B4E0529A022754:
        // SetType<AnimOrChore>();
        break;
    case 0xA5D09E10B6CE1CC4:
        SetType<DCArray<unsigned char>>();
        break;
    case 0xA62FE74CCFA3467C:
        // SetType<EnlightenModule::EnumeDistributedBuildSystem>();
        break;
    case 0xA6E64DD3378991B4:
        // SetType<SoundAmbience::AmbienceDefinition>();
        break;
    case 0xA7152CED90755212:
        // SetType<DlgFolder>();
        break;
    case 0xA7353268AC8AAD1F:
        SetType<DCArray<T3MaterialCompiledData>>();
        break;
    case 0xA7A8C91070E4C52E:
        // SetType<DCArray<ParticleSprite::Animation>>();
        break;
    case 0xA7DAAA296D1491CC:
        SetType<DCArray<T3MeshTexture>>();
        break;
    case 0xA7FE20E35345AC33:
        // SetType<DlgLine>();
        break;
    case 0xA877237AFCDAAA59:
        SetType<KeyframedValue<Handle<PropertySet>>>();
        break;
    case 0xA8C7AA1469C78EA2:
        // SetType<List<List<Symbol>>>();
        break;
    case 0xA8E93E14BF58645C:
        // SetType<DCArray<Ptr<ActingAccentPalette>>>();
        break;
    case 0xA8F90B07ADEFAB41:
        SetType<short>();
        break;
    case 0xA96424E7FCCBF8EB:
        // SetType<EnumT3LightEnvBakeOnStatic>();
        break;
    case 0xA98EAE8F6CFF1125:
        // SetType<Map<String, LogicGroup::LogicItem, less<String>>>();
        break;
    case 0xA98F0652295DE685:
        // SetType<EnumT3MaterialLightModelType>();
        break;
    case 0xAA9E970095A20B0E:
        // SetType<StyleIdleTransitionsRes>();
        break;
    case 0xAAFF3A6B600D4D00:
        // SetType<CompressedKeys<SoundEventName<1>>>();
        break;
    case 0xAB04CC2F75BCF6C0:
        // SetType<DCArray<Ptr<ActingPaletteGroup>>>();
        break;
    case 0xAB4BFA2304C2292C:
        // SetType<Font::GlyphInfo>();
        break;
    case 0xAB929FC5155636EF:
        // SetType<RootKey>();
        break;
    case 0xABA164D5AAB73489:
        // SetType<Map<int, DlgLine, less<int>>>();
        break;
    case 0xABB6151861AA76C7:
        // SetType<Scene::AgentInfo>();
        break;
    case 0xABD836B706872262:
        // SetType<Handle<DialogResource>>();
        break;
    case 0xAC389286CDE5A182:
        // SetType<Map<Symbol, SoundBankWaveMapEntry, less<Symbol>>>();
        break;
    case 0xAD15A7FE0904AE6A:
        // SetType<EnumT3LightEnvGroup>();
        break;
    case 0xAD550479D1324785:
        // SetType<DlgDownstreamVisibilityConditions>();
        break;
    case 0xADABE93EAA87F7DB:
        // SetType<Camera>();
        break;
    case 0xAF292B29059F879B:
        // SetType<LocalizationRegistry>();
        break;
    case 0xAFB5DB7305E23480:
        SetType<int8>();
        break;
    case 0xB02BC4AD45C96F0E:
        // SetType<FootSteps>();
        break;
    case 0xB038C6742811D7FA:
        // SetType<DCArray<CorrespondencePoint>>();
        break;
    case 0xB03A4E300519F2C1:
        SetType<__int64>();
        break;
    case 0xB056BCD869E07B38:
        // SetType<DCArray<KeyframedValue<Handle<SoundEventData>>::Sample>>();
        break;
    case 0xB060A66E8CD67299:
        // SetType<DCArray<SklNodeData>>();
        break;
    case 0xB0F644BC42B51B0B:
        // SetType<KeyframedValue<Handle<Scene>>>();
        break;
    case 0xB1F4EDB8750E7BFA:
        // SetType<Procedural_LookAt_Value>();
        break;
    case 0xB32B46B47690925E:
        // SetType<DlgNodeCriteria::EnumDefaultResultT>();
        break;
    case 0xB36577F91D1BF28C:
        // SetType<CompressedQuaternionKeys2>();
        break;
    case 0xB3740F5DEE93334A:
        // SetType<PivotJointKey>();
        break;
    case 0xB4292F0DA0DEA9EB:
        SetType<Map<unsigned int, Set<Symbol, std::less<Symbol>>, std::less<unsigned int>>>();
        break;
    case 0xB45FAE180770628C:
        // SetType<EnlightenModule>();
        break;
    case 0xB4C683CEFE185EA1:
        // SetType<DlgNodeStoryBoard>();
        break;
    case 0xB54642189B1237CA:
        // SetType<DlgVisibilityConditions>();
        break;
    case 0xB5A80428425E68E0:
        // SetType<AnimatedValueInterface<SoundEventName<1>>>();
        break;
    case 0xB5D28DB9AA796F18:
        // SetType<DCArray<Procedural_LookAt::Constraint>>();
        break;
    case 0xB64F1AE3E7BBC58F:
        // SetType<EnlightenModule::EnumeQualityWithDefault>();
        break;
    case 0xB68C72191F215606:
        // SetType<langres>();
        break;
    case 0xB6DDB3CC25BAB0A1:
        // SetType<AgentMap::AgentMapEntry>();
        break;
    case 0xB705C1A4E971420E:
        // SetType<LogicGroup::LogicItem>();
        break;
    case 0xB72556399FBC3C04:
        // SetType<AnimatedValueInterface<T3VertexBufferSample<T3PositionSampleData, T3HeapAllocator>>>();
        break;
    case 0xB76962276766EA0A:
        // SetType<PathSegment>();
        break;
    case 0xB76E07D6BB899BFE:
        SetType<Vector4>();
        break;
    case 0xB76E52C699301BDA:
        SetType<DCArray<T3MaterialTextureParam>>();
        break;
    case 0xB876B4CEF80F1EDB:
        // SetType<DCArray<ActingPaletteClass>>();
        break;
    case 0xB8AC7017234E9F78:
        // SetType<ResourceGroupInfo>();
        break;
    case 0xB930FF00A4687C7E:
        // SetType<Handle<InputMapper>>();
        break;
    case 0xBA2A9CC6D78EDEA8:
        // SetType<SingleValue<Handle<SoundEventSnapshotData>>>();
        break;
    case 0xBA4781F930BE11F7:
        // SetType<DCArray<KeyframedValue<Handle<SoundBusSnapshot::SnapshotSuite>>::Sample>>();
        break;
    case 0xBA6CABFE529F5849:
        // SetType<DCArray<InputMapper::EventMapping>>();
        break;
    case 0xBABC2FCF7E7B70AA:
        // SetType<Style>();
        break;
    case 0xBAE4CBD77F139A91:
        SetType<float>();
        break;
    case 0xBAF342C1FC31C370:
        SetType<T3GFXVertexState>();
        break;
    case 0xBB01AD6EFE5EE662:
        // SetType<List<T3ToonGradientRegion>>();
        break;
    case 0xBB03444E2D5051F5:
        // SetType<KeyframedValue<Handle<SoundBusSnapshot::Snapshot>>>();
        break;
    case 0xBB0D8C38D7C34967:
        // SetType<SingleValue<T3VertexBufferSample<T3NormalSampleData, T3HeapAllocator>>>();
        break;
    case 0xBB6BAD6A055D7EDB:
        // SetType<EnlightenModule::EnumeAutoUVSimplificationMode>();
        break;
    case 0xBB6D47AFCEF5DC7B:
        // SetType<DlgFolderChild>();
        break;
    case 0xBB7E5208092CAA9F:
        // SetType<BallJointKey>();
        break;
    case 0xBB86B36D253B1EC8:
        // SetType<ColorHDR>();
        break;
    case 0xBBC6633C9F6B2537:
        // SetType<PerAgentClipResourceFilter>();
        break;
    case 0xBC2BBAEBB7DD049B:
        // SetType<AnimationManager>();
        break;
    case 0xBC62744AC9114C72:
        SetType<Set<int, std::less<int>>>();
        break;
    case 0xBC6B9F28CC33A947:
        // SetType<Procedural_LookAt>();
        break;
    case 0xBCA387FC2FAAEAE9:
        // SetType<DCArray<LightGroupInstance>>();
        break;
    case 0xBD4C9F5B0EC743C2:
        SetType<Map<String, Vector3, std::less<String>>>();
        break;
    case 0xBDB2F6DC0135CA3E:
        // SetType<InverseKinematicsAttach>();
        break;
    case 0xBDEBB69D2C134E45:
        // SetType<EnumT3NPRSpecularType>();
        break;
    case 0xBE12CAA65204CDE4:
        // SetType<DCArray<KeyframedValue<Handle<Dlg>>::Sample>>();
        break;
    case 0xBE2A918022753C0F:
        // SetType<DCArray<FileName<SoundEventBankDummy>>>();
        break;
    case 0xBE89EB598EBB294D:
        // SetType<LanguageResource>();
        break;
    case 0xBF2E8C49D2783BDC:
        // SetType<Map<String, Rule *__ptr64, less<String>>>();
        break;
    case 0xBF34FB893AC17AAD:
        // SetType<Map<Symbol, PhonemeTable::PhonemeEntry, less<Symbol>>>();
        break;
    case 0xBF8F61B0F64AED35:
        // SetType<CompressedKeys<Vector2>>();
        break;
    case 0xBFB0CE2BD1F38792:
        // SetType<DlgChild>();
        break;
    case 0xBFC99E3D3E3CBB4A:
        // SetType<InverseKinematicsDerived>();
        break;
    case 0xBFD0071071629E03:
        // SetType<Map<unsignedint, LanguageRes, less<unsignedint>>>();
        break;
    case 0xBFD68E6E1C629E01:
        SetType<T3MaterialRuntimeProperty>();
        break;
    case 0xC04ED0CBAF7D9C90:
        // SetType<EnumGlowQualityLevel>();
        break;
    case 0xC07A4D6DA8CD0B6C:
        // SetType<Handle<BlendGraphManager>>();
        break;
    case 0xC09A0F1FEE902C1A:
        // SetType<CSPK2Context>();
        break;
    case 0xC0B682D7D515ED83:
        // SetType<Handle<SoundEventBankDummy>>();
        break;
    case 0xC0E90B6129B2DADA:
        // SetType<CompressedKeys<bool>>();
        break;
    case 0xC16762F7763D62AB:
        SetType<Color>();
        break;
    case 0xC1E4AC327DAD6D1C:
        // SetType<bgh>();
        break;
    case 0xC2254DAAD52E7340:
        // SetType<Handle<PhysicsData>>();
        break;
    case 0xC23697BBFB06DD17:
        // SetType<Handle<LanguageResource>>();
        break;
    case 0xC39BEABE5AD9E70C:
        // SetType<DCArray<Ptr<DlgChild>>>();
        break;
    case 0xC3EFDA35DDD4ABC3:
        // SetType<List<float>>();
        break;
    case 0xC41AA69F9B838B0A:
        // SetType<Map<int, Ptr<DialogBranch>, less<int>>>();
        break;
    case 0xC472E26D936CE1A8:
        // SetType<SingleValue<Vector2>>();
        break;
    case 0xC475B96DE47A0DD8:
        // SetType<DlgNodeNotes>();
        break;
    case 0xC478B1CC1D7D94B7:
        // SetType<SaveGame>();
        break;
    case 0xC4D5427CF81B6B1F:
        // SetType<Set<FileName<SoundEventBankDummy>, less<FileName<SoundEventBankDummy>>>>();
        break;
    case 0xC4F8BD87AEC361E6:
        // SetType<SingleValue<Handle<SoundReverbDefinition>>>();
        break;
    case 0xC561A117A7710B6A:
        SetType<T3MaterialPreShader>();
        break;
    case 0xC5C3044FA9C1D61F:
        // SetType<CompressedKeys<Handle<SoundEventData>>>();
        break;
    case 0xC604C9307F8A6EB1:
        // SetType<AnimatedValueInterface<Handle<PhonemeTable>>>();
        break;
    case 0xC6136FB4A18BBE93:
        SetType<BitSetBase<5>>();
        break;
    case 0xC61768F8C7376559:
        // SetType<Handle<SoundBusSnapshot::Snapshot>>();
        break;
    case 0xC69D25163737A7F3:
        // SetType<DCArray<KeyframedValue<CompressedPathBlockingValue::CompressedPathInfoKey>::Sample>>();
        break;
    case 0xC74E20BBF90CEB7C:
        // SetType<List<Handle<Rules>>>();
        break;
    case 0xC7ED283D130BC1FE:
        // SetType<CompressedKeys<LocationInfo>>();
        break;
    case 0xC810FA560D267D67:
        SetType<Map<Symbol, PropertySet, std::less<Symbol>>>();
        break;
    case 0xC8564FB0D1D68883:
        // SetType<InverseKinematicsBase>();
        break;
    case 0xC8A7A09B43C48E97:
        // SetType<FilterArea>();
        break;
    case 0xC8D1F9C70A684B97:
        // SetType<ParticlePropConnect>();
        break;
    case 0xC96C8DBBBEA1DEAB:
        // SetType<EnumTextOrientationType>();
        break;
    case 0xC995828AC3B803F2:
        SetType<DCArray<Skeleton::Entry>>();
        break;
    case 0xC9CA51C8795945F0:
        // SetType<DCArray<WalkBoxes::Vert>>();
        break;
    case 0xCA26CD88FAD4EF7E:
        // SetType<EnlightenModule::EnlightenLightSettings>();
        break;
    case 0xCA272B9CDA05B750:
        // SetType<bgm>();
        break;
    case 0xCA874E09192E2598:
        SetType<AnimatedValueInterface<Color>>();
        break;
    case 0xCB029403B12D08D6:
        SetType<unsigned int>();
        break;
    case 0xCB17BA9E6EF9F5A9:
        SetType<AnimatedValueInterface<Vector3>>();
        break;
    case 0xCB31FAC32D7FAD8D:
        // SetType<eyes>();
        break;
    case 0xCB39F1559069B3BA:
        // SetType<wav>();
        break;
    case 0xCB9B7B7C2D2A90E7:
        // SetType<EnumT3LightEnvEnlightenBakeBehavior>();
        break;
    case 0xCBF0AB8D9CB98AEF:
        SetType<DCArray<KeyframedValue<float>::Sample>>();
        break;
    case 0xCBFD53673C25ECC0:
        // SetType<EnumHTextAlignmentType>();
        break;
    case 0xCC77A061EBC3ABED:
        // SetType<AudioData>();
        break;
    case 0xCCDF9AEC974E91FC:
        // SetType<CompressedKeys<Handle<WalkBoxes>>>();
        break;
    case 0xCCE2FC8ABD78A775:
        // SetType<EnlightenModule::EnumeProbeResolutionWithDefault>();
        break;
    case 0xCD75DC4F6B9F15D2:
        SetType<PropertySet>();
        break;
    case 0xCD9B448F1003E791:
        SetType<KeyframedValue<Color>>();
        break;
    case 0xCD9C6E605F5AF4B4:
        SetType<String>();
        break;
    case 0xCDA6183D330B433B:
        // SetType<ChoreInst>();
        break;
    case 0xCDD094E2E769C2B5:
        // SetType<ToolProps>();
        break;
    case 0xCDFC7236DB3B636B:
        // SetType<EnumRenderTextureResolution>();
        break;
    case 0xCE1B42C4736DEB3A:
        // SetType<DlgObjectProps>();
        break;
    case 0xCECACE3A835CB7EE:
        // SetType<SingleValue<Quaternion>>();
        break;
    case 0xCECC22CA2F746449:
        // SetType<CompressedKeys<SoundEventName<2>>>();
        break;
    case 0xCF3AE053D709090B:
        // SetType<DCArray<Handle<AudioData>>>();
        break;
    case 0xCF7134C9149B5131:
        // SetType<EnumBase>();
        break;
    case 0xCF8A73B34BC665CC:
        // SetType<AnimatedValueInterface<AnimOrChore>>();
        break;
    case 0xCFAF2019AB83376A:
        // SetType<KeyframedValue<Handle<SoundAmbience::AmbienceDefinition>>>();
        break;
    case 0xCFD0EBF69D907EED:
        SetType<T3MaterialEnlightenPrecomputeParams>();
        break;
    case 0xD01D47E19594B3E9:
        // SetType<T3OverlayParams>();
        break;
    case 0xD0A931F89ED7734D:
        // SetType<CompressedKeys<T3VertexBufferSample<T3PositionSampleData, T3HeapAllocator>>>();
        break;
    case 0xD0B8814E41A8A279:
        SetType<DCArray<KeyframedValue<Symbol>::Sample>>();
        break;
    case 0xD0E7D2AFB7D9C68B:
        // SetType<DlgNodeText>();
        break;
    case 0xD170386D6E88C1AF:
        // SetType<T3LightEnvLOD>();
        break;
    case 0xD19B1C890D2741A9:
        // SetType<AnimatedValueInterface<SoundEventName<2>>>();
        break;
    case 0xD1C9280F82A39E78:
        // SetType<SingleValue<Handle<T3Texture>>>();
        break;
    case 0xD1EF776F1BEFCA35:
        // SetType<ActingPaletteClass>();
        break;
    case 0xD1F049E6EAEA09DD:
        // SetType<SingleValue<bool>>();
        break;
    case 0xD27EA1BFAC786303:
        // SetType<Set<Color, less<Color>>>();
        break;
    case 0xD2D678B2AA9112D8:
        // SetType<DCArray<DlgNodeInstanceSequence::ElemInstanceData>>();
        break;
    case 0xD2E7CDB2B4266AE2:
        // SetType<DCArray<HandleBase>>();
        break;
    case 0xD388A4AFB51DB41C:
        // SetType<AnimatedValueInterface<Handle<WalkBoxes>>>();
        break;
    case 0xD3C3AA7C4CDFF788:
        // SetType<KeyframedValue<T3VertexBufferSample<T3PositionSampleData, T3HeapAllocator>>>();
        break;
    case 0xD471D07BB4F74743:
        // SetType<List<unsignedint>>();
        break;
    case 0xD48D0C3B810C1975:
        SetType<DCArray<PropertySet>>();
        break;
    case 0xD4B5597D859A03DE:
        // SetType<PreloadPackage::ResourceKey>();
        break;
    case 0xD4BFE847C1725627:
        // SetType<DCArray<RenderObject_Mesh::TextureInstance>>();
        break;
    case 0xD4D0C7977631D29D:
        // SetType<SingleValue<ScriptEnum>>();
        break;
    case 0xD513AEAF2180FC7E:
        // SetType<DlgNodeCriteria::EnumThresholdT>();
        break;
    case 0xD521915AA8E8C0F7:
        SetType<DCArray<KeyframedValue<Handle<T3Texture>>::Sample>>();
        break;
    case 0xD5C86012BF6B91CA:
        // SetType<LanguageResProxy>();
        break;
    case 0xD5D35E216D0124D6:
        // SetType<Dlg>();
        break;
    case 0xD6652FB7B143EA32:
        // SetType<AutoActStatus>();
        break;
    case 0xD6A50A09FEA7E4A6:
        SetType<DCArray<KeyframedValue<Vector3>::Sample>>();
        break;
    case 0xD713BF2F0EEF6FE0:
        SetType<KeyframedValue<bool>>();
        break;
    case 0xD78BF3D477EC3DFB:
        SetType<Map<String, Set<String, std::less<String>>, std::less<String>>>();
        break;
    case 0xD7CE90BB8FFA4753:
        // SetType<EnumT3MaterialNormalSpaceType>();
        break;
    case 0xD7FF03FA339F3F62:
        // SetType<DlgVisibilityConditionsOwner>();
        break;
    case 0xD8785AF203AA53EB:
        // SetType<DCArray<Map<String, String, less<String>>>>();
        break;
    case 0xD8794539F89A180E:
        // SetType<List<Handle<SoundData>>>();
        break;
    case 0xD8893CCA081E38A2:
        SetType<Map<Symbol, String, std::less<Symbol>>>();
        break;
    case 0xD93FCCB03BC94F69:
        // SetType<ambience>();
        break;
    case 0xD940A60D3DE56488:
        // SetType<BallTwistJointKey>();
        break;
    case 0xD941AA25E96493EB:
        // SetType<RenderObject_Mesh>();
        break;
    case 0xD97E0C880A33ADCE:
        // SetType<DlgNodeLogic>();
        break;
    case 0xD992E1D329469995:
        SetType<DCArray<KeyframedValue<int>::Sample>>();
        break;
    case 0xD9E5E39D06F0A6E3:
        // SetType<List<bool>>();
        break;
    case 0xDA31784DA793EAA2:
        // SetType<KeyframedValue<Handle<SoundEventSnapshotData>>>();
        break;
    case 0xDA3D01BDBECEDE15:
        // SetType<KeyframedValue<PhonemeKey>>();
        break;
    case 0xDAC65150E4EE6266:
        // SetType<EnlightenModule::EnumeRadiositySampleRate>();
        break;
    case 0xDAE9DA89AF7C3612:
        SetType<BitSetBase<7>>();
        break;
    case 0xDBD3D5D932FEA4DA:
        // SetType<MovieCaptureInfo::EnumCompressorType>();
        break;
    case 0xDC03A83314ADFC51:
        // SetType<Handle<BlendGraph>>();
        break;
    case 0xDCD169E0C98FE760:
        // SetType<T3MaterialTransform2D>();
        break;
    case 0xDDADACE79FB1DDF0:
        // SetType<EnumHBAOParticipationType>();
        break;
    case 0xDDB5965209539B0E:
        // SetType<snapshotsuite>();
        break;
    case 0xDDE3A9E749A30518:
        SetType<unsigned__int64>();
        break;
    case 0xDE877F4252845725:
        // SetType<probe>();
        break;
    case 0xDE9FEE749B0ED110:
        // SetType<EnumRenderMaskWrite>();
        break;
    case 0xDF2C74713A04DDA7:
        // SetType<Handle<SoundData>>();
        break;
    case 0xDF302FFF123E7CAB:
        SetType<T3MaterialParameter>();
        break;
    case 0xDF30362E292BEF14:
        // SetType<CompressedKeys<Color>>();
        break;
    case 0xDFA5071C13D73E63:
        // SetType<Handle<AgentMap>>();
        break;
    case 0xE008B7EFBA7579D4:
        // SetType<DlgNodeExchange::Entry>();
        break;
    case 0xE00CB3BD8BD8ACE7:
        // SetType<LightType>();
        break;
    case 0xE04937724C9E5EF1:
        // SetType<List<Handle<AudioData>>>();
        break;
    case 0xE05D92D1490181FA:
        // SetType<PreloadPackage::RuntimeDataDialog::DialogResourceInfo>();
        break;
    case 0xE06CA3604D85DCB6:
        // SetType<DlgNodeScript>();
        break;
    case 0xE09B099B8076C147:
        // SetType<ResourceBundle>();
        break;
    case 0xE0B18DCC44F3E24D:
        // SetType<SingleValue<Symbol>>();
        break;
    case 0xE0F187F2BB24DD1F:
        SetType<T3MaterialTexture>();
        break;
    case 0xE0FDB8250AD3923D:
        // SetType<AnimatedValueInterface<String>>();
        break;
    case 0xE115A057E3014D94:
        // SetType<CompressedKeys<Handle<Font>>>();
        break;
    case 0xE139ECA106BB239A:
        // SetType<SingleValue<Handle<SoundEventData>>>();
        break;
    case 0xE17D3D2A8074782B:
        // SetType<SingleValue<Vector4>>();
        break;
    case 0xE1C51CF067B11F25:
        // SetType<DCArray<PreloadPackage::RuntimeDataDialog::DlgObjIdAndResourceVector>>();
        break;
    case 0xE1E6CA8E844E23EB:
        // SetType<T3LightProbeInternalData>();
        break;
    case 0xE2602DAF0134246D:
        SetType<DCArray<Transform>>();
        break;
    case 0xE26BBBA29EBA3E2A:
        // SetType<DlgChainHead>();
        break;
    case 0xE2ACF7CEBEA09992:
        // SetType<KeyframedValue<AnimOrChore>>();
        break;
    case 0xE2AF89E495F738E2:
        SetType<DCArray<DCArray<String>>>();
        break;
    case 0xE2BA743E952F9338:
        SetType<T3MaterialData>();
        break;
    case 0xE2BF28F948F35B68:
        // SetType<SingleValue<Color>>();
        break;
    case 0xE2D51D83712BDC5A:
        // SetType<Map<String, SoundBusSystem::BusDescription, less<String>>>();
        break;
    case 0xE31CB0F3B2932710:
        SetType<BitSetBase<3>>();
        break;
    case 0xE340A108AD7DCEB1:
        // SetType<CompressedKeys<Handle<Scene>>>();
        break;
    case 0xE366AC7546B12675:
        // SetType<DlgNodeInstanceParallel::ElemInstanceData>();
        break;
    case 0xE37774F4D4CD6E67:
        // SetType<BlendGraph::EnumBlendGraphType>();
        break;
    case 0xE38C3CAC5CF8DCEC:
        // SetType<tmap>();
        break;
    case 0xE3BC39514745D2DE:
        // SetType<Map<SoundFootsteps::EnumMaterial, DCArray<Handle<SoundData>>, less<SoundFootsteps::EnumMaterial>>>();
        break;
    case 0xE4510BD515264FE5:
        // SetType<langdb>();
        break;
    case 0xE494D922BF9DFB44:
        // SetType<T3ToonGradientRegion>();
        break;
    case 0xE4E5A2E3EC044937:
        SetType<DCArray<KeyframedValue<String>::Sample>>();
        break;
    case 0xE4E87E07690A89E6:
        // SetType<InputMapper>();
        break;
    case 0xE4E8C8ABFF566D60:
        // SetType<dss>();
        break;
    case 0xE6130DF4EDCEC9C8:
        // SetType<DlgConditionSet>();
        break;
    case 0xE6293E22F651B314:
        // SetType<DCArray<SkeletonPoseValue::BoneEntry>>();
        break;
    case 0xE67D8AC64150698E:
        // SetType<SingleValue<Handle<PhonemeTable>>>();
        break;
    case 0xE6B45077A341070A:
        // SetType<List<Handle<Chore>>>();
        break;
    case 0xE73848E8EAE76623:
        // SetType<CompressedPathBlockingValue>();
        break;
    case 0xE7D7C131B05A9D80:
        // SetType<AnimatedValueInterface<Handle<SoundData>>>();
        break;
    case 0xE7E302FBBD9C4126:
        // SetType<DlgNodeParallel::DlgChildSetElement>();
        break;
    case 0xE84BB8D0F7E7F749:
        // SetType<DlgConditionRule>();
        break;
    case 0xE89EBE3CD9FBD25A:
        // SetType<CameraFacingTypes>();
        break;
    case 0xE8B65EEA1581A9DA:
        // SetType<DlgNodeInstanceSequence::ElemInstanceData>();
        break;
    case 0xE8F586C87CB34551:
        // SetType<HandleLock<PropertySet>>();
        break;
    case 0xE908072C98443ADA:
        // SetType<prop>();
        break;
    case 0xE98036E69062C8F4:
        // SetType<ChoreAgent>();
        break;
    case 0xE9EFDB064BDA7682:
        // SetType<DCArray<Handle<AnimOrChore>>>();
        break;
    case 0xE9FA4A9E9D453359:
        SetType<Skeleton::Entry>();
        break;
    case 0xEA086C95C87CA185:
        // SetType<EnlightenModule::EnlightenPrimitiveSettings>();
        break;
    case 0xEA20A667D4C75946:
        // SetType<EnumBokehOcclusionType>();
        break;
    case 0xEAB763402F4836AF:
        // SetType<ScriptEnum>();
        break;
    case 0xEAE06ABE810518EE:
        // SetType<T3LightEnvInternalData>();
        break;
    case 0xEB48981A297A46B7:
        // SetType<KeyframedValue<Handle<SoundReverbDefinition>>>();
        break;
    case 0xEB7FE6D415249768:
        // SetType<Handle<PreloadPackage::RuntimeDataScene>>();
        break;
    case 0xEB906C78C340D4A6:
        SetType<SArray<Handle<T3Texture>, 1>>();
        break;
    case 0xECB739634B43D072:
        // SetType<Map<Symbol, Map<Symbol, int, less<Symbol>>, less<Symbol>>>();
        break;
    case 0xEE3C7E2110139663:
        SetType<DCArray<DCArray<PropertySet>>>();
        break;
    case 0xEE3FD7CC7ED685E9:
        // SetType<DlgChoicesChildPre>();
        break;
    case 0xEE65A936C01E9C9A:
        // SetType<KeyframedValue<Handle<PhonemeTable>>>();
        break;
    case 0xEEF01208F0F466CD:
        // SetType<AnimatedValueInterface<Handle<Chore>>>();
        break;
    case 0xEEF9EEDD05A42AEA:
        // SetType<ScriptEnum : MenuAlignment>();
        break;
    case 0xEFA1BA20E620F40F:
        // SetType<T3Texture::StreamHeader>();
        break;
    case 0xEFC64D422DF9376F:
        // SetType<DependencyLoader<1>>();
        break;
    case 0xF0181C2BFD4EA8D6:
        // SetType<Polar>();
        break;
    case 0xF0205400D4C83EBC:
        SetType<TRange<float>>();
        break;
    case 0xF07C552824816DD1:
        SetType<char>();
        break;
    case 0xF07D50698E252C35:
        // SetType<ldb>();
        break;
    case 0xF0CA92E85C1E9849:
        SetType<KeyframedValue<Handle<T3Texture>>>();
        break;
    case 0xF17A1008ADE9BDCD:
        // SetType<EnumDepthOfFieldType>();
        break;
    case 0xF195067C56F55DD3:
        // SetType<DCArray<WalkBoxes::Quad>>();
        break;
    case 0xF297790770C35A97:
        SetType<Map<int, String, std::less<int>>>();
        break;
    case 0xF2C0E4B485AF6F5B:
        // SetType<imap>();
        break;
    case 0xF31B900E385D5320:
        // SetType<IntrusiveSet<Symbol, PropertySet::KeyInfo, TagPropertyKeyInfoSet, Symbol::CompareCRC>>();
        break;
    case 0xF343D8D117C6ED72:
        // SetType<CompressedKeys<Handle<SoundReverbDefinition>>>();
        break;
    case 0xF3A0D2B0CA777981:
        // SetType<Set<Ptr<PlaybackController>, less<Ptr<PlaybackController>>>>();
        break;
    case 0xF3E07C3D67895FD1:
        SetType<DCArray<T3MeshBatch>>();
        break;
    case 0xF47250AB93E98778:
        // SetType<Rollover>();
        break;
    case 0xF47CD36D533ECCB5:
        SetType<DCArray<KeyframedValue<Quaternion>::Sample>>();
        break;
    case 0xF496A008F1E15BA5:
        // SetType<EnumHBAOPreset>();
        break;
    case 0xF4DB84D1EC8B1578:
        // SetType<SoundEventBankMap>();
        break;
    case 0xF5302008E0012D0A:
        // SetType<Scene>();
        break;
    case 0xF5BF2ED9B8F3B6E4:
        // SetType<SoundReverbDefinition>();
        break;
    case 0xF5D798B82914F0F9:
        // SetType<PlaceableBallTwistJointKey>();
        break;
    case 0xF61F7BA7EA84F63B:
        SetType<Map<String, Map<String, DCArray<String>, std::less<String>>, std::less<String>>>();
        break;
    case 0xF6792A98BDA977A7:
        // SetType<EnumLightCellBlendMode>();
        break;
    case 0xF6D4C230B74B44FD:
        // SetType<DlgConditionTime>();
        break;
    case 0xF6F394AF6E4003AD:
        SetType<KeyframedValue<Vector3>>();
        break;
    case 0xF70A9218630D4FF4:
        // SetType<DCArray<Handle<SoundData>>>();
        break;
    case 0xF720178956CB9F80:
        // SetType<SoundEventName<1>>();
        break;
    case 0xF7D8D0ECA82AA7FF:
        // SetType<DCArray<BlendEntry>>();
        break;
    case 0xF7DF47AB15C99066:
        // SetType<SingleValue<Handle<PropertySet>>>();
        break;
    case 0xF7FA917047267F56:
        // SetType<EnumVTextAlignmentType>();
        break;
    case 0xF82881A26B7647A6:
        // SetType<EnlightenModule::EnlightenAutoProbeVolumeSettings>();
        break;
    case 0xF84DFA4EC80325D8:
        // SetType<DCArray<ParticleProperties::Animation>>();
        break;
    case 0xF880FF729209B860:
        // SetType<CompressedKeys<Handle<SoundData>>>();
        break;
    case 0xF8E76EC13E469046:
        // SetType<CompressedVector3Keys2>();
        break;
    case 0xF9F4A9C47B852D14:
        // SetType<SoundEventSnapshotData>();
        break;
    case 0xFA26600C4954EA02:
        // SetType<SingleValue<unsigned__int64>>();
        break;
    case 0xFA6C8889876EBA7A:
        // SetType<RenderSwizzleParams>();
        break;
    case 0xFA7FC6889D2A5CFC:
        // SetType<ParticleLODKey>();
        break;
    case 0xFAD2B7D432F6E393:
        // SetType<EnumHBAOPerPixelNormals>();
        break;
    case 0xFB0617E6C51F821D:
        // SetType<Environment>();
        break;
    case 0xFB30E42239EC1AF5:
        // SetType<T3LightEnvInternalData::QualityEntry>();
        break;
    case 0xFBC46015AD30C413:
        // SetType<DCArray<KeyframedValue<Handle<D3DMesh>>::Sample>>();
        break;
    case 0xFC21C32667FC91B4:
        // SetType<InputMapper::EventMapping>();
        break;
    case 0xFC6597EB1FE5458E:
        // SetType<CompressedTransformKeys>();
        break;
    case 0xFC7C5120ABAA70AA:
        // SetType<overlay>();
        break;
    case 0xFC96DFDEDE31FB4A:
        SetType<unsigned long>();
        break;
    case 0xFCB10E2F8E89DB2B:
        // SetType<SoundBusSnapshot::Snapshot>();
        break;
    case 0xFCE72EB881AEAFB7:
        // SetType<LocalizeInfo>();
        break;
    case 0xFD0F32CBB13B258D:
        // SetType<CompressedKeys<Handle<SoundBusSnapshot::Snapshot>>>();
        break;
    case 0xFD267A5B808A5824:
        // SetType<List<Handle<AnimOrChore>>>();
        break;
    case 0xFD45D124E5FAC6CE:
        // SetType<T3MeshMaterial>();
        break;
    case 0xFD5454BA0F088B05:
        // SetType<wbox>();
        break;
    case 0xFE828771D8009C1D:
        // SetType<preloadpackagertd>();
        break;
    case 0xFE96A13E293CC8EF:
        // SetType<Map<String, DCArray<unsignedchar>, less<String>>>();
        break;
    case 0xFF15DC09F8B4F0E1:
        // SetType<IdleTransitionSettings>();
        break;
    case 0xFF38D8541F524A49:
        // SetType<ActingOverridablePropOwner>();
        break;
    case 0xFF5781EF90514A8C:
        // SetType<ClipResourceFilter>();
        break;
    case 0xFFA2F0E137146530:
        // SetType<Scene::AgentQualitySettings>();
        break;
    case 0xFFE605CEBC64AF91:
        SetType<BitSetBase<1>>();
        break;
    case 0xFFEA794BCAFBF983:
        // SetType<SoundSystem::Implementation::ChannelHolder>();
        break;
    case 0xFFECC5B70AD06BE6:
        // SetType<PhysicsObject::EnumePhysicsCollisionType>();
        break;
    default:
        break;
    }
}

} // namespace TTH