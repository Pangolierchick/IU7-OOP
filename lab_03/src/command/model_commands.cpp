#include <command/model_commands.h>
#include <load_controller/model/model_load_controller_creator.h>
#include <managers/load/load_manager_creator.h>
#include <managers/scene/scene_manager_creator.h>
#include <managers/transform/transform_manager_creator.h>
#include <utility>

#define cd const double

MoveModel::MoveModel(cd& dx, cd& dy, cd& dz, const std::size_t& model_number) : _dx(dx), _dy(dy), _dz(dz), _model_number(model_number) {}

void MoveModel::execute() {
    Point move(_dx, _dy, _dz);
    Point scale(1, 1, 1);
    Point rotate(0, 0, 0);

    std::shared_ptr<Object> model = SceneManagerCreator().create_manager()->get_scene()->get_models().at(_model_number);
    TransformManagerCreator().create_manager()->transform_object(model, move, scale, rotate);
}

ScaleModel::ScaleModel(cd& kx, cd& ky, cd& kz, const std::size_t& model_number) : _kx(kx), _ky(ky), _kz(kz), _model_number(model_number) {}

void ScaleModel::execute() {
    Point move(0, 0, 0);
    Point scale(_kx, _ky, _kz);
    Point turn(0, 0, 0);

    std::shared_ptr<Object> model = SceneManagerCreator().create_manager()->get_scene()->get_models().at(_model_number);
    TransformManagerCreator().create_manager()->transform_object(model, move, scale, turn);
}

RotateModel::RotateModel(cd& ox, cd& oy, cd& oz, const std::size_t& model_number) : _ox(ox), _oy(oy), _oz(oz), _model_number(model_number) {}

void RotateModel::execute() {
    Point move(0, 0, 0);
    Point scale(1, 1, 1);
    Point rotate(_ox, _oy, _oz);

    std::shared_ptr<Object> model = SceneManagerCreator().create_manager()->get_scene()->get_models().at(_model_number);
    TransformManagerCreator().create_manager()->transform_object(model, move, scale, rotate);
}

ReformModel::ReformModel(const std::size_t& model_number, const Point& move, const Point& scale, const Point& rotate) : _model_number(model_number), move(move), scale(scale), rotate(rotate) {}

void ReformModel::execute() {
    std::shared_ptr<Object> model = SceneManagerCreator().create_manager()->get_scene()->get_models().at(_model_number);
    TransformManagerCreator().create_manager()->transform_object(model, move, scale, rotate);
}

LoadModel::LoadModel(std::string filename) : _filename(std::move(filename)) {}

void LoadModel::execute() {
    auto controller = ModelLoadControllerCreator().create_controller();
    auto manager = LoadManagerCreator().create_manager(controller);

    auto model = manager->load(_filename);
    SceneManagerCreator().create_manager()->get_scene()->add_model(model);
}

ExportModel::ExportModel(std::string filename) {
}

void ExportModel::execute() {
}

AddModel::AddModel(std::shared_ptr<Object> model) : _model(std::move(model)) {}

void AddModel::execute() {
    SceneManagerCreator().create_manager()->get_scene()->add_model(_model);
}

RemoveModel::RemoveModel(const std::size_t& model_number) : _model_number(model_number) {}

void RemoveModel::execute() {
    SceneManagerCreator().create_manager()->get_scene()->delete_model(_model_number);
}

ModelCount::ModelCount(std::shared_ptr<size_t>& count) : _count(count) {}

void ModelCount::execute() {
    (*_count) = SceneManagerCreator().create_manager()->get_scene()->get_models().size();
}
