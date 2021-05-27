#include <object/model/model.h>

#include <memory>

Model::Model(const Model &model) {
    _details = model._details;
}

void Model::transform(const Point &move, const Point &scale, const Point &rotate) {
    _details->transform(move, scale, rotate);
}

void Model::accept(std::shared_ptr<Visitor> visitor) {
    visitor->visit(*this);
}
