#include "FPSMod.h"

#include <windows.h>
#include <fstream>
#include "inipp.h"
#include <thread>
#include <winuser.h>

namespace FPSPatcher {
    FPSMod::FPSMod(MemoryCommando::MemoryCommando& memoryCommando, HMODULE moduleHandle):
        _memoryCommando(memoryCommando),
        _moduleHandle(moduleHandle),
        _inGameFPSVariable{ GetInGameMaxFPSVariableAddress(_memoryCommando) },
        _maxFPS(InitializeMaxFPS()),
        _matchStartInjection{ memoryCommando, _inGameFPSVariable, _maxFPS },
        _simpleSelectFixInjection{ memoryCommando },
        _matchEndInjection{ memoryCommando, _inGameFPSVariable },
        _matchExitInjection(memoryCommando, _inGameFPSVariable) {

    }

    void FPSMod::ApplyMod() {
        _matchStartInjection.Inject();
        _simpleSelectFixInjection.Inject();
        _matchEndInjection.Inject();
        _matchExitInjection.Inject();
    }

    void FPSMod::CancelMod() {
        _matchStartInjection.CancelInjection();
        _simpleSelectFixInjection.CancelInjection();
        _matchEndInjection.CancelInjection();
        _matchExitInjection.CancelInjection();
    }


    uintptr_t FPSMod::GetInGameMaxFPSVariableAddress(MemoryCommando::MemoryCommando& memoryCommando) const {
        // todo "Show message box if it can't find the fpsVariableAddress, then close the library without crashing the game".
        const std::vector<uintptr_t> scanResults = memoryCommando.ScanVirtualMemory(L"TekkenGame-Win64-Shipping.exe",
            std::string(std::string("?? ?? ?? ?? F3 0F 10 00 41 0F 2F C0 77 03 0F 28 C6 0F 28 74 24 40 44 0F 28 44 24 30 44 0F 28 4C 24 20 48 83 C4 50 5B C3")));

        if(scanResults.empty()) {
            MessageBox(nullptr, L"Couldn't find a pattern of the fpsBaseClassOffsetAddress. Freeing dll and exiting...", nullptr, MB_OK);
            FreeLibraryAndExitThread(_moduleHandle, 1);
        }

        const uintptr_t fpsBaseClassOffsetAddress = scanResults[0];

        const ptrdiff_t fpsBaseClassOffset = ptrdiff_t(UINT64_MAX << 32 | memoryCommando.ReadVirtualMemory<unsigned>(fpsBaseClassOffsetAddress));

        const uintptr_t fpsPointerAddress = (fpsBaseClassOffsetAddress + 4) + fpsBaseClassOffset;
        uintptr_t fpsAddress;
        do {
            fpsAddress = memoryCommando.ReadVirtualMemory<unsigned int>(fpsPointerAddress);
            std::this_thread::sleep_for(std::chrono::seconds(1));
        } while(!fpsAddress);

        return fpsAddress;
    }

    size_t FPSMod::InitializeMaxFPS() const {
        inipp::Ini<char> ini;
        std::ifstream is("maxFPS.ini");
        ini.parse(is);
        int maxFPS{};
        inipp::extract(ini.sections["maxFPS"]["maxFPS"], maxFPS);

        return size_t(maxFPS);
    }

    void __declspec(naked) SetFPS(float fps, uintptr_t fpsAddress) {
        __asm {
            //push rax
            //pop rax
        }
    }
}
