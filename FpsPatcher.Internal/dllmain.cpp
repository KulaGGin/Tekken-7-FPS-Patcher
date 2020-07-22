// dllmain.cpp : Defines the entry point for the DLL application.
#include "framework.h"
#include <Windows.h>
#include <TlHelp32.h>
#include "MemoryCommandoCPP/MemoryCommando/MemoryCommando.h"
#include "Mods/FPSMod/FPSMod.h"

__declspec(dllexport) DWORD WINAPI FpsPatchInternal(HMODULE hModule) {
    MemoryCommando::MemoryCommando memoryCommando;
    FpsPatcher::FpsMod fpsMod(memoryCommando);
    fpsMod.ApplyMod();

    FreeLibraryAndExitThread(hModule, 0);
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        CloseHandle(CreateThread(nullptr, 0, LPTHREAD_START_ROUTINE(FpsPatchInternal), hModule, 0, nullptr));
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

