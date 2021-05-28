#pragma once

#include "loader/camera/base_camera_loader.h"

class FileCameraLoader : public BaseCameraLoader {
public:
    FileCameraLoader() : file(std::make_shared<std::ifstream>()) {};
    explicit FileCameraLoader(std::shared_ptr<std::ifstream> &read_file);

    ~FileCameraLoader() override = default;

    std::shared_ptr<Object> load(const std::shared_ptr<CameraBuilder> &builder) override;

    void open(std::string &filename) override;

protected:
    std::shared_ptr<std::ifstream> file;
};


