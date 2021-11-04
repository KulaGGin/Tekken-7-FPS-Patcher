#include "FPSUnlocker.h"



#include <filesystem>
#include <fstream>
#include <inipp.h>

#include "MemoryCommandoCPP/MemoryCommando/MemoryCommando.h"

namespace FPSPatcher {
    FPSUnlocker::FPSUnlocker() {
        Sleep(10000);
        this->wantedMaximumFPS = GetWantedMaxFPS();
        initializeGameFPSVar();
        initializeTargetFunctionPointers();
        MH_Initialize();
        createHooks();
        enableUnlockedFPSMod();
    }

    FPSUnlocker::~FPSUnlocker() {
        removeUnlockedFPSMod();
        MH_Uninitialize();
    }

    void FPSUnlocker::enableUnlockedFPSMod()
    {
        enableHooks();
    }

    void FPSUnlocker::disableUnlockedFPSMod() {
        disableHooks();
    }

    void FPSUnlocker::removeUnlockedFPSMod() {
        removeHooks();
    }

    void FPSUnlocker::ApplyMod() {
        enableUnlockedFPSMod();
    }

    void FPSUnlocker::CancelMod() {
        removeUnlockedFPSMod();
    }

    void FPSUnlocker::createHooks() {
        MH_CreateHook((LPVOID)targetFightStartLoadingScreenFunctionPointer, &FPSUnlocker::fightStartLoadingScreenFunction_SetCustomMaxFPSLimitDetour, (LPVOID*)&originalFightStartLoadingScreenFunctionPointer);
        MH_CreateHook((LPVOID)targetFightStartFunctionPointer, &FPSUnlocker::fightStartFunction_SetCustomMaxFPSLimitDetour, (LPVOID*)&originalFightStartFunctionPointer);
        MH_CreateHook((LPVOID)targetFightExitFunctionPointer, &FPSUnlocker::fightExitFunction_SetMaxFPSLimit60Detour, (LPVOID*)&originalFightExitFunctionPointer);
        MH_CreateHook((LPVOID)targetFightEndFunctionPointer, &FPSUnlocker::fightEndFunction_SetMaxFPSLimit60Detour, (LPVOID*)&originalFightEndFunctionPointer);
    }

    void FPSUnlocker::enableHooks() {
        MH_EnableHook((LPVOID)targetFightStartLoadingScreenFunctionPointer);
        MH_EnableHook((LPVOID)targetFightStartFunctionPointer);
        MH_EnableHook((LPVOID)targetFightExitFunctionPointer);
        MH_EnableHook((LPVOID)targetFightEndFunctionPointer);
    }

    void FPSUnlocker::disableHooks() {
        MH_DisableHook((LPVOID)targetFightStartLoadingScreenFunctionPointer);
        MH_DisableHook((LPVOID)targetFightStartFunctionPointer);
        MH_DisableHook((LPVOID)targetFightExitFunctionPointer);
        MH_DisableHook((LPVOID)targetFightEndFunctionPointer);
    }

    void FPSUnlocker::removeHooks() {
        disableHooks();

        MH_RemoveHook((LPVOID)targetFightStartLoadingScreenFunctionPointer);
        MH_RemoveHook((LPVOID)targetFightStartFunctionPointer);
        MH_RemoveHook((LPVOID)targetFightExitFunctionPointer);
        MH_RemoveHook((LPVOID)targetFightEndFunctionPointer);
    }

    void FPSUnlocker::initializeGameFPSVar() {
        MemoryCommando::MemoryCommando memoryCommando{};
        auto moduleToScan = memoryCommando.GetModule(0);
        auto scanResults = memoryCommando.ScanVirtualMemory(moduleToScan.szModule, std::string("?? ?? ?? ?? F3 0F 10 00 41 0F 2F C0 77 03 0F 28 C6"));
        int fpsPointerOffset = *reinterpret_cast<int*>(scanResults[0]);
        float** absoluteFPSPointer = reinterpret_cast<float**>(scanResults[0] + fpsPointerOffset + 4);
        currentMaxFPSLimitGameVariable = ObjectProxy<float>({0, reinterpret_cast<uintptr_t>(absoluteFPSPointer), 0});
    }

