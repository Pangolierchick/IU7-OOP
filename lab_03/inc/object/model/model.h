#pragma once

#include <memory>
#include <utility>

#include "managers/draw/draw_manager.h"
#include "object/model/details/details.h"
#include "object/model/details/edge/edge.h"
#include "object/model/details/point/point.h"
#include "object/object.h"

class Model : public VisibleObject {
    friend void DrawManager::visit(const Model& model);

public:
    Model() : _details(new ModelDetails){};
    explicit Model(const std::shared_ptr<ModelDetails>& details) : _details(details){};
    Model(const Model& model);

    ~Model() override = default;

    void transform(const Point& move, const Point& scale, const Point& rotate) override;
    void accept(std::shared_ptr<Visitor> visitor) override;

protected:
    std::shared_ptr<ModelDetails> _details;
};
