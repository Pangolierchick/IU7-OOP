#pragma once

enum commands {
    MOVE,
    SCALE,
    ROTATE,
    DRAW,
    LOAD_FROM_FILE,
    SAVE_TO_FILE,
    QUIT,
    UNKNOWN_COMMAND
};

using commands_t = enum commands;
