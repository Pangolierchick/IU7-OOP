#pragma once

#include "loader/scene/base_scene_loader.h"

class FileSceneLoader : public BaseSceneLoader {
public:
    FileSceneLoader();

    ~FileSceneLoader() override = default;

    std::shared_ptr<Object> load(const std::shared_ptr<SceneBuilder>& builder) override;

    void open(std::string& filename) override;

protected:
    std::shared_ptr<std::ifstream> file;

    void load_models(std::shared_ptr<SceneBuilder> builder) override;
    void load_cameras(std::shared_ptr<SceneBuilder> builder) override;
};
