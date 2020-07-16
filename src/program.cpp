#include "animation.hpp"
#include "settings.hpp"

#include <chrono>
#include <cstdint>
#include <iostream>
#include <utility>

#include <SDL.h>

enum error_code {
    EXIT_SUCCESSFUL = 0,
    EXIT_SDL_INIT_FAILED = 1,
    EXIT_SDL_SURFACE_CREATION_FAILED = 2,
};

class sdl_color_mapper : public fire::color_mapper {
public:
    sdl_color_mapper(SDL_PixelFormat *format) : color_mapper(format) {
    }

    uint32_t operator()(uint8_t r, uint8_t g, uint8_t b) override {
        SDL_PixelFormat *sdl_format = static_cast<SDL_PixelFormat *>(format);
        return SDL_MapRGB(sdl_format, r, g, b);
    }
};

static std::pair<int, int> query_max_resolution() {
    SDL_Rect **modes = SDL_ListModes(nullptr, SDL_FULLSCREEN | SDL_HWSURFACE);
    if (modes == nullptr || modes == reinterpret_cast<SDL_Rect **>(-1)) {
        std::cerr << "Warning: Could not decide screen resolution, "
                     "falling back to 640x480.\n";
        return std::make_pair(640, 480);
    }

    SDL_Rect *highest = nullptr;
    for (int i = 0; modes[i] != nullptr; ++i) {
        SDL_Rect *r = modes[i];
        if (highest == nullptr || (r->w >= highest->w && r->h >= highest->h))
            highest = r;
    }

    return std::make_pair(highest->w, highest->h);
}

static void loop(SDL_Surface *surface, fire::animation& animation) {
    using clock = std::chrono::system_clock;
    using time = clock::time_point;
    constexpr auto delay = std::chrono::milliseconds(25);

    SDL_Event event;

    bool exiting = false;
    time before = clock::now();

    while (!exiting) {
        time now = clock::now();
        if (now - before > delay) {
            animation.render();
            animation.flip_to(static_cast<uint32_t *>(surface->pixels));
            SDL_Flip(surface);
            before = now;
        }

        if (!SDL_PollEvent(&event))
            continue;

        if (event.type == SDL_QUIT)
            exiting = true;

        if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_q)
            exiting = true;
    }
}

int main(int argc, char **argv) {
    const fire::settings settings(argc, argv);

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "Error: Could not initialize SDL.\n";
        return EXIT_SDL_INIT_FAILED;
    }

    const auto resolution = settings.resolution_set() && !settings.full_screen()
        ? std::make_pair(settings.width(), settings.height())
        : query_max_resolution();

    SDL_Surface *surface = SDL_SetVideoMode(resolution.first,
                                            resolution.second,
                                            32,
                                            SDL_SWSURFACE);

    if (surface == nullptr) {
        std::cerr << "Error: Could not create SDL surface.\n";
        return EXIT_SDL_SURFACE_CREATION_FAILED;
    }

    SDL_WM_SetCaption("Fire", nullptr);

    if (settings.full_screen())
        SDL_WM_ToggleFullScreen(surface);

    sdl_color_mapper map_rgb(surface->format);
    fire::animation animation(resolution.first, resolution.second, map_rgb);

    SDL_ShowCursor(SDL_DISABLE);
    loop(surface, animation);
    SDL_ShowCursor(SDL_ENABLE);

    SDL_Quit();
    return EXIT_SUCCESSFUL;
}
