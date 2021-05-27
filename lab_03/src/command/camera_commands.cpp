#include <object/camera/camera.h>

#include <command/camera_commands.h>
#include <managers/scene/scene_manager_creator.h>
#include <managers/transform/transform_manager_creator.h>

AddCamera::AddCamera(const double x, const double y, const double z) : x_pos(x), y_pos(y), z_pos(z) {}

void AddCamera::execute() {
    Point cam_pos(x_pos, y_pos, z_pos);

    std::shared_ptr<Camera> cam(new Camera);
    cam->transform(cam_pos, cam_pos, cam_pos);

    auto _scene_manager = SceneManagerCreator().create_manager();
    _scene_manager->get_scene()->add_camera(cam);
    _scene_manager->set_camera(_scene_manager->get_scene()->get_cameras().size() - 1);
}

RemoveCamera::RemoveCamera(const std::size_t& camera_number) : _camera_number(camera_number) {}

void RemoveCamera::execute() {
    SceneManagerCreator().create_manager()->get_scene()->delete_camera(_camera_number);
}

MoveCamera::MoveCamera(const std::size_t& camera_number, const double& dx, const double& dy) : _camera_number(camera_number), _dx(dx), _dy(dy) {}

void MoveCamera::execute() {
    Point move(_dx, _dy, 0);
    auto camera = SceneManagerCreator().create_manager()->get_scene()->get_cameras().at(_camera_number);
    TransformManagerCreator().create_manager()->transform_object(camera, move, move, move);
}

SetCamera::SetCamera(const std::size_t& camera_number) : _camera_number(camera_number) {}

void SetCamera::execute() {
    SceneManagerCreator().create_manager()->set_camera(_camera_number);
}

CameraCount::CameraCount(std::shared_ptr<size_t>& count) : _count(count) {}

void CameraCount::execute() {
    (*_count) = SceneManagerCreator().create_manager()->get_scene()->get_cameras().size();
}
