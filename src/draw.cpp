// clang-format off
#include <iostream>
#include <filesystem>
#include <cstring>
#include <glad/gl.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>
#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_opengl3.h"
#include "draw.h"
#include "git.h"
// clang-format on

static SDL_Window* Window = nullptr;
//static SDL_Renderer* Renderer = nullptr;
static SDL_GLContext glcontext = nullptr;
static constexpr int width = 1200;
static constexpr int height = (width / 4.) * 3.;

#define CHECK_SDL_RESULT(X, MSG)                                       \
    do {                                                               \
        if (X) {                                                       \
            std::cerr << "\t[ SDL2  ] " MSG << SDL_GetError() << "\n"; \
            exit(EXIT_FAILURE);                                        \
        }                                                              \
    } while (0)
#define EXIT_ON_FALSE(X, MSG)               \
    do {                                    \
        if (X) {                            \
            std::cerr << "\t " MSG << "\n"; \
            exit(EXIT_FAILURE);             \
        }                                   \
    } while (0)
#define GL_GREY .15, .15, .15, 1

void graphics_initialize() {
    CHECK_SDL_RESULT(SDL_Init(SDL_INIT_EVENTS | SDL_INIT_TIMER | SDL_INIT_VIDEO), "Initialisation failure: ");

    CHECK_SDL_RESULT(SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3), "Error setting GL_MAJOR_VERSION :");
    CHECK_SDL_RESULT(SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0), "Error setting GL_MINOR_VERSION :");
    //    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
    SDL_WindowFlags window_flags = (SDL_WindowFlags)(SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);  // SDL_WINDOW_HIDDEN
    CHECK_SDL_RESULT(Window = SDL_CreateWindow("", 0, 0, 0, 0, window_flags); !Window, "Window creation failure: ");
    CHECK_SDL_RESULT(glcontext = SDL_GL_CreateContext(Window); !glcontext, "Context creation failure: ");

    SDL_GL_MakeCurrent(Window, glcontext);
    SDL_GL_SetSwapInterval(1);  // vsync

    SDL_SetWindowSize(Window, width, height);
    SDL_SetWindowPosition(Window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
    SDL_SetWindowTitle(Window, "git-gui");
    SDL_ShowWindow(Window);
    //int icon_width;
    //int icon_length;
    // LoadTextureFromFile("D:/github.com/git-gui/assets/slack-penguin-bw-255x300.png", icon_width, icon_length);
    SDL_Surface* icon = IMG_Load("/home/pattakosn/github.com/git-gui/assets/git64-1.png");
    if (!icon) std::cerr << "error loading icon\n";
    SDL_SetWindowIcon(Window, icon);
    SDL_FreeSurface(icon);

    int version = gladLoadGL((GLADloadfunc)SDL_GL_GetProcAddress);
    printf("[ GLAD  ] Version %d.%d\n", GLAD_VERSION_MAJOR(version), GLAD_VERSION_MINOR(version));
    // SDL_Log("[GL] Vendor   : %s", glGetString(GL_VENDOR));
    printf("[  GL   ] Vendor   : %s\n", glGetString(GL_VENDOR));
    printf("[  GL   ] Renderer : %s\n", glGetString(GL_RENDERER));
    printf("[  GL   ] Version  : %s\n", glGetString(GL_VERSION));
    printf("[  GL   ] GLSL     : %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
    int maj;
    int min;
    glGetIntegerv(GL_MAJOR_VERSION, &maj);
    glGetIntegerv(GL_MINOR_VERSION, &min);
    printf("[  GL   ] Context  : %d.%d\n", maj, min);

    CHECK_SDL_RESULT(SDL_GL_GetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, &maj), "Error getting GL_CONTEXT_MAJOR_VER :");
    CHECK_SDL_RESULT(SDL_GL_GetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, &min), "Error getting GL_CONTEXT_MINOR_VER :");
    printf("[ SDL2  ] Context  : %d.%d\n", maj, min);

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    ImGui::StyleColorsDark();
    // ImGui::StyleColorsLight();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;   // Enable Gamepad Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;      // IF using Docking Branch
    // io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
    io.ConfigDockingWithShift = false;

    // Setup Platform/Renderer backends
    EXIT_ON_FALSE(!ImGui_ImplSDL2_InitForOpenGL(Window, glcontext), "Error Initializing ImGuiImplSDL2_OGL\n");
    EXIT_ON_FALSE(!ImGui_ImplOpenGL3_Init(), "Error Initializing ImGuiImplOGL\n");

    glClearColor(GL_GREY);
}

