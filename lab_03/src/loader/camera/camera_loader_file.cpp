#include <error/error.h>
#include <loader/camera/camera_loader_file.h>

FileCameraLoader::FileCameraLoader(std::shared_ptr<std::ifstream>& read_file) {
    file = read_file;
}

std::shared_ptr<Object> FileCameraLoader::load(const std::shared_ptr<CameraBuilder>& builder) {
    double x, y, z;

    builder->build();
    *file >> x >> y >> z;

    builder->build_position(x, y, z);

    return builder->get();
}

void FileCameraLoader::open(std::string& filename) {
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