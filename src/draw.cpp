// clang-format off
#include "draw.h"
#include <iostream>
#include <filesystem>
#include <glad/gl.h>
#include <SDL.h>
#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "git.h"
#include "themes.h"
// clang-format on

static bool please_exit = false;
int my_poll() {
    if (please_exit) return 0;

    SDL_Event event;
    // SDL_WaitEvent(&event);
    while (SDL_PollEvent(&event)) {
        // (Where your code calls SDL_PollEvent())
        ImGui_ImplSDL2_ProcessEvent(&event);  // Forward your event to backend
        if (event.type == SDL_QUIT) {
            return 0;
        }
        if (event.type == SDL_KEYDOWN) {
            switch (event.key.keysym.sym) {
                case SDLK_ESCAPE:
                case SDLK_q:
                    return 0;
                    break;
                default:
                    break;
            }
        }
        if (event.type == SDL_WINDOWEVENT) {
            if (event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
                glViewport(0, 0, event.window.data1, event.window.data2);
            }
        }
    }
    return 1;
}

// TODO remove me
static void HelpMarker(const char* desc) {
    ImGui::TextDisabled("(?)");
    if (ImGui::BeginItemTooltip()) {
        ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
        ImGui::TextUnformatted(desc);
        ImGui::PopTextWrapPos();
        ImGui::EndTooltip();
    }
}
bool show_open_menu = false;
bool show_gui_debug_info = false;
bool show_no_git_found_error = false;
std::string show_no_git_found_error_msg{};
bool show_demo_win = false;
void OpenMenu() {
    constexpr int path_size = 128;
    static char open_dir[path_size];
    static bool cwd_isnt_initialized = true;
    if (cwd_isnt_initialized) {
        strncpy(open_dir, std::filesystem::current_path().string().c_str(), path_size - 1);
        cwd_isnt_initialized = false;
    }

    ImGui::SetWindowSize({300, 60});
    if (ImGui::Begin("Open Repository in", &show_open_menu)){ //}, ImGuiWindowFlags_NoDecoration ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoCollapse)) {
        ImGui::InputText("##", open_dir, IM_ARRAYSIZE(open_dir));
        ImGui::SameLine();
        HelpMarker(
            "USER:\n"
            "Hold SHIFT or use mouse to select text.\n"
            "CTRL+Left/Right to word jump.\n"
            "CTRL+A or Double-Click to select all.\n"
            "CTRL+X,CTRL+C,CTRL+V clipboard.\n"
            "CTRL+Z,CTRL+Y undo/redo.\n"
            "ESCAPE to revert.\n\n"
            "PROGRAMMER:\n"
            "You can use the ImGuiInputTextFlags_CallbackResize facility if you need to wire InputText() "
            "to a dynamic string type. See misc/cpp/imgui_stdlib.h for an example (this is not demonstrated "
            "in imgui_demo.cpp).");

        ImGuiStyle& style = ImGui::GetStyle();
        float size = ImGui::CalcTextSize("Open").x + style.FramePadding.x * 2.0f;
        float avail = ImGui::GetContentRegionAvail().x;
        float off = (avail - size) * 0.5f;  // center alignment
        if (off > 0.0f) ImGui::SetCursorPosX(ImGui::GetCursorPosX() + off);
        if (ImGui::Button("Open")) {
            auto res = repo_open(open_dir);
            if (!res.empty()) {
                show_no_git_found_error = true;
                show_no_git_found_error_msg = res;
                auto detected_repo = find_repo();
                if(!detected_repo.empty())
                ;//    show_no_git_found_error_msg += "\n"
            } else
                show_open_menu = false;
        }
        ImGui::End();
    }
    if (show_no_git_found_error) {
        // ImGui::SetWindowSize(ImVec2(150, 75));
        if (ImGui::Begin("Git repo not found", &show_no_git_found_error)) {  //}, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse)) {
            ImGui::Text("%s", show_no_git_found_error_msg.c_str());
            float size = ImGui::CalcTextSize("OK").x + ImGui::GetStyle().FramePadding.x * 2.0f;
            float avail = ImGui::GetContentRegionAvail().x;
            float off = (avail - size) * 0.5f;  // center alignment
            if (off > 0.0f) 
                ImGui::SetCursorPosX(ImGui::GetCursorPosX() + off);
            if (ImGui::Button("OK")) show_no_git_found_error = false;
        }
        ImGui::End();
    }
}

void menu_bar() {
    if (ImGui::BeginMainMenuBar()) {
        if (ImGui::BeginMenu("File")) {
            // ImGui::MenuItem("sample", NULL, false, false);
            if (ImGui::MenuItem("Open repository", "Ctrl+O", &show_open_menu)) {
                std::cout << "Open\n";
            }
            if (ImGui::MenuItem("Close repository")) {
                repo_close();
            }
            if (ImGui::MenuItem("Create repository", "Ctrl+N")) {
                std::cout << "Created\n";
            }
            if (ImGui::MenuItem("Scan for repositories")) {
                std::cout << "Scanned\n";
            }
            if (ImGui::MenuItem("Quit", "Ctrl+z")) {
                please_exit = true;
                std::cout << "Au revoir\n";
            }
            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Repository")) {
            if (ImGui::MenuItem("Fetch")) {
                std::cout << "Fetch\n";
            }
            if (ImGui::MenuItem("Pull", "CTRL+P", false, false)) {
                std::cout << "Pull\n";
            }
            if (ImGui::MenuItem("Push")) {
                std::cout << "Push\n";
            }  // Disabled item
            ImGui::Separator();
            if (ImGui::MenuItem("a")) {
            }
            if (ImGui::MenuItem("b")) {
            }
            if (ImGui::MenuItem("c")) {
            }
            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("About")) {
            if (ImGui::MenuItem("gui debug info")) show_gui_debug_info = !show_gui_debug_info;
            if (ImGui::MenuItem("demo window")) show_demo_win = !show_demo_win;
            if (ImGui::MenuItem("themes")) show_theme_win = !show_theme_win;
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }

    if (show_open_menu) OpenMenu();
    if (show_gui_debug_info) ImGui::ShowMetricsWindow(&show_gui_debug_info);
    if (show_demo_win) ImGui::ShowDemoWindow(&show_demo_win);
    if (show_theme_win) Themes();
}

void imgui_shortcut_handler()
{
    if (ImGui::IsKeyDown(ImGuiKey_LeftCtrl) && ImGui::IsKeyPressed(ImGuiKey_O)) {
        show_open_menu = true;
        std::cout << "Open menu keyboard\n";
    }
    if (ImGui::IsKeyDown(ImGuiKey_LeftCtrl) && ImGui::IsKeyPressed(ImGuiKey_N))
        std::cout << "new repo from keyboard?\n";
    if (ImGui::IsKeyDown(ImGuiKey_LeftCtrl) && ImGui::IsKeyPressed(ImGuiKey_Z))
        please_exit = true;
}

/*
    ImGui::SetNextWindowSize(ImVec2(200, -1));
    ImGui::Begin("Toolbar");
    // Add toolbar items here
    ImGui::End();

    ImGui::SetNextWindowSize(ImVec2(200, -1));
    ImGui::SetNextWindowPos(ImVec2(ImGui::GetIO().DisplaySize.x - 200, 0));
    ImGui::Begin("Property Panel");
    // Add property panel items here
    ImGui::End();

    ImGui::Begin("Main Content Area");
    // Add main content items here
    ImGui::End();
*/