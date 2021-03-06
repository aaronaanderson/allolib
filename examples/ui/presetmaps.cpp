#include "al/util/ui/al_Preset.hpp"
#include "al/util/ui/al_PresetMapper.hpp"

using namespace al;

int main(int argc, char* argv[]) {
  PresetHandler handler("data/presets-example");
  PresetMapper mapper;
  mapper.registerPresetHandler(handler);
}
