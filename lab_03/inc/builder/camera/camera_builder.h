#pragma once

#include "base_builder.h"
#include "camera/camera.h"

class CameraBuilder : public BaseBuilder {
public:
    CameraBuilder() = default;

    ~CameraBuilder() = default;

    bool is_built() const override;
    void build() override;
    void build_position(double x, double y, double z);

    std::shared_ptr<Object> get() override;

private:
    std::shared_ptr<Camera> camera_pointer;
};
