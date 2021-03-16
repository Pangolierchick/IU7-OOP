#pragma once

#define OK                      0
#define ALLOC_ERROR             1
#define READ_ERROR              2
#define WRITE_ERROR             3
#define ALREADY_LOADED          4
#define BAD_EDGES_NUM           5
#define MOVE_ERROR              6
#define ROTATE_ERROR            7
#define SCALE_ERROR             8
#define BAD_DOTS_NUM            9

void error_manager(int errnum);
