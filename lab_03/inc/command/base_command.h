#pragma once

#include <string>

class BaseCommand {
public:
    BaseCommand() = default;
    virtual ~BaseCommand() = default;
    virtual void execute() = 0;
};

