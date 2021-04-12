#include "dots_arr_transform.hpp"
#include "error.hpp"

int rotate_dots(dots_arr_t &dots, const rotate_t &rotate)
{
    if (dot_arr_is_empty(dots))
        return ROTATE_ERROR;

    unsigned int ndots = get_dots_num(dots);

    for (unsigned int i = 0; i < ndots; i++)
    {
        dot_t &dot = get_dot(dots, i);
        rotate_dot(dot, rotate);
    }

    return OK;
}

int scale_dots(dots_arr_t &dots, const scale_t &scale)
{
    if (dot_arr_is_empty(dots))
        return SCALE_ERROR;

    unsigned int ndots = get_dots_num(dots);

    for (unsigned int i = 0; i < ndots; i++)
    {
        dot_t &dot = get_dot(dots, i);
        scale_dot(dot, scale);
    }

    return OK;
}

int move_dots(dots_arr_t &dots, const move_t &move)
{
    if (dot_arr_is_empty(dots))
        return MOVE_ERROR;

    unsigned int ndots = get_dots_num(dots);

    for (unsigned int i = 0; i < ndots; i++)
    {
        dot_t &dot = get_dot(dots, i);
        move_dot(dot, move);
    }

    return OK;
}
