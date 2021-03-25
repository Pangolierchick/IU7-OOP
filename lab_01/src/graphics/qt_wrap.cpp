#include "qt_wrap.hpp"

void draw_line(graphic_view_t &field, dot_t d1, dot_t d2) {
    field.scene->addLine(d1.x, d1.y, d2.x, d2.y);
}

void clean_screen(graphic_view_t &field) {
    field.scene->clear();
}
