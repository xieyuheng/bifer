#include "index.h"

canvas_t *
canvas_new(size_t width, size_t height, size_t scale) {
    canvas_t *self = allocate(sizeof(canvas_t));
    self->width = width;
    self->height = height;
    self->scale = scale;

    self->pixels = allocate(self->width * self->height * sizeof(uint32_t));

    self->palette[BG_COLOR] = 0xff0047A0;
    self->palette[SL_COLOR] = 0xffcd2e3a;
    self->palette[FG_COLOR] = 0xff000000;
    self->palette[AP_COLOR] = 0xffffffff;

    self->window = canvas_window_new(self);

    self->clickable_area_list = list_new();
    return self;
}

void
canvas_destroy(canvas_t **self_pointer) {
    assert(self_pointer);
    if (*self_pointer) {
        canvas_t *self = *self_pointer;
        free(self->pixels);
        canvas_window_destroy(&self->window);
        free(self);
        *self_pointer = NULL;
    }
}

void
canvas_open(canvas_t *self) {
    canvas_window_open(self->window);
}

void
canvas_put_pixel(canvas_t *self, size_t x, size_t y, uint32_t pixel) {
    self->pixels[y * self->width + x] = pixel;
}

void
canvas_draw_pixel(canvas_t *self, size_t x, size_t y, color_t color) {
    canvas_put_pixel(self, x, y, self->palette[color]);
}
