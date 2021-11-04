#pragma once
#include <activation.h>
#include <string>
#include <utility>

#include "WinAPIException.h"

class CreateToolhelp32SnapshotException : public WinAPIException {
public:
    CreateToolhelp32SnapshotException(std::string errorMessage, DWORD lastError) : WinAPIException(std::move(errorMessage), lastError) {
    }
    const char* what() const override {
        return _errorMessage.c_str();
    }
    DWORD GetError() const {
        return _lastErrorCode;
    }
};
