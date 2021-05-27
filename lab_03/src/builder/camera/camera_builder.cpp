#include <builder/camera/camera_builder.h>

bool CameraBuilder::is_built() const {
    return camera_pointer != nullptr;
}

void CameraBuilder::build() {
    camera_pointer = std::make_shared<Camera>();
}

void CameraBuilder::build_position(double x, double y, double z) {
}

std::shared_ptr<Object> CameraBuilder::get() {
    return camera_pointer;
}
