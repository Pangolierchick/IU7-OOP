#include <iterator>
#include "scene/scene.h"
#include <object/composite/composite.h>

void Scene::add_model(const std::shared_ptr<Object> &model) {
    models->add(model);
}

void Scene::delete_model(const std::size_t index) {
    auto iter = models->begin();

    std::advance(iter, index);
    models->remove(iter);
}

void Scene::add_camera(const std::shared_ptr<Camera> &camera) {
    cameras.push_back(camera);
}

void Scene::delete_camera(const std::size_t index) {
    auto iter = cameras.begin();

    std::advance(iter, index);
    cameras.erase(iter);
}

std::vector<std::shared_ptr<Object>> Scene::get_models() {
    return models->objects;
}

std::shared_ptr<Composite> Scene::get_composite() {
    return models;
}

std::vector<std::shared_ptr<Camera>> Scene::get_cameras() {
    return cameras;
}

Scene::Scene() : models(new Composite) {}
