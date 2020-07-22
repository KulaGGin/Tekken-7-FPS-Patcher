#pragma once
#include "Injections/CodeCaveAoBInjection.h"

namespace FPSPatcher {
    class MatchStartInjection : public CodeCaveAoBInjection {
    public:
        explicit MatchStartInjection(MemoryCommando::MemoryCommando& memoryCommando, uintptr_t inGameMaxFPSAddress, size_t maxFPSValue);

    private:
        static std::vector<BYTE> GenerateCodeCaveMachineCode(uintptr_t inGameMaxFPSAddress);
        uintptr_t _maxFPSValue;
        uintptr_t _customMaxFPSAddress;
        uintptr_t _inGameMaxFPSAddress;
    };
}

