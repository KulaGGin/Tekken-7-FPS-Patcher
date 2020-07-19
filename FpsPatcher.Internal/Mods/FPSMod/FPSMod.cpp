#include "FPSMod.h"

#include <thread>

namespace FpsPatcher {
    FpsMod::FpsMod(MemoryCommando::MemoryCommando& memoryCommando):
        _memoryCommando(memoryCommando),
        _inGameFPSVariable{ GetInGameMaxFpsVariableAddress(_memoryCommando) },
        _matchStartInjection{ memoryCommando, _inGameFPSVariable },
        _simpleSelectFixInjection{ memoryCommando },
        _matchEndInjection{ memoryCommando, _inGameFPSVariable },
        _matchExitInjection(memoryCommando, _inGameFPSVariable){

    }

    void FpsMod::ApplyMod() {
        _matchStartInjection.Inject();
        _simpleSelectFixInjection.Inject();
        _matchEndInjection.Inject();
        _matchExitInjection.Inject();
    }

    void FpsMod::CancelMod() {
        _matchStartInjection.CancelInjection();
        _simpleSelectFixInjection.CancelInjection();
        _matchEndInjection.CancelInjection();
        _matchExitInjection.CancelInjection();
    }

    uintptr_t FpsMod::GetInGameMaxFpsVariableAddress(MemoryCommando::MemoryCommando& memoryCommando) {
        const uintptr_t fpsBaseClassOffsetAddress = memoryCommando.ScanVirtualMemory(L"TekkenGame-Win64-Shipping.exe",
            std::string(std::string("?? ?? ?? ?? F3 0F 10 00 41 0F 2F C0 77 03 0F 28 C6 0F 28 74 24 40 44 0F 28 44 24 30 44 0F 28 4C 24 20 48 83 C4 50 5B C3")))[0];

        const ptrdiff_t fpsBaseClassOffset = ptrdiff_t(UINT64_MAX << 32 | memoryCommando.ReadVirtualMemory<unsigned>(fpsBaseClassOffsetAddress));

        const uintptr_t fpsPointerAddress = (fpsBaseClassOffsetAddress + 4) + fpsBaseClassOffset;
        uintptr_t fpsAddress;
        do {
            fpsAddress = memoryCommando.ReadVirtualMemory<unsigned int>(fpsPointerAddress);
            std::this_thread::sleep_for(std::chrono::seconds(1));
        } while(!fpsAddress);

        return fpsAddress;
    }
}
