#ifndef LOAD_TEXTURE_FROM_FILE
#define LOAD_TEXTURE_FROM_FILE
#include <SDL.h>
SDL_Surface* LoadTextureFromFile(const char* filename, int& width, int& height);
#endif