    void FPSUnlocker::initializeTargetFunctionPointers() {
        MemoryCommando::MemoryCommando memoryCommando{};
        auto moduleToScan = memoryCommando.GetModule(0);

        auto scanResults = memoryCommando.ScanVirtualMemory(moduleToScan.szModule, std::string("40 53 48 83 EC 50 48 8B 05 ?? ?? ?? ?? 48 33 C4 48 89 44 24 40 80 79 62 00 0F B6 DA 0F 84 5D 01 00 00"));
        if(!scanResults.empty())
            targetFightStartLoadingScreenFunctionPointer = reinterpret_cast<FightStartLoadingScreenFunctionPointer_t>(scanResults[0]);

        scanResults = memoryCommando.ScanVirtualMemory(moduleToScan.szModule, std::string("40 53 48 83 EC 30 0F B6 D9 48 8D 4C 24 20 E8 ?? ?? ?? ?? 48 8B 4C 24 20 0F B6 D3"));
        if(!scanResults.empty())
            targetFightStartFunctionPointer = reinterpret_cast<FightStartFunctionPointer_t>(scanResults[0]);

        scanResults = memoryCommando.ScanVirtualMemory(moduleToScan.szModule, std::string("48 89 5C 24 08 48 89 74 24 10 57 48 83 EC 30 48 8B D9 33 C9"));
        if(!scanResults.empty())
            targetFightExitFunctionPointer = reinterpret_cast<FightExitFunctionPointer_t>(scanResults[0]);

        scanResults = memoryCommando.ScanVirtualMemory(moduleToScan.szModule, std::string("48 89 5C 24 08 57 48 83 EC 20 0F B6 D9 E8 ?? ?? ?? ?? 48 8B F8 84 DB 75 04 38 18 74 22"));
        if(!scanResults.empty())
            targetFightEndFunctionPointer = reinterpret_cast<FightEndFunctionPointer_t>(scanResults[0]);
    }

    void FPSUnlocker::setMaxFPSLimit(int fps) const {
        currentMaxFPSLimitGameVariable.Set(static_cast<float>(fps));
    }

    void __fastcall FPSUnlocker::fightStartLoadingScreenFunction_SetCustomMaxFPSLimitDetour(__int64 argument1, char argument2)
    {
        Instance->originalFightStartLoadingScreenFunctionPointer(argument1, argument2);

        Instance->setMaxFPSLimit(Instance->wantedMaximumFPS);
    }

    long long FPSUnlocker::fightStartFunction_SetCustomMaxFPSLimitDetour(unsigned char a1) {
        auto originalReturnValue = Instance->originalFightStartFunctionPointer(a1);

        Instance->setMaxFPSLimit(Instance->wantedMaximumFPS);

        return originalReturnValue;
    }


    char FPSUnlocker::fightEndFunction_SetMaxFPSLimit60Detour(char a1) {
        auto originalReturnValue = Instance->originalFightEndFunctionPointer(a1);

        Instance->setMaxFPSLimit(60);

        return originalReturnValue;
    }

    void __fastcall FPSUnlocker::fightExitFunction_SetMaxFPSLimit60Detour(long long* a1) {
        Instance->originalFightExitFunctionPointer(a1);

        Instance->setMaxFPSLimit(60);
    }

    size_t FPSUnlocker::GetWantedMaxFPS() const {
        inipp::Ini<char>      ini;
        std::filesystem::path iniFilePath = std::filesystem::current_path() / "maxFPS.ini";
        std::ifstream inputFileStream(iniFilePath.string());
        ini.parse(inputFileStream);
        int maxFPS{};
        inipp::extract(ini.sections["maxFPS"]["maxFPS"], maxFPS);

        return static_cast<size_t>(maxFPS);
    }
}
