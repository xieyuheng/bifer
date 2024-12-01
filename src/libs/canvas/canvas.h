#pragma once

// About the four colors:
// - https://wiki.xxiivv.com/site/theme.html

typedef enum {
    BG_COLOR = 0, // Background/alpha
    SL_COLOR = 1, // Selection
    FG_COLOR = 2, // Foreground
    AP_COLOR = 3, // Application
} palette_color_t;

// The width and height of canvas are measured in tile.
struct canvas_t {
    size_t width, height;
    uint32_t *pixels;
    uint32_t palette[4];
};

canvas_t *canvas_new(size_t width, size_t height);
void canvas_destroy(canvas_t **self_pointer);

// The x and y position are measured in pixel.

void canvas_put_pixel(canvas_t *self, size_t x, size_t y, uint32_t pixel);
void canvas_draw_pixel(canvas_t *self, size_t x, size_t y, palette_color_t color);

void canvas_fill_bottom_right(canvas_t *self, size_t x, size_t y, palette_color_t color);
void canvas_fill_bottom_left(canvas_t *self, size_t x, size_t y, palette_color_t color);
void canvas_fill_top_right(canvas_t *self, size_t x, size_t y, palette_color_t color);
void canvas_fill_top_left(canvas_t *self, size_t x, size_t y, palette_color_t color);

// The width and height of image are measured in tile.

void canvas_draw_icn(canvas_t *self, size_t x, size_t y, uint8_t *bytes, size_t width, size_t height, uint8_t blending);
void canvas_draw_chr(canvas_t *self, size_t x, size_t y, uint8_t *bytes, size_t width, size_t height, uint8_t blending);
