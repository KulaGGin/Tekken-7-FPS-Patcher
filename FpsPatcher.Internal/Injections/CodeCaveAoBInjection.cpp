#include "CodeCaveAoBInjection.h"

#include "MemoryCommandoCPP/MemoryCommando/Exceptions/VirtualAllocException.h"
#include <algorithm>

namespace FPSPatcher {
    CodeCaveAoBInjection::CodeCaveAoBInjection(MemoryCommando::MemoryCommando& memoryCommando) : AOBInjection(memoryCommando) {
    }

    CodeCaveAoBInjection::~CodeCaveAoBInjection() {
        // _memoryCommando.FreeVirtualMemory(_codeCaveAddress);
    }

    uintptr_t CodeCaveAoBInjection::MakeCodeCave(MemoryCommando::MemoryCommando& memoryCommando, const uintptr_t afterInjectionAddress, std::vector<BYTE>& codeCaveMachineCode) {
        const auto systemInfo = MemoryCommando::HelperMethods::GetSystemInfo();
        uintptr_t codeCaveStartAddress = uintptr_t(std::max<ptrdiff_t>(ptrdiff_t(0), ptrdiff_t(afterInjectionAddress - INT32_MAX + systemInfo.dwAllocationGranularity)));
        codeCaveStartAddress = memoryCommando.AllocateVirtualMemoryNear(codeCaveStartAddress, codeCaveMachineCode.size() + 5);

        const uintptr_t codeCaveMachineCodeEndAddress = codeCaveStartAddress + codeCaveMachineCode.size();
        memoryCommando.AppendJumpMachineCode(codeCaveMachineCode, codeCaveMachineCodeEndAddress, afterInjectionAddress);

        memoryCommando.WriteVirtualMemory(codeCaveStartAddress, codeCaveMachineCode);

        return codeCaveStartAddress;
    }
}
