#include <loader/scene/scene_loader_file.h>
#include <builder/scene/scene_builder.h>
#include <loader/model/model_loader_file.h>
#include <loader/camera/camera_loader_file.h>
#include <error/error.h>

FileSceneLoader::FileSceneLoader() : file(std::make_shared<std::ifstream>()){}

std::shared_ptr<Object> FileSceneLoader::load(const std::shared_ptr<SceneBuilder> &builder) {
    builder->build();
    load_models(builder);
    load_cameras(builder);

    return builder->get();
}

void FileSceneLoader::open(std::string &filename) {
    if (!file) {
        std::string message = "Error while open file.";
        throw FileError(message);
    }
    file->open(filename);

    if (!file) {
        std::string message = "Error while open file.";
        throw FileError(message);
    }
}

void FileSceneLoader::load_models(std::shared_ptr<SceneBuilder> builder) {
    std::size_t models_count;
    *file >> models_count;
    auto model_builder = std::make_shared<ModelBuilder>();

    for (size_t i = 0; i < models_count; ++i)
    {
        builder->build_model(FileModelLoader(file).load(model_builder));
    }
}

void FileSceneLoader::load_cameras(std::shared_ptr<SceneBuilder> builder) {
    std::size_t cameras_count;
    *file >> cameras_count;
    auto camera_builder = std::make_shared<CameraBuilder>();

    for (size_t i = 0; i < cameras_count; ++i)
    {
        auto camera = std::dynamic_pointer_cast<Camera>(FileCameraLoader(file).load(camera_builder));
        builder->build_camera(camera);
    }
}