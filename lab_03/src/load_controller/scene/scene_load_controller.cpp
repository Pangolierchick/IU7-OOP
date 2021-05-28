#include "error/error.h"
#include "load_controller/scene/scene_load_controller.h"

std::shared_ptr<Object> SceneLoadController::load(std::string& filename) {
    try {
        _loader->open(filename);
    } catch (SourceError& error) {
        throw SourceError((std::string&)"can't open source");
    }

    std::shared_ptr<Object> scene;
    try {
        scene = _loader->load(_builder);
    } catch (std::exception& error) {
        throw SourceError((std::string&)"can't read model");
    }

    return scene;
}
