#include <managers/scene/scene_manager.h>

#include <memory>
#include <utility>

SceneManager::SceneManager() {
    _scene = std::make_shared<Scene>();
}

std::shared_ptr<Scene> SceneManager::get_scene() const {
    return _scene;
}

std::shared_ptr<Camera> SceneManager::get_camera() const {
    return current_camera;
}

void SceneManager::set_scene(std::shared_ptr<Scene> scene) {
    _scene = std::move(scene);
}

void SceneManager::set_camera(const size_t &camera_number) {
    auto camera = _scene->get_cameras().at(camera_number);
    current_camera = camera;
}
