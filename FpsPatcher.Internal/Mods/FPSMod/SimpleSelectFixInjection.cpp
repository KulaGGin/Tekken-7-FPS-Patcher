#include "SimpleSelectFixInjection.h"

namespace FPSPatcher {
    SimpleSelectFixInjection::SimpleSelectFixInjection(MemoryCommando::MemoryCommando& memoryCommando): AOBInjection(memoryCommando) {
        _aobSignature = "FF 90 40 02 00 00 E8";
        _originalInstructionsLength = 6;
        _offsetFromAOB = 0;
        _injectionAddress = InitializeInjectionAddress(_memoryCommando, _aobSignature) + _offsetFromAOB;
        _originalMachineCode = GetOriginalMachineCode(memoryCommando, _injectionAddress, _originalInstructionsLength);
        _injectionMachineCode = std::vector<BYTE>(_originalInstructionsLength, 0x90);
    }
}
