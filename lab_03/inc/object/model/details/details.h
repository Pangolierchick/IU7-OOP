#pragma once

#include "model/details/edge/edge.h"
#include "model/details/point/point.h"
#include <vector>

class ModelDetails {
public:
    ModelDetails() = default;
    ModelDetails(std::vector<Point>& points, std::vector<Edge>& edges) : _center{}, _points(points), _edges(edges){};
    ModelDetails(Point& center, std::vector<Point>& points, std::vector<Edge>& edges) : _center(center), _points(points), _edges(edges){};

    ~ModelDetails() = default;

    void add_point(const Point& point);
    void add_edge(const Edge& edge);
    void transform(const Point& move, const Point& scale, const Point& rotate);

    const Point& get_center() const;
    const std::vector<Point>& get_points() const;
    const std::vector<Edge>& get_edges() const;

private:
    Point _center;

    std::vector<Point> _points;
    std::vector<Edge> _edges;
};
