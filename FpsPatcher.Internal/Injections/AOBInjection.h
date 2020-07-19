#pragma once
#include <string>
#include <utility>

#include "MemoryCommandoCPP/MemoryCommando/MemoryCommando.h"

namespace FpsPatcher {
    class AOBInjection {
    public:
        std::string GetAoBSignature() const;

        void Inject() const;
        void CancelInjection() const;
    protected:
        AOBInjection(MemoryCommando::MemoryCommando& memoryCommando);

        MemoryCommando::MemoryCommando& _memoryCommando;
        size_t _offsetFromAOB;
        uintptr_t _injectionAddress{};
        size_t _originalInstructionsLength{};
        std::vector<BYTE> _originalMachineCode{};
        std::vector<BYTE> _injectionMachineCode{};

        std::string _aobSignature;

        static uintptr_t InitializeInjectionAddress(MemoryCommando::MemoryCommando& memoryCommando, const std::string& aobInjectionSignature);
        static std::vector<BYTE> GetOriginalMachineCode(MemoryCommando::MemoryCommando& memoryCommando, uintptr_t injectionAddress, size_t injectionInstructionsLength);
    };
}

