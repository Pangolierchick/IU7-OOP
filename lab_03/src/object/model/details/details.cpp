#include "object/model/details/details.h"

void ModelDetails::add_point(const Point& point) {
    _points.push_back(point);
}

void ModelDetails::add_edge(const Edge& edge) {
    _edges.push_back(edge);
}

const Point& ModelDetails::get_center() const {
    return _center;
}

const std::vector<Point>& ModelDetails::get_points() const {
    return _points;
}

const std::vector<Edge>& ModelDetails::get_edges() const {
    return _edges;
}

void ModelDetails::transform(const Point& move, const Point& scale, const Point& rotate) {
    _center.move(move.get_x(), move.get_y(), move.get_z());

    for (auto& point : _points) {
        point.scale(scale.get_x(), scale.get_y(), scale.get_z());
        point.rotate(rotate.get_x(), rotate.get_y(), rotate.get_z());
    }
}
