#pragma once
#include <exception>
#include <string>

class IllegalMoveException : public std::exception {
private:
    std::string m_message;

public:
    IllegalMoveException(const std::string& message = "Illegal chess move") : m_message(message) {}
    
    virtual const char* what() const noexcept override {
        return m_message.c_str();
    }
};

class CheckmateException : public std::exception {
private:
    std::string m_message;

public:
    CheckmateException(const std::string& message = "Move would result in checkmate") : m_message(message) {}
    
    virtual const char* what() const noexcept override {
        return m_message.c_str();
    }
}; 