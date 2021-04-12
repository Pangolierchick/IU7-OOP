#include "manager.hpp"
#include "draw.hpp"
#include "model.hpp"
#include "model_io.hpp"

int task_manager(const event_t &event, event_data_t &data) {
    int res = 0;

    static model_t model = init_model();

    switch (event.cmd) {
    case MOVE:
        res = move_model(model, data.move);
        break;
    case SCALE:
        res = scale_model(model, data.scale);
        break;
    case ROTATE:
        res = rotate_model(model, data.rotate);
        break;
    case DRAW:
        res = draw_model(model, data.field);
        break;
    case LOAD_FROM_FILE:
        res = read_from_file(model, data.input_filename);
        break;
    case SAVE_TO_FILE:
        res = save_to_file(model, data.output_filename);
        break;
    case QUIT:
        destroy_model(model);
        break;
    default:
        res = UNKNOWN_COMMAND;
        break;
    }

    return res;
}
