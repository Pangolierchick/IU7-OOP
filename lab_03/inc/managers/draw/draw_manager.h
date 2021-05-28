#pragma once

#include <memory>

#include "visitor.h"
#include "managers/base_manager.h"
#include "drawer/abstract_drawer.h"
#include "object/composite/composite.h"
#include "object/object.h"
#include "object/model/details/point/point.h"

class Camera;

class DrawManager : public Visitor, public BaseManager {
public:
    DrawManager() = default;
    DrawManager(const DrawManager&) = delete;

    DrawManager& operator = (const DrawManager&) = delete;

    ~DrawManager() = default;

    void visit(const Camera& camera) override;
    void visit(const Model& model) override;
    void visit(const Composite& composite) override;

    void set_drawer(std::shared_ptr<AbstractDrawer>);
    void set_camera(std::shared_ptr<Camera>);

    Point point_proection(const Point& point);

private:
    std::shared_ptr<AbstractDrawer> _drawer;
    std::shared_ptr<Camera> _camera;
};

