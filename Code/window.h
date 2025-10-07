#pragma once

#include "types.h"

void window_init(const char *title, int width, int height);
bool window_is_closing();

int window_get_width();
int window_get_height();

int window_get_fb_width();
int window_get_fb_height();
