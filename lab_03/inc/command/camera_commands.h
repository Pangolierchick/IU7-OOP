#pragma once

#include <cstddef>
#include <memory>

#include "command/base_command.h"

class CameraBaseCommand : public BaseCommand {};

class AddCamera : public CameraBaseCommand {
public:
    AddCamera() = delete;
    AddCamera(const double x, const double y, const double z);
    ~AddCamera() override = default;

    void execute() override;

private:
    double x_pos, y_pos, z_pos;
};

class RemoveCamera : public CameraBaseCommand {
public:
    RemoveCamera() = delete;
    explicit RemoveCamera(const std::size_t& camera_number);
    ~RemoveCamera() override = default;

    void execute() override;

private:
    std::size_t _camera_number;
};

class MoveCamera : public CameraBaseCommand {
public:
    MoveCamera() = delete;
    MoveCamera(const std::size_t& camera_number, const double& dx, const double& dy);
    ~MoveCamera() override = default;

    void execute() override;

private:
    std::size_t _camera_number;

    double _dx, _dy;
};

class SetCamera : public CameraBaseCommand {
public:
    SetCamera() = delete;
    explicit SetCamera(const std::size_t& camera_number);
    ~SetCamera() override = default;

    void execute() override;

private:
    std::size_t _camera_number;
};

class CameraCount : public CameraBaseCommand {
public:
    CameraCount() = delete;
    explicit CameraCount(std::shared_ptr<size_t>& count);
    ~CameraCount() override = default;

    void execute() override;

private:
    std::shared_ptr<size_t>& _count;
};
