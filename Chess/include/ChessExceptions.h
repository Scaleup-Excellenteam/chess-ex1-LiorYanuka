#pragma once
#include <exception>
#include <string>

class IllegalMoveException : public std::exception {
private:
    std::string _message;

public:
    IllegalMoveException(const std::string &message = "Illegal chess move") : _message(message) {
    }

    virtual const char *what() const noexcept override {
        return _message.c_str();
    }
};

class CheckmateException : public std::exception {
private:
    std::string _message;

public:
    CheckmateException(const std::string &message = "Move would result in checkmate") : _message(message) {
    }

    virtual const char *what() const noexcept override {
        return _message.c_str();
    }
};
