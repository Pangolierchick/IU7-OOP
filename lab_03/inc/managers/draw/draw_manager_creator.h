#pragma once

#include "draw_manager.h"
#include <memory>

class DrawManagerCreator {
public:
    std::shared_ptr<DrawManager> create_manager();

private:
    void create_instance();
    std::shared_ptr<DrawManager> _manager;
};
