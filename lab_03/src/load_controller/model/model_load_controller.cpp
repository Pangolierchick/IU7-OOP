#include <load_controller/model/model_load_controller.h>
#include <error/error.h>

std::shared_ptr<Object> ModelLoadController::load(std::string &filename) {
    try {
        _loader->open(filename);
    } catch (SourceError &error) {
        throw SourceError((std::string &) "can't open source");
    }

    std::shared_ptr<Object> model;

    try {
        model = _loader->load(_builder);
    } catch (std::exception &error) {
        throw SourceError((std::string &) "can't read model");
    }

    return model;
}
