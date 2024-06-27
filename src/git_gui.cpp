// https://libgit2.org/docs/guides/101-samples/
// clang-format off
#include <iostream>
#include "git.h"
#include "draw.h"
// clang-format on

int main(int, char **) {
    std::cout << "\n[git-gui]\tGit-Gui 0.0.1\n\n";
    atexit(deinit);
    atexit(deinit);
    atexit(deinit);
    init();
    init();

    find_repo();

    graphics_initialize();

    while (my_poll()) {
        my_imgui_loop_start();
        
       // my_imgui_demo();
        my_imgui_stupid_win();
        my_imgui_more_stupid_win();

        my_imgui_loop_end();
    }

    graphics_shutdown();
    return EXIT_SUCCESS;
}
