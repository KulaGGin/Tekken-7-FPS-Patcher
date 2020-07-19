#include "Mod.h"

namespace FpsPatcher {
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
