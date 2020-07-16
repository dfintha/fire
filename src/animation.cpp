#include "animation.hpp"

#include <cstdlib>
#include <cstring>
#include <ctime>

fire::color_mapper::color_mapper(void *format) : format(format) {
}

fire::color_mapper::~color_mapper() {
}

fire::animation::animation(int width, int height, color_mapper& map_rgb) :
    width(width),
    height(height),
    scale(height / 10),
    pixels(new int[width * height]),
    palette(new uint32_t[scale])
{
    for (int i = 0; i < scale; ++i) {
        const uint8_t red = i * scheme[0] / scale;
        const uint8_t green = i * scheme[1] / scale;
        const uint8_t blue = i * scheme[2] / scale;
        palette[i] = map_rgb(red, green, blue);
    }

    memset(pixels.get(), 0, width * height * sizeof(int));
    for (int i = 0; i < width; ++i)
        pixels[(height - 1) * width + i] = scale - 1;

    srand(unsigned(time(nullptr)));
}

void fire::animation::render() {
    for (int x = 0; x < width; ++x)
        for (int y = 1; y < height; ++y)
            spread(y * width + x);
}

void fire::animation::flip_to(uint32_t *window_pixels) {
    for (int i = 0; i < width * height; ++i)
        window_pixels[i] = palette[pixels[i]];
}

void fire::animation::spread(int index) {
    if (pixels[index] == 0) {
        pixels[index - width] = 0;
        return;
    }

    const int random = (rand() % 3) & 3;
    const int where = index - random + 1;
    pixels[where - width] = pixels[index] - (random & 1);
}
