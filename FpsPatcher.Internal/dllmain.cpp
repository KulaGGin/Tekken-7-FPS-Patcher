// dllmain.cpp : Defines the entry point for the DLL application.
#include "framework.h"
#include <Windows.h>
#include <TlHelp32.h>
#include "MemoryCommandoCPP/MemoryCommando/MemoryCommando.h"
#include "Mods/FPSMod/FPSMod.h"

__declspec(dllexport) DWORD WINAPI FPSPatchInternal(HMODULE hModule) {
    MemoryCommando::MemoryCommando memoryCommando;
    FPSPatcher::FPSMod fpsMod(memoryCommando, hModule);
    fpsMod.ApplyMod();

    FreeLibraryAndExitThread(hModule, 0);
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

