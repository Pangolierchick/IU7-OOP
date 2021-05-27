#define _USE_MATH_DEFINES

#include <cmath>
#include <object/model/details/point/point.h>

Point::Point(const Point&& point) noexcept : _x(point._x), _y(point._y), _z(point._z) {
    point.~Point();
}

Point& Point::operator=(Point&& point) noexcept {
    set_x(point._x);
    set_y(point._y);
    set_z(point._z);
    point.~Point();

    return *this;
}

bool Point::operator==(const Point& point) const noexcept {
    return (point._x == _x) && (point._y == _y) && (point._z == _z);
}

bool Point::is_equal(const Point& point) const noexcept {
    return *this == point;
}

bool Point::operator!=(const Point& point) const noexcept {
    return !(*this == point);
}

bool Point::is_not_equal(const Point& point) const noexcept {
    return !(*this == point);
}

double Point::get_x() const {
    return _x;
}

double Point::get_y() const {
    return _y;
}

double Point::get_z() const {
    return _z;
}

void Point::set_x(const double& x) {
    _x = x;
}

void Point::set_y(const double& y) {
    _y = y;
}

void Point::set_z(const double& z) {
    _z = z;
}

Point Point::operator+(const Point& point) {
    Point p{*this};

    p.set_x(p._x + point._x);
    p.set_y(p._y + point._y);
    p.set_z(p._z + point._z);

    return p;
}

Point Point::sum(const Point& point) {
    Point p{*this};

    p.set_x(p._x + point._x);
    p.set_y(p._y + point._y);
    p.set_z(p._z + point._z);

    return p;
}

Point Point::operator-(const Point& point) {
    Point p{*this};

    p.set_x(p._x - point._x);
    p.set_y(p._y - point._y);
    p.set_z(p._z - point._z);

    return p;
}

Point Point::sub(const Point& point) {
    Point p{*this};

    p.set_x(p._x - point._x);
    p.set_y(p._y - point._y);
    p.set_z(p._z - point._z);

    return p;
}

Point Point::relative_to(const Point& center) {
    return *this + center;
}

void Point::move(const double dx, const double dy, const double dz) {
    set_x(_x + dx);
    set_y(_y + dy);
    set_z(_z + dz);
}

void Point::scale(const double kx, const double ky, const double kz) {
    set_x(_x * kx);
    set_y(_y * ky);
    set_z(_z * kz);
}

void Point::rotate(const double x_o, const double y_o, const double z_o) {
    rotate_x(x_o);
    rotate_y(y_o);
    rotate_z(z_o);
}

inline double to_radians(const double& angle) {
    return angle * (M_PI / 180);
}

void Point::rotate_x(const double& x_o) {
    const double r_cos = cos(to_radians(x_o));
    const double r_sin = sin(to_radians(x_o));
    const double temp = _y;

    set_y(_y * r_cos + _z * r_sin);
    set_z(-temp * r_sin + _z * r_cos);
}

void Point::rotate_y(const double& y_o) {
    const double r_cos = cos(to_radians(y_o));
    const double r_sin = sin(to_radians(y_o));
    const double temp = _x;

    set_x(_x * r_cos + _z * r_sin);
    set_z(-temp * r_sin + _z * r_cos);
}

void Point::rotate_z(const double& z_o) {
    const double r_cos = cos(to_radians(z_o));
    const double r_sin = sin(to_radians(z_o));
    const double temp = _x;

    set_x(_x * r_cos + _y * r_sin);
    set_y(-temp * r_sin + _y * r_cos);
}
