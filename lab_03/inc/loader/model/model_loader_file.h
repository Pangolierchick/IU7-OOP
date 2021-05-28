#pragma once

#include "loader/model/base_model_loader.h"

class FileModelLoader : public BaseModelLoader {
public:
    FileModelLoader() : file(std::make_shared<std::ifstream>()) {};

    explicit FileModelLoader(std::shared_ptr<std::ifstream> &read_file);

    ~FileModelLoader() override = default;

    std::shared_ptr<Object> load(std::shared_ptr<ModelBuilder> builder) override;

    void open(std::string &filename) override;

protected:
    std::shared_ptr<std::ifstream> file;
};
