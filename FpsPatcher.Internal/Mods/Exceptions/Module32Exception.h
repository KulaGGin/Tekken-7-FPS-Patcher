#pragma once
#include "WinAPIException.h"


class Module32Exception : public WinAPIException {
public:
    Module32Exception(const std::string& errorMessage, DWORD lastError) : WinAPIException(errorMessage, lastError) {
    }
};