void graphics_shutdown() {
    repo_close();
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

    SDL_GL_DeleteContext(glcontext);
    SDL_DestroyWindow(Window);
    SDL_Quit();
}

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

void my_imgui_loop_start() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // (After event loop)
    // Start the Dear ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();
}

void my_imgui_loop_end() {
    // Rendering
    // (Your code clears your framebuffer, renders your other stuff etc.)
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    // viewport specific    // Update and Render additional Platform Windows
    // viewport specific    // (Platform functions may change the current OpenGL context, so we save/restore it to make it easier to paste this code elsewhere.
    // viewport specific    //  For this specific demo app we could also call SDL_GL_MakeCurrent(window, gl_context) directly)
    // viewport specific    ImGuiIO& io = ImGui::GetIO();
    // viewport specific    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
    // viewport specific        SDL_Window* backup_current_window = SDL_GL_GetCurrentWindow();
    // viewport specific        SDL_GLContext backup_current_context = SDL_GL_GetCurrentContext();
    // viewport specific        ImGui::UpdatePlatformWindows();
    // viewport specific        ImGui::RenderPlatformWindowsDefault();
    // viewport specific        SDL_GL_MakeCurrent(backup_current_window, backup_current_context);
    // viewport specific    }

    // (Your code calls SDL_GL_SwapWindow() etc.)
    SDL_GL_SwapWindow(Window);
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
    static char open_dir[128];
    static bool cwd_isnt_initialized = true;
    if (cwd_isnt_initialized) {
        std::strncpy(open_dir, std::filesystem::current_path().c_str(), 127);
        open_dir[127] = '\0';
        cwd_isnt_initialized = false;
    }

    ImGui::SetWindowSize({300, 60});
    if (ImGui::Begin("Open Repository in", &show_open_menu)) {
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
            } else
                show_open_menu = false;
        }
        ImGui::End();
    }
    if (show_no_git_found_error) {
        // ImGui::SetWindowSize(ImVec2(150, 75));
        if (ImGui::Begin("Git repo not found", &show_no_git_found_error)) {  //}, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse)) {
            ImGui::Text("%s", show_no_git_found_error_msg.c_str());
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
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }

    if (show_open_menu) OpenMenu();
    if (show_gui_debug_info) ImGui::ShowMetricsWindow(&show_gui_debug_info);
    if (show_demo_win) ImGui::ShowDemoWindow(&show_demo_win);
}

void bottom_bar() {
    auto text_size = ImGui::CalcTextSize("FPS");
    auto toolbar_size_y = text_size.y + ImGui::GetStyle().FramePadding.y;
    ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(ImVec2(viewport->Pos.x, ImGui::GetIO().DisplaySize.y - 2. * toolbar_size_y));  // ));  // menuBarHeight));
    ImGui::SetNextWindowSize(ImVec2(viewport->Size.x, toolbar_size_y));
    ImGui::SetNextWindowViewport(viewport->ID);

    ImGuiWindowFlags window_flags = 0 | ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
                                    ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoSavedSettings;
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0);
    if (ImGui::Begin("TOOLBAR", NULL, window_flags)) {
        ImGui::PopStyleVar();
        ImGui::Text("%.1f FPS (%.3f ms/frame)", ImGui::GetIO().Framerate, 1000.0f / ImGui::GetIO().Framerate);
        ImGui::End();
    }
}
/*
void tool_bar() {
    ImGui::SetNextWindowSize(ImVec2(200, -1));
    ImGui::Begin("Toolbar");
    // Add toolbar items here
    ImGui::End();
}
void property_panel() {
    ImGui::SetNextWindowSize(ImVec2(200, -1));
    ImGui::SetNextWindowPos(ImVec2(ImGui::GetIO().DisplaySize.x - 200, 0));
    ImGui::Begin("Property Panel");
    // Add property panel items here
    ImGui::End();
}

void main_area() {
    ImGui::Begin("Main Content Area");
    // Add main content items here
    ImGui::End();
}
*/