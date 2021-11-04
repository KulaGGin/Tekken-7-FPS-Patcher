#pragma once
#include <exception>
#include <string>

class BaseException : public std::exception {
public:
    BaseException(std::string errorMessage) : _errorMessage(std::move(errorMessage)) {
    }
    std::string GetErrorMessage() const {
        return _errorMessage;
    }
protected:
    std::string _errorMessage;
};

