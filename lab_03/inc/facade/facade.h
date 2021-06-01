#pragma once

#include <memory>

#include "command/base_command.h"

class Facade {
public:
    void execute(BaseCommand& command);
};
