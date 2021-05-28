#pragma once

#include <vector>
#include "object/object.h"

class Scene : public Object {
public:
    Scene();

    ~Scene() override = default;

    void add_model(const std::shared_ptr<Object>& model);
    void delete_model(const std::size_t index);

    void add_camera(const std::shared_ptr<Camera>& camera);
    void delete_camera(const std::size_t index);

    std::vector<std::shared_ptr<Object>> get_models();
    std::shared_ptr<Composite> get_composite();
    std::vector<std::shared_ptr<Camera>> get_cameras();

protected:
    std::shared_ptr<Composite> models;
    std::vector<std::shared_ptr<Camera>> cameras;

private:
    void accept(std::shared_ptr<Visitor> visitor) override {};
    void transform(const Point& move, const Point& scale, const Point& rotate) override {};
};

