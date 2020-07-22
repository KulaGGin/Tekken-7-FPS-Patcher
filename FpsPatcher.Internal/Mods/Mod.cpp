#include "Mod.h"

namespace FPSPatcher {
    void Mod::SwitchMod() {
        if(_enabled) {
            _enabled = false;
            CancelMod();
        }
        else {
            _enabled = true;
            ApplyMod();
        }
    }
}
