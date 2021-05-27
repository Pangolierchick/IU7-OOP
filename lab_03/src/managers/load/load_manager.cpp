#include <utility>

#include <managers/load/load_manager.h>
#include <load_controller/scene/scene_load_controller_creator.h>
#include <loader/model/model_loader_file.h>
#include <load_controller/model/model_load_controller.h>

LoadManager::LoadManager() {
    _loader = SceneLoadControllerCreator().create_controller();
}

std::shared_ptr<Object> LoadManager::load(std::string &name) {
    return _loader->load(name);
}

void LoadManager::set_loader(std::shared_ptr<AbstractLoadController> loader) {
    _loader = std::move(loader);
}
