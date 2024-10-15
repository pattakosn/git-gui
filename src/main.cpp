// https://libgit2.org/docs/guides/101-samples/
// https://pthom.github.io/imgui_manual_online/manual/imgui_manual.html
// https://possiblyashrub.github.io/imgui-docs/#/docs/latest/home
// clang-format off
#include <iostream>
#include "git.h"
#include "draw.h"
#include <SDL_timer.h>
#include "video_player.h"
// clang-format on

static constexpr Uint64 FRAMES_PER_SECOND = 10U;
static constexpr Uint64 SKIP_TICKS = 1000U / FRAMES_PER_SECOND;
//tatic const char* video = "/home/pattakosn/github.com/git-gui/assets/SampleVideo_360x240_1mb.mp4";

int main(int, char**) {
    std::cout << "\n[git-gui]\tGit-Gui 0.0.1\n\n";
    atexit(deinit);
    atexit(deinit);
    atexit(deinit);
    init();
    init();

    find_repo();

    graphics_initialize();

    bool once = true;
    auto next_tick = SDL_GetTicks();
    long int sleep_time = 0;
    while (my_poll()) {
        my_imgui_loop_start();

        menu_bar();
        // tool_bar();
        // property_panel();
        // main_area();
        bottom_bar();
        my_imgui_loop_end();

        next_tick += SKIP_TICKS;
        sleep_time = next_tick - SDL_GetTicks();
        if (sleep_time >= 0) {
            SDL_Delay(sleep_time);
            once = true;
        } else {
            if (once) {
                std::cout << "[git-gui] Running behind on time?\n";
                once = false;
            }
        }
    }

    graphics_shutdown();
    return EXIT_SUCCESS;
}
