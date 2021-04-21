#pragma once

#include <exception>
#include <string>

class basicMatrixException : public std::exception {
public:
    basicMatrixException(std::string file, std::string className, int line,
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

class indexException : public basicMatrixException {
public:
    indexException(std::string file, std::string className, int line,
                   time_t time, std::string error_name)
        : basicMatrixException(file, className, line, time, error_name){};

    const char* what(void) const noexcept { return this->error_msg.c_str(); }
};

class NullPtrException : public basicMatrixException {
public:
    NullPtrException(std::string file, std::string className, int line,
                     time_t time, std::string error_name)
        : basicMatrixException(file, className, line, time, error_name){};

    const char* what(void) const noexcept { return this->error_msg.c_str(); }
};

class MultMatrixException : public basicMatrixException {
public:
    MultMatrixException(std::string file, std::string className, int line,
                        time_t time, std::string error_name)
        : basicMatrixException(file, className, line, time, error_name){};

    const char* what(void) const noexcept { return this->error_msg.c_str(); }
};

class MatrixDetException : public basicMatrixException {
public:
    MatrixDetException(std::string file, std::string className, int line,
                       time_t time, std::string error_name)
        : basicMatrixException(file, className, line, time, error_name){};

    const char* what(void) const noexcept { return this->error_msg.c_str(); }
};

class badAllocException : public basicMatrixException {
public:
    badAllocException(std::string file, std::string className, int line,
                      time_t time, std::string error_name)
        : basicMatrixException(file, className, line, time, error_name){};

    const char* what(void) const noexcept { return this->error_msg.c_str(); }
};
