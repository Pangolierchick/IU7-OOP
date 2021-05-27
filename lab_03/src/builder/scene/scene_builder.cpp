#include "builder/scene/scene_builder.h"

bool SceneBuilder::is_built() const {
    return scene_pointer != nullptr;
}

void SceneBuilder::build() {
    scene_pointer = std::make_shared<Scene>();
}

void SceneBuilder::build_model(const std::shared_ptr<Object>& object) {
    scene_pointer->add_model(object);
}

void SceneBuilder::build_camera(const std::shared_ptr<Camera>& camera) {
    scene_pointer->add_camera(camera);
}

std::shared_ptr<Object> SceneBuilder::get() {
    return scene_pointer;
}
