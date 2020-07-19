#pragma once
#include "Injections/AOBInjection.h"

namespace FpsPatcher {
    class SimpleSelectFixInjection : public AOBInjection {
    public:
        SimpleSelectFixInjection(MemoryCommando::MemoryCommando& memoryCommando);
    };
}

