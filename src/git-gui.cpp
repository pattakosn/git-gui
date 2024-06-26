// https://libgit2.org/docs/guides/101-samples/
// clang-format off
#include <iostream>
#include "my_git.h"
#include "draw.h"
#include <glad/gl.h>
#include <SDL.h>
#include <SDL_opengl.h>
// clang-format on

extern SDL_Window *Window;

int main(int, char **) {
    std::cout << "\n\tGit-Gui 0.0.1\n\n";
    atexit(deinit);
    atexit(deinit);
    atexit(deinit);
    init();
    init();

    find_repo();

    graphics_initialize();

    while (my_poll()) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        my_imgui_loop_start();
        my_imgui_demo();

        my_imgui_stupid_win();
        my_imgui_loop_end();
        SDL_GL_SwapWindow(Window);
    }

    graphics_shutdown();
    return EXIT_SUCCESS;
}
