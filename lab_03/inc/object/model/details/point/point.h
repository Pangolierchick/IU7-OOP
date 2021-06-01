#pragma once

class Point {
public:
    Point() = default;
    Point(const double x, const double y, const double z) : _x(x), _y(y), _z(z){};

    ~Point() = default;

    Point(const Point& point) = default;
    Point& operator=(const Point& point) = default;

    Point(const Point&& point) noexcept;
    Point& operator=(Point&& point) noexcept;

    bool operator==(const Point& point) const noexcept;
    bool is_equal(const Point& point) const noexcept;
    bool operator!=(const Point& point) const noexcept;
    bool is_not_equal(const Point& point) const noexcept;

    double get_x() const;
    double get_y() const;
    double get_z() const;

    void set_x(double const& x);
    void set_y(double const& y);
    void set_z(double const& z);

    Point operator+(const Point& point);
    Point sum(const Point& point);
    Point operator-(const Point& point);
    Point sub(const Point& point);

    Point relative_to(const Point& c);

    void move(const double dx, const double dy, const double dz);
    void scale(const double dx, const double dy, const double dz);
    void rotate(const double x_o, const double y_o, const double z_o);

private:
    double _x, _y, _z;
    void rotate_x(const double& x_o);
    void rotate_y(const double& y_o);
    void rotate_z(const double& z_o);
};