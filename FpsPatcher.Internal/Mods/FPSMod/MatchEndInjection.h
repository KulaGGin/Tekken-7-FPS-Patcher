#pragma once
#include "Injections/CodeCaveAoBInjection.h"

namespace FPSPatcher {
    class MatchEndInjection : public CodeCaveAoBInjection {
    public:
        explicit MatchEndInjection(MemoryCommando::MemoryCommando& memoryCommando, uintptr_t inGameFPSVariableAddress);
    protected:
        __int32 _inGameFPSVariableAddress;
    };
}

