#include "load_controller/abstract_load_controller.h"

void AbstractLoadController::set_loader(std::shared_ptr<BaseLoader> loader) {
    _loader = std::move(loader);
}
