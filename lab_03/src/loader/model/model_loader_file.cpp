#include "builder/model/model_builder.h"
#include "error/error.h"
#include "loader/model/model_loader_file.h"

FileModelLoader::FileModelLoader(std::shared_ptr<std::ifstream>& read_file) {
    file = read_file;
}

std::shared_ptr<Object> FileModelLoader::load(std::shared_ptr<ModelBuilder> builder) {
    builder->build();

    std::size_t points_count;
    *file >> points_count;
    double x, y, z;

    for (std::size_t i = 0; i < points_count; i++) {
        *file >> x >> y >> z;
        builder->build_point(x, y, z);
    }

    std::size_t edges_count;
    *file >> edges_count;
    std::size_t point_1, point_2;

    for (std::size_t i = 0; i < edges_count; i++) {
        *file >> point_1 >> point_2;
        builder->build_edge(point_1, point_2);
    }

    return builder->get();
}

void FileModelLoader::open(std::string& filename) {
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
