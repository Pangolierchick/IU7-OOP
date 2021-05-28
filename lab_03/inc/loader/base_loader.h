#pragma once

#include <fstream>
#include <string>

#include "builder/base_builder.h"
#include "error/error.h"
#include "object/object.h"
#include "builder/model/model_builder.h"

class BaseLoader {
public:
    BaseLoader() = default;

    virtual ~BaseLoader() = default;

    virtual void open(std::string &filename) = 0;
    //virtual std::shared_ptr<Object> load(std::shared_ptr<ModelBuilder> builder) = 0;
};

