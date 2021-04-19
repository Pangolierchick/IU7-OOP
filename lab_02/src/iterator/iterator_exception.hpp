#pragma once

#include <exception>
#include <string>

class baseIteratorException : public std::exception {
    public:

    baseIteratorException(std::string file, std::string className, int line,
                         time_t time, std::string error_name) {
                             error_msg = " File name: " + file + " in class: " + className +
                                         " in line " + std::to_string(line) +
                                         "\nTime: " + ctime(&time) + "Info: " + error_name + "\n";
                         }

    virtual const char* what(void) const noexcept override {
        return this->error_msg.c_str();
    }

  protected:
    std::string error_msg;
};

class nullPointerIteratorExc : public baseIteratorException {
    public:

        nullPointerIteratorExc(std::string file, std::string className, int line,
                         time_t time, std::string error_name) : baseIteratorException(file, className, line, time, error_name) {};
    
    const char* what(void) const noexcept { return this->error_msg.c_str(); }
};
