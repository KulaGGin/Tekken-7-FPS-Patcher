#pragma once
#include <activation.h>

#include "BaseException.h"


class WinAPIException : public BaseException {
public:
    WinAPIException(std::string errorMessage, DWORD lastError) : BaseException(std::move(errorMessage)), _lastErrorCode(lastError) {
    }
    DWORD GetErrorCode() {
        return _lastErrorCode;
    }
protected:
    DWORD _lastErrorCode;
};
