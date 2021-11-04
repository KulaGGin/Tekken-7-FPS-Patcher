#pragma once
#include "WinAPIException.h"

class VirtualQueryException : public WinAPIException {
public:
    VirtualQueryException(const std::string& errorMessage, DWORD lastError, uintptr_t address) : WinAPIException(errorMessage, lastError),
        Address(address) {
    }

    const uintptr_t Address;
};
