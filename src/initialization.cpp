// clang-format off
#include <iostream>
#include <glad/gl.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>
#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_opengl3.h"
// clang-format on

static SDL_Window* Window = nullptr;
// static SDL_Renderer* Renderer = nullptr;
static SDL_GLContext glcontext = nullptr;
static constexpr int width = 1200;
static constexpr int height = width * 3 / 4;

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
#define GL_GREY .15f, .15f, .15f, 1.f

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
    // int icon_width;
    // int icon_length;
    //  LoadTextureFromFile("D:/github.com/git-gui/assets/slack-penguin-bw-255x300.png", icon_width, icon_length);
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
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

    SDL_GL_DeleteContext(glcontext);
    SDL_DestroyWindow(Window);
    SDL_Quit();
}

void imgui_loop_start() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // (After event loop)
    // Start the Dear ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();
}

void imgui_loop_end() {
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