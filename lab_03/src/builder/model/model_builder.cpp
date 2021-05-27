#include "builder/model/model_builder.h"

bool ModelBuilder::is_built() const {
    return model_pointer != nullptr;
}

void ModelBuilder::build() {
    model_pointer = std::make_shared<ModelDetails>();
}

void ModelBuilder::build_point(const double &x, const double &y, const double &z) {
    Point point_object(x, y, z);
    model_pointer->add_point(point_object);
}

void ModelBuilder::build_edge(const size_t &point1, const size_t &point2) {
    Edge edge_object(point1, point2);
    model_pointer->add_edge(edge_object);
}

std::shared_ptr<Object> ModelBuilder::get() {
    return std::make_shared<Model>(Model(model_pointer));
}
