#pragma once

#include "object/object.h"

class BaseBuilder {
public:
    BaseBuilder() = default;

    ~BaseBuilder() = default;

    virtual bool is_built() const = 0;
    virtual void build() = 0;

    virtual std::shared_ptr<Object> get() = 0;
};


