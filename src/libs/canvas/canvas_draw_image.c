#include "index.h"

static uint8_t blending_table[4][16] = {
    {0, 0, 0, 0, 1, 0, 1, 1, 2, 2, 0, 2, 3, 3, 3, 0},
    {0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3},
    {1, 2, 3, 1, 1, 2, 3, 1, 1, 2, 3, 1, 1, 2, 3, 1},
    {2, 3, 1, 2, 2, 3, 1, 2, 2, 3, 1, 2, 2, 3, 1, 2},
};

void
canvas_draw_icn_image(
    canvas_t *self,
    size_t x, size_t y,
    uint8_t *bytes,
    size_t width, size_t height,
    uint8_t blending
) {
    for (size_t row = 0; row < height; row++) {
        for (size_t col = 0; col < width; col++) {
            for (size_t line = 0; line < 8; line++) {
                size_t index = (row * 8 * width) + (col * 8 + line);
                uint8_t byte = bytes[index];
                for (uint8_t s = 0; s < 8; s++) {
                    uint8_t bit = ((byte << s) & 0x80) != 0;
                    color_t color = bit;
                    color_t blended = blending_table[color][blending];
                    canvas_draw_pixel(
                        self,
                        x + (col * 8 + s),
                        y + (row * 8 + line),
                        blended);
                }
            }
        }
    }
}

void
canvas_draw_chr_image(
    canvas_t *self,
    size_t x, size_t y,
    uint8_t *bytes,
    size_t width, size_t height,
    uint8_t blending
) {
    for (size_t row = 0; row < height; row++) {
        for (size_t col = 0; col < width; col++) {
            for (size_t line = 0; line < 8; line++) {
                size_t index = (row * 8 * 2 * width) + (col * 8 * 2 + line);
                uint8_t chr1 = bytes[index];
                uint8_t chr2 = bytes[index + 8];
                for (uint8_t s = 0; s < 8; s++) {
                    uint8_t bit1 = ((chr1 << s) & 0x80) != 0;
                    uint8_t bit2 = ((chr2 << s) & 0x80) != 0;
                    color_t color = bit1 + bit2 * 2;
                    color_t blended = blending_table[color][blending];
                    canvas_draw_pixel(
                        self,
                        x + (col * 8 + s),
                        y + (row * 8 + line),
                        blended);
                }
            }
        }
    }
}
