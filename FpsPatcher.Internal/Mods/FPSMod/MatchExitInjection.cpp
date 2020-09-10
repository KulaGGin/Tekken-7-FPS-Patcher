#include "MatchExitInjection.h"

#include "Mods/FPSMod/FPSMod.h"

namespace FPSPatcher {
    MatchExitInjection::MatchExitInjection(MemoryCommando::MemoryCommando& memoryCommando, uintptr_t inGameFPSVariableAddress): CodeCaveAoBInjection(memoryCommando) {
        _inGameFPSVariableAddress = __int32(inGameFPSVariableAddress);
        _aobSignature = "BA 02 00 00 00 48 89 E9 E8 ?? ?? ?? ?? 49 8B 06";
        _originalInstructionsLength = 5;
        _injectionAddress = InitializeInjectionAddress(_memoryCommando, _aobSignature);
        _originalMachineCode = GetOriginalMachineCode(memoryCommando, _injectionAddress, _originalInstructionsLength);
        _codeCaveMachineCode = GenerateCodeCaveMachineCode(inGameFPSVariableAddress);
        FPSMod::Append(_codeCaveMachineCode, _originalMachineCode);
        const uintptr_t afterInjectionAddress = _injectionAddress + _originalInstructionsLength;
        _codeCaveAddress = MakeCodeCave(_memoryCommando, afterInjectionAddress, _codeCaveMachineCode);
        _memoryCommando.AppendJumpMachineCode(_injectionMachineCode, _injectionAddress, _codeCaveAddress);
    }

    std::vector<BYTE> MatchExitInjection::GenerateCodeCaveMachineCode(__int32 inGameFPSVariableAddress) {
        std::vector<BYTE> machineCode;

        FPSMod::Append(machineCode, { 0xC7, 0x04, 0x25 }); // mov [
        FPSMod::Append(machineCode, MemoryCommando::HelperMethods::ConvertObjectToBytes(inGameFPSVariableAddress));
        FPSMod::Append(machineCode, MemoryCommando::HelperMethods::ConvertObjectToBytes(60.0f)); // 60.0f

        return machineCode;
    }
}
