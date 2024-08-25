// clang-format off
#include "load_texture_from_file.h"
#include "stb_image.h"
// clang-format on

SDL_Surface* LoadTextureFromFile(const char* filename, int& width, int& height) {
    int channels;
    unsigned char* data = stbi_load(filename, &width, &height, &channels, 0);

    if (data == nullptr) {
        fprintf(stderr, "Failed to load image: %s\n", stbi_failure_reason());
        return nullptr;
    }

    SDL_Surface* surface = SDL_CreateRGBSurfaceFrom((void*)data, width, height, channels * 8, channels * width, 0x000000ff, 0x0000ff00, 0x00ff0000, 0xff000000);

    if (surface == nullptr) {
        fprintf(stderr, "Failed to create SDL surface: %s\n", SDL_GetError());
        return nullptr;
    }
    stbi_image_free(data);
    return surface;
}
