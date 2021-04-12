#pragma once

#include <exception>
#include <string>

class basicMatrixException : public std::exception
{
public:
    basicMatrixException(std::string file, std::string className, int line, time_t time, std::string error_name)
    {
        error_msg = "File name: " + file + " in line " + std::to_string(line) + "\nTime: " + ctime(&time) + "Info: " + msg + "\n";
    }

    virtual const char *what(void) const noexcept override { return this->error_msg.c_str(); }

protected:
    std::string error_msg;
};

class indexException : public basicMatrixException
{
    indexException(std::string file, std::string className, int line, time_t time, std::string error_name) : basicMatrixException(file, className, line, time, error_name){};

    const char *what(void) const noexcept { return this->error_msg.c_str(); }
};

//TODO is not equal

class isEmptyException : public basicMatrixException {
    public:

    isEmptyException(std::string file, std::string className, int line, time_t time, std::string error_name) : basicMatrixException(file, className, line, time, error_name){};

    const char *what(void) const noexcept { return this->error_msg.c_str(); }
};

class MultMatrixException : public basicMatrixException {
    public:

    MultMatrixException(std::string file, std::string className, int line, time_t time, std::string error_name) : basicMatrixException(file, className, line, time, error_name){};

    const char *what(void) const noexcept { return this->error_msg.c_str(); }
};
