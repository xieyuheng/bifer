#pragma once

// The width and height of image are measured in tile.

void canvas_draw_icn_image(canvas_t *self, size_t x, size_t y, uint8_t *bytes, size_t width, size_t height, uint8_t blending);
void canvas_draw_chr_image(canvas_t *self, size_t x, size_t y, uint8_t *bytes, size_t width, size_t height, uint8_t blending);
