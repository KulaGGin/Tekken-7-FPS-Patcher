// dllmain.cpp : Defines the entry point for the DLL application.
#include "framework.h"
#include <Windows.h>

#include "MemoryCommandoCPP/MemoryCommando/MemoryCommando.h"
#include "Mods/FPSUnlocker/FPSUnlocker.h"

using namespace FPSPatcher;
__declspec(dllexport) DWORD WINAPI FPSPatchInternal(HMODULE hModule) {
    FPSUnlocker::Instance = std::make_shared<FPSUnlocker>();
    ExitThread(0);
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    HANDLE hObject;
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        hObject = CreateThread(nullptr, 0, LPTHREAD_START_ROUTINE(FPSPatchInternal), hModule, 0, nullptr);
        CloseHandle(hObject);
        break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

