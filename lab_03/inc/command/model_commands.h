#pragma once

#include <cstddef>
#include <memory>

#include "command/base_command.h"
#include "object/object.h"


class ModelBaseCommand : public BaseCommand {};

class MoveModel : public ModelBaseCommand {
public:
    MoveModel() = delete;
    MoveModel(const double &dx, const double &dy, const double &dz, const std::size_t& model_number);
    ~MoveModel() override = default;

    void execute() override;

private:
    std::size_t _model_number;

    double _dx, _dy, _dz;
};

class ScaleModel : public ModelBaseCommand {
public:
    ScaleModel() = delete;
    ScaleModel(const double &kx, const double &ky, const double &kz, const std::size_t& model_number);
    ~ScaleModel() override = default;

    void execute() override;

private:
    std::size_t _model_number;

    double _kx, _ky, _kz;
};

class RotateModel : public ModelBaseCommand {
public:
    RotateModel() = delete;
    RotateModel(const double &ox, const double &oy, const double &oz, const std::size_t& model_number);
    ~RotateModel() override = default;

    void execute() override;

private:
    std::size_t _model_number;

    double _ox, _oy, _oz;
};

class ReformModel : public ModelBaseCommand {
public:
    ReformModel() = delete;
    ReformModel(const std::size_t &number, const Point &move, const Point &scale, const Point &rotate);
    ~ReformModel() override = default;

    void execute() override;

private:
    std::size_t _model_number;

    Point move, scale, rotate;
};

class LoadModel : public ModelBaseCommand {
public:
    LoadModel() = delete;
    explicit LoadModel(std::string filename);
    ~LoadModel() override = default;

    void execute() override;

private:
    std::string _filename;
};

class ExportModel : public ModelBaseCommand {
public:
    ExportModel() = delete;
    explicit ExportModel(std::string filename);
    ~ExportModel() override = default;

    void execute() override;

private:
    std::string _filename;
};

class AddModel : public ModelBaseCommand {
public:
    AddModel() = delete;
    explicit AddModel(std::shared_ptr<Object> model);
    ~AddModel() override = default;

    void execute() override;

private:
    std::shared_ptr<Object> _model;
};

class RemoveModel : public ModelBaseCommand {
public:
    RemoveModel() = delete;
    explicit RemoveModel(const std::size_t& model_number);
    ~RemoveModel() override = default;

    void execute() override;

private:
    std::size_t _model_number;
};

class ModelCount : public ModelBaseCommand {
public:
    ModelCount() = delete;
    explicit ModelCount(std::shared_ptr<size_t>& count);
    ~ModelCount() override = default;

    void execute() override;

private:
    std::shared_ptr<size_t>& _count;
};
