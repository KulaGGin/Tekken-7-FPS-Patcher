#include "MatchEndInjection.h"
#include "FPSMod.h"

namespace FPSPatcher {

    MatchEndInjection::MatchEndInjection(MemoryCommando::MemoryCommando& memoryCommando, uintptr_t inGameFPSVariableAddress) : CodeCaveAoBInjection(memoryCommando) {
        _inGameFPSVariableAddress = __int32(inGameFPSVariableAddress);
        _aobSignature = "8B 0B 8B 10 3B CA 7E 04 8B DE EB 20";
        _originalInstructionsLength = 6;
        _injectionAddress = InitializeInjectionAddress(_memoryCommando, _aobSignature);
        _originalMachineCode = GetOriginalMachineCode(memoryCommando, _injectionAddress, _originalInstructionsLength);
        _codeCaveMachineCode = { 0xC7, 0x04, 0x25, 0xE8, 0x88, 0x8F, 0x0A, 0x00, 0x00, 0x70, 0x42 };
        std::memcpy(&_codeCaveMachineCode[3], &_inGameFPSVariableAddress, sizeof _inGameFPSVariableAddress);
        FPSMod::Append(_codeCaveMachineCode, _originalMachineCode);
        const uintptr_t afterInjectionAddress = _injectionAddress + _originalInstructionsLength;
        _codeCaveAddress = MakeCodeCave(_memoryCommando, afterInjectionAddress, _codeCaveMachineCode);
        _memoryCommando.AppendTrampolineMachineCode(_injectionMachineCode, _injectionAddress, _codeCaveAddress);
    }
}
