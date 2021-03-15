#pragma once

#include <cstdio>
#include "model.hpp"

#define READ_ERROR              1
#define WRITE_ERROR             2
#define ALREADY_LOADED          3

int get_model(model_t &model, FILE *file);
int read_from_file(model_t &model, const char *filename);
int save_to_file(const model_t &model, const char *filename);
