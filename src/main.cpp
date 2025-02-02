#include <tth/animation/animation.hpp>
#include <tth/convert/asset.hpp>
#include <tth/d3dmesh/d3dmesh.hpp>
#include <tth/skeleton/skeleton.hpp>
#include <tth/stream/stream.hpp>

using namespace TTH;

int main(void)
{

    Stream sklStream = Stream("/home/asil/Documents/decryption/TelltaleDevTool/cipherTexts/skl/skM1_jack.skl", "rb");
    Stream anmStream = Stream("/home/asil/Documents/decryption/TelltaleDevTool/cipherTexts/animation/skM1_action_jackPetsLluna.anm", "rb");
    Stream streamMesh = Stream("/home/asil/Documents/decryption/TelltaleDevTool/cipherTexts/d3dmesh/skM1_jack_body.d3dmesh", "rb");

    sklStream.SeekMetaHeaderEnd();
    anmStream.SeekMetaHeaderEnd();
    streamMesh.SeekMetaHeaderEnd();

    Skeleton skeleton;
    Animation animation;
    D3DMesh mesh;
    skeleton.Create();
    mesh.Create();
    animation.Create();

    sklStream.Read<Skeleton>(skeleton, false);
    anmStream.Read<Animation>(animation, false);
    streamMesh.Read<D3DMesh>(mesh, false);

    ExportAsset("hydra2.glb", skeleton, &animation, &mesh, 1, 1);

    skeleton.Destroy();
    animation.Destroy();
    mesh.Destroy();

    return 0;
}