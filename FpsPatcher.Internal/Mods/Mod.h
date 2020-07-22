#pragma once

namespace FPSPatcher {
    class Mod {
    protected:
        virtual ~Mod() = default;
    public:
        virtual void ApplyMod() = 0;
        virtual void CancelMod() = 0;
        void SwitchMod();
    private:
        bool _enabled = false;
    };
}

