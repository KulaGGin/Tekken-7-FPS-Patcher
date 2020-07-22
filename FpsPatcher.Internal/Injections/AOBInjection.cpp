#include "AOBInjection.h"

namespace FPSPatcher {
    AOBInjection::AOBInjection(MemoryCommando::MemoryCommando& memoryCommando) : _memoryCommando(memoryCommando) {
    }

    std::string AOBInjection::GetAoBSignature() const {
        return _aobSignature;
    }

    void AOBInjection::Inject() const {
        const DWORD originalProtection = _memoryCommando.QueryVirtualMemory(_injectionAddress).AllocationProtect;
        _memoryCommando.ProtectVirtualMemory(_injectionAddress, _injectionMachineCode.size(), PAGE_EXECUTE_READWRITE);
        _memoryCommando.WriteVirtualMemory(_injectionAddress, _injectionMachineCode);
        _memoryCommando.ProtectVirtualMemory(_injectionAddress, _injectionMachineCode.size(), originalProtection);
    }

    void AOBInjection::CancelInjection() const {
        _memoryCommando.WriteVirtualMemory(_injectionAddress, _originalMachineCode);
    }

    uintptr_t AOBInjection::InitializeInjectionAddress(MemoryCommando::MemoryCommando& memoryCommando, const std::string& aobInjectionSignature) {
        const uintptr_t injectionAddress = memoryCommando.ScanVirtualMemory(L"TekkenGame-Win64-Shipping.exe", aobInjectionSignature)[0];

        return injectionAddress;
    }

    std::vector<BYTE> AOBInjection::GetOriginalMachineCode(MemoryCommando::MemoryCommando& memoryCommando, uintptr_t injectionAddress, size_t injectionInstructionsLength) {
        std::vector<BYTE> originalMachineCode = memoryCommando.ReadVirtualMemory(injectionAddress, injectionInstructionsLength);

        return originalMachineCode;
    }
}
