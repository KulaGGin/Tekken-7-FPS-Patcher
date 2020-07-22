#pragma once
#include "Injections/CodeCaveAoBInjection.h"

namespace FpsPatcher {
    class MatchStartInjection : public CodeCaveAoBInjection {
    public:
        explicit MatchStartInjection(MemoryCommando::MemoryCommando& memoryCommando, uintptr_t inGameMaxFpsAddress, size_t maxFPSValue);

    private:
        static std::vector<BYTE> GenerateCodeCaveMachineCode(uintptr_t inGameMaxFpsAddress);
        uintptr_t _maxFPSValue;
        uintptr_t _customMaxFpsAddress;
        uintptr_t _inGameMaxFpsAddress;
    };
}

