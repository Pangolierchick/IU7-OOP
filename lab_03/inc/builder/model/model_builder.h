#pragma once

#include "base_builder.h"
#include "model/details/details.h"
#include "model/model.h"

class ModelBuilder : public BaseBuilder {
public:
    ModelBuilder() = default;

    ~ModelBuilder() = default;

    bool is_built() const override;

    void build() override;
    void build_point(const double& x, const double& y, const double& z);
    void build_edge(const std::size_t& point1, const std::size_t& point2);

    std::shared_ptr<Object> get() override;

private:
    std::shared_ptr<ModelDetails> model_pointer;
};
