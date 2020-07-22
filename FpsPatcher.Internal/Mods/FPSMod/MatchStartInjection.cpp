#include "MatchStartInjection.h"

#include "Mods/FPSMod/FPSMod.h"

namespace FPSPatcher {

    MatchStartInjection::MatchStartInjection(MemoryCommando::MemoryCommando& memoryCommando, uintptr_t inGameMaxFPSAddress, size_t maxFPSValue):
    CodeCaveAoBInjection(memoryCommando) {
        _maxFPSValue = maxFPSValue;
        _inGameMaxFPSAddress = inGameMaxFPSAddress;
        _aobSignature = "53 48 83 EC 50 48 8B 05 ?? ?? ?? ?? 48 31 E0 48 89 44 24 40 80 79 62 00 0F B6 DA 0F 84 60 01 00 00";
        _originalInstructionsLength = 5;
        _offsetFromAOB = 0x11D;
        _injectionAddress = InitializeInjectionAddress(_memoryCommando, _aobSignature) + _offsetFromAOB;
        _originalMachineCode = GetOriginalMachineCode(memoryCommando, _injectionAddress, _originalInstructionsLength);
        _codeCaveMachineCode = GenerateCodeCaveMachineCode(_inGameMaxFPSAddress);
        FPSMod::Append(_codeCaveMachineCode, _originalMachineCode);
        const uintptr_t afterInjectionAddress = _injectionAddress + _originalInstructionsLength;
        _codeCaveAddress = MakeCodeCave(_memoryCommando, afterInjectionAddress, _codeCaveMachineCode);
        _memoryCommando.AppendTrampolineMachineCode(_injectionMachineCode, _injectionAddress, _codeCaveAddress);
        _customMaxFPSAddress = _codeCaveAddress + 0x100;
        _memoryCommando.WriteVirtualMemory(_customMaxFPSAddress, static_cast<float>(_maxFPSValue));
    }

    std::vector<BYTE> MatchStartInjection::GenerateCodeCaveMachineCode(const uintptr_t inGameMaxFPSAddress) {
        std::vector<BYTE> codeCaveMachineCode{};

        FPSMod::Append(codeCaveMachineCode, { 0x50 }); // push rax
        FPSMod::Append(codeCaveMachineCode, { 0x48, 0x8b, 0x05, 0xf8, 0x00, 0x00, 0x00 }); // mov rax,QWORD PTR [rip+0xf8]
        FPSMod::Append(codeCaveMachineCode, { 0x51 }); // push rcx
        FPSMod::Append(codeCaveMachineCode, { 0x48, 0xB9 }); // mov rcx,
        FPSMod::Append(codeCaveMachineCode, MemoryCommando::HelperMethods::ConvertObjectToBytes(inGameMaxFPSAddress)); // t.maxFPS address
        FPSMod::Append(codeCaveMachineCode, { 0x48, 0x89, 0x01 }); // mov [rcx],rax
        FPSMod::Append(codeCaveMachineCode, { 0x59 }); // pop rcx
        FPSMod::Append(codeCaveMachineCode, { 0x58 }); // pop rax

        return codeCaveMachineCode;
    }
}
