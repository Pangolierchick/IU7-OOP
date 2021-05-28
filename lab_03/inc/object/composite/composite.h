#pragma once

#include "object/object.h"
#include "scene/scene.h"
#include "visitor.h"

class Composite : public Object {
    friend std::vector<std::shared_ptr<Object>> Scene::get_models();

public:
    Composite() = default;
    explicit Composite(std::shared_ptr<Object>& component);
    explicit Composite(const std::vector<std::shared_ptr<Object>>& vector);

    bool add(const std::shared_ptr<Object>& component) override;
    bool remove(const Iterator& iter) override;

    Iterator begin() override;
    Iterator end() override;

    bool is_visible() override;
    bool is_composite() const override;
    void transform(const Point& move, const Point& scale, const Point& rotate) override;
    void accept(std::shared_ptr<Visitor> visitor) override;

protected:
    std::vector<std::shared_ptr<Object>> objects;
};
