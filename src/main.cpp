#include <tth/animation/animation.hpp>
#include <tth/convert/asset.hpp>
#include <tth/skeleton/skeleton.hpp>
#include <tth/stream/stream.hpp>

using namespace TTH;

int main(void)
{

    Stream sklStream = Stream("/home/asil/Documents/decryption/TelltaleDevTool/cipherTexts/skl/sk61_javier.skl", "rb");
    Stream anmStream = Stream("/home/asil/Documents/decryption/TelltaleDevTool/cipherTexts/animation/sk61_javierAction_toStandA.anm", "rb");

    sklStream.SeekMetaHeaderEnd();
    anmStream.SeekMetaHeaderEnd();

    Skeleton skeleton;
    Animation animation;
    skeleton.Create();
    animation.Create();

    sklStream.Read<Skeleton>(skeleton, false);
    anmStream.Read<Animation>(animation, false);

    ExportAsset("hydra2.glb", skeleton, &animation, 1, 0);

    skeleton.Destroy();
    animation.Destroy();

    return 0;
}