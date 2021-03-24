#include "qt_wrap.hpp"

static inline double move_x_to_center(double x, double width) {
    return x + width / 2.0;
}

static inline double move_y_to_center(double y, double height) {
    return y + height / 2.0;
}


void draw_line(graphic_view_t &field, dot_t d1, dot_t d2) {
    field.scene->addLine(move_x_to_center(d1.x, field.width), 
                         move_y_to_center(d1.y, field.height),
                         move_x_to_center(d2.x, field.width), 
                         move_y_to_center(d2.y, field.height));
}

void clean_screen(graphic_view_t &field) {
    field.scene->clear();
}
