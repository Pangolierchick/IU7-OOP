#pragma once

#include <exception>
#include <string>

#include "matrix_exceptions.h"

class nullPointerIteratorExc : public basicMatrixException {
public:
    nullPointerIteratorExc(std::string file, std::string className, int line,
                           time_t time, std::string error_name) : basicMatrixException(file, className, line, time, error_name){};

    const char* what(void) const noexcept { return this->error_msg.c_str(); }
};
