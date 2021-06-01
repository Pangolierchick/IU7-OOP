#pragma once

#include "managers/base_manager.h"
#include "scene/scene.h"

class SceneManager : public BaseManager {
public:
    SceneManager();
    SceneManager(const SceneManager&) = delete;
    SceneManager& operator=(const SceneManager&) = delete;

    ~SceneManager() = default;

    std::shared_ptr<Scene> get_scene() const;
    std::shared_ptr<Camera> get_camera() const;

    void set_scene(std::shared_ptr<Scene> scene);
    void set_camera(const std::size_t& camera_number);

private:
    std::shared_ptr<Scene> _scene;
    std::shared_ptr<Camera> current_camera;
};
