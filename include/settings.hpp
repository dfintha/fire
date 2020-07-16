#if !defined(FIRE_SETTINGS_HPP)
#define FIRE_SETTINGS_HPP

namespace fire {

class settings {
public:
    settings(int argc, char **argv);
    int width() const;
    int height() const;
    bool resolution_set() const;
    bool full_screen() const;

private:
    int window_width;
    int window_height;
    bool is_full_screen;
};

}

#endif
