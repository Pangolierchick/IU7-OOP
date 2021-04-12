#pragma once

#include "model.hpp"
#include <cstdio>

int read_model(model_t &model, FILE *file);
int read_from_file(model_t &model, const char *filename);
int save_to_file(const model_t &model, const char *filename);
