#pragma once

#include <utility>

#include "builder/model/model_builder.h"
#include "load_controller/abstract_load_controller.h"
#include "loader/base_loader.h"
#include "loader/model/base_model_loader.h"

class ModelLoadController : public AbstractLoadController {
public:
    explicit ModelLoadController(std::shared_ptr<BaseModelLoader> _loader) : _builder(new ModelBuilder), _loader(std::move(_loader)){};
    ~ModelLoadController() = default;

    std::shared_ptr<Object> load(std::string& filename) override;

private:
    std::shared_ptr<ModelBuilder> _builder;
    std::shared_ptr<BaseModelLoader> _loader;
};
