#pragma once

#include "Injections/CodeCaveAoBInjection.h"

namespace FPSPatcher {
    class MatchExitInjection final : public CodeCaveAoBInjection {

    public:
        explicit MatchExitInjection(MemoryCommando::MemoryCommando& memoryCommando, uintptr_t inGameFPSVariableAddress);
        static std::vector<BYTE> GenerateCodeCaveMachineCode(int inGameFPSVariableAddress);
        __int32 _inGameFPSVariableAddress;
    };
}

