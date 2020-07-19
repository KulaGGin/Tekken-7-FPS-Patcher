#include "CodeCaveAoBInjection.h"

#include "MemoryCommandoCPP/MemoryCommando/Exceptions/VirtualAllocException.h"
#include <algorithm>

namespace FpsPatcher {

    /*CodeCaveAoBInjection::CodeCaveAoBInjection(MemoryCommando::MemoryCommando& memoryCommando,
                                               std::string                     aobInjectionSignature,
                                               const size_t                    injectionInstructionsLength,
                                               std::vector<BYTE>               codeCaveMachineCode) :
        AOBInjection(std::move(aobInjectionSignature)),
        _memoryCommando{ memoryCommando } {

        _injectionInstructionsLength = injectionInstructionsLength;
        _codeCaveMachineCode = std::move(codeCaveMachineCode);
        _injectionAddress = InitializeInjectionAddress(_aobSignature, _memoryCommando);
        const uintptr_t afterInjectionAddress = _injectionAddress + _injectionInstructionsLength;
        _codeCaveAddress = MakeCodeCave(afterInjectionAddress, _codeCaveAddress, _codeCaveMachineCode, _memoryCommando);
        _originalMachineCode = GetOriginalMachineCode(_injectionAddress, _injectionInstructionsLength, memoryCommando);

        _memoryCommando.AppendTrampolineMachineCode(_injectionMachineCode, _injectionAddress, _codeCaveAddress);

         _injectionMachineCode.push_back(0xE9);
        const int32_t     injectionJumpOffset = _codeCaveAddress - (_injectionAddress + sizeof int32_t);
        std::vector<BYTE> injectionJumpOffsetBytes = MemoryCommando::HelperMethods::ConvertObjectToBytes(injectionJumpOffset);
        _injectionMachineCode.insert(_injectionMachineCode.begin(), injectionJumpOffsetBytes.begin(), injectionJumpOffsetBytes.end());

        _codeCaveMachineCode.push_back(0xE9);
        const uintptr_t   afterInjectionAddress = _injectionAddress + _injectionInstructionsLength;
        const int32_t     codeCaveJumpOffset = afterInjectionAddress - (_codeCaveAddress + _codeCaveMachineCode.size() + _jmpSize);
        std::vector<BYTE> codeCaveJumpOffsetBytes = MemoryCommando::HelperMethods::ConvertObjectToBytes(codeCaveJumpOffset);
        _codeCaveMachineCode.insert(_codeCaveMachineCode.begin(), codeCaveJumpOffsetBytes.begin(), codeCaveJumpOffsetBytes.end());
    }*/

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
        memoryCommando.AppendTrampolineMachineCode(codeCaveMachineCode, codeCaveMachineCodeEndAddress, afterInjectionAddress);

        memoryCommando.WriteVirtualMemory(codeCaveStartAddress, codeCaveMachineCode);

        return codeCaveStartAddress;
    }
}
