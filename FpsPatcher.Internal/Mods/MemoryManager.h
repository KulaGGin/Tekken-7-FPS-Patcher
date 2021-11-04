#pragma once

#include <activation.h>
#include <TlHelp32.h>
#include <vector>
#include <wil/resource.h>

#include "Mods/Exceptions/CreateToolhelp32SnapshotException.h"
#include "Mods/Exceptions/Module32Exception.h"

class MemoryManager {
public:
    std::vector<MODULEENTRY32W> GetModules() const {
        DWORD _processId = GetCurrentProcessId();

        std::vector<MODULEENTRY32W> modules{};
        MODULEENTRY32W moduleInst{};
        moduleInst.dwSize = sizeof moduleInst;

        const auto modulesSnapshot = wil::unique_tool_help_snapshot(CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, _processId));

        if(!modulesSnapshot)
            throw CreateToolhelp32SnapshotException("CreateToolhelp32Snapshot failed to create a snapshot of modules.", GetLastError());

        bool copiedToBuffer = Module32FirstW(modulesSnapshot.get(), &moduleInst);
        if(!copiedToBuffer)
            throw Module32Exception("Module32First failed to fill the buffer.", GetLastError());

        do {
            modules.push_back(moduleInst);
            copiedToBuffer = Module32NextW(modulesSnapshot.get(), &moduleInst);
        } while(copiedToBuffer);

        if(GetLastError() != ERROR_NO_MORE_FILES)
            throw Module32Exception("Module32Next failed to fill the buffer.", GetLastError());

        return modules;
    }

    static uintptr_t GetAddress(std::vector<uintptr_t> multiLevelPointer) {
        if(multiLevelPointer.empty())
            return 0;

        if(multiLevelPointer.size() == 1)
            return multiLevelPointer[0];

        if(multiLevelPointer.size() == 2)
            return multiLevelPointer[0] + multiLevelPointer[1];

        uintptr_t baseAddress = multiLevelPointer[0];
        uintptr_t address;
        for(size_t currentOffsetIndex = 1; currentOffsetIndex < multiLevelPointer.size() - 1; ++currentOffsetIndex) {
            address = baseAddress + multiLevelPointer[currentOffsetIndex];

            if(IsBadReadPtr(reinterpret_cast<void*>(address), sizeof uintptr_t))
                return 0;

            baseAddress = *reinterpret_cast<uintptr_t*>(address);
        }

        address = baseAddress + multiLevelPointer.back();

        if(IsBadReadPtr(reinterpret_cast<void*>(address), sizeof uintptr_t))
            return 0;

        return address;
    }
};
