#pragma once
#include "Injections/AOBInjection.h"

namespace FPSPatcher {
    class SimpleSelectFixInjection : public AOBInjection {
    public:
        SimpleSelectFixInjection(MemoryCommando::MemoryCommando& memoryCommando);
    };
}

