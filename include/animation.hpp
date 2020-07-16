#if !defined(FIRE_ANIMATION_HPP)
#define FIRE_ANIMATION_HPP

#include <cstdint>
#include <memory>

namespace fire {

class color_mapper {
public:
    color_mapper(void *format);
    virtual ~color_mapper();
    virtual uint32_t operator()(uint8_t r, uint8_t g, uint8_t b) = 0;
protected:
    void *format;
};

class animation {
public:
    static constexpr int scheme[] = { 0xFF, 0x55, 0x00 };

public:
    animation(int width, int height, color_mapper& map_rgb);
    ~animation() noexcept = default;
    void render();
    void flip_to(uint32_t *window_pixels);

private:
    void spread(int index);

private:
    int width;
    int height;
    int scale;
    std::unique_ptr<int[]> pixels;
    std::unique_ptr<uint32_t[]> palette;
};

} // namespace fire

#endif
