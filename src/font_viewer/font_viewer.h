#pragma once

struct font_viewer_t {
    canvas_t *canvas;
    size_t width, height;
    blending_t blending;
    store_t *asset_store;
    font_t *font;
    glyph_t *glyph;
};

font_viewer_t *font_viewer_new(font_t *font);
void font_viewer_destroy(font_viewer_t **self_pointer);

void font_viewer_start(font_t *font);
