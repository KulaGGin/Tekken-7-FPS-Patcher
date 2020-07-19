#pragma once
#include "MemoryCommandoCPP/MemoryCommando/MemoryCommando.h"
#include <windows.h>
#include <utility>
#include <vector>

#include "AOBInjection.h"

namespace FpsPatcher {
    class CodeCaveAoBInjection : public AOBInjection {
    public:
        virtual ~CodeCaveAoBInjection();
    protected:
        std::vector<BYTE> _codeCaveMachineCode{};
        uintptr_t _codeCaveAddress{};

        CodeCaveAoBInjection(MemoryCommando::MemoryCommando& memoryCommando);

        static uintptr_t MakeCodeCave(MemoryCommando::MemoryCommando& memoryCommando, uintptr_t afterInjectionAddress, std::vector<BYTE>& codeCaveMachineCode);
    };
}

