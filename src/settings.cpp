#include "settings.hpp"

#include <cstdlib>
#include <cstring>

fire::settings::settings(int argc, char **argv) :
    window_width(0),
    window_height(0),
    is_full_screen(true)
{
    enum parse_state {
        ARGUMENT,
        WIDTH,
        HEIGHT
    } state = ARGUMENT;

    --argc, ++argv;
    for (int i = 0; i < argc; ++i) {
        const char *arg = argv[i];

        switch (state) {
            case ARGUMENT:
                if (strcmp(arg, "--width") == 0) {
                    state = WIDTH;
                } else if (strcmp(arg, "--height") == 0) {
                    state = HEIGHT;
                } else if (strcmp(arg, "--no-full-screen") == 0) {
                    is_full_screen = false;
                }
                break;

            case WIDTH:
                window_width = atoi(arg);
                state = ARGUMENT;
                break;

            case HEIGHT:
                window_height = atoi(arg);
                state = ARGUMENT;
                break;

            default:
                break;
        }
    }
}

int fire::settings::width() const {
    return window_width;
}

int fire::settings::height() const {
    return window_height;
}

bool fire::settings::resolution_set() const {
    return width() != 0 && height() != 0;
}

bool fire::settings::full_screen() const {
    return is_full_screen;
}
