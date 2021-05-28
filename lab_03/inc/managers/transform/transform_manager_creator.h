#pragma once

#include <memory>
#include "transform_manager.h"

class TransformManagerCreator {
public:
    std::shared_ptr<TransformManager> create_manager();

private:
    void create_instance();
    std::shared_ptr<TransformManager> _manager;
};
