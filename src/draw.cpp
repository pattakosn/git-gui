// clang-format off
#include <iostream>
#include "draw.h"
#include <glad/gl.h>
#include <SDL.h>
#include <SDL_opengl.h>
//#include <SDL_image.h>
#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_opengl3.h"
// clang-format on

SDL_Window *Window = nullptr;
SDL_Renderer *Renderer = nullptr;
SDL_GLContext glcontext = nullptr;
static constexpr int width = 1080;
static constexpr int height = (width / 16.) * 9.;

#define MY_SDL_CHECK(X, MSG)                                       \
    do {                                                           \
        if (X) {                                                   \
            std::cerr << "\tSDL2: " MSG << SDL_GetError() << "\n"; \
            exit(EXIT_FAILURE);                                    \
        }                                                          \
    } while (0)
#define GL_GREY .5, .5, .5, 1

void graphics_initialize() {
    MY_SDL_CHECK(SDL_Init(SDL_INIT_EVENTS | SDL_INIT_TIMER | SDL_INIT_VIDEO), "Initialisation failure: ");
    MY_SDL_CHECK(Window = SDL_CreateWindow("", 0, 0, 0, 0, SDL_WINDOW_HIDDEN | SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE); !Window, "Window creation failure: ");
    MY_SDL_CHECK(glcontext = SDL_GL_CreateContext(Window); !glcontext, "Context creation failure: ");
    // SDL_Surface *icon = IMG_Load("./dobbs96.png");
    // if (!icon) std::cerr << "error loading icon\n";
    // SDL_SetWindowIcon(Window, icon);
    // SDL_FreeSurface(icon);
    SDL_SetWindowSize(Window, width, height);
    SDL_SetWindowPosition(Window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
    SDL_SetWindowTitle(Window, "Context 4.6 with GLAD");
    SDL_ShowWindow(Window);
    MY_SDL_CHECK(SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4), "Error setting GL_MAJOR_VERSION :");
    MY_SDL_CHECK(SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6), "Error setting GL_MINOR_VERSION :");

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

    SDL_GL_GetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, &maj);
    SDL_GL_GetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, &min);
    printf("[ SDL2  ] Context  : %d.%d\n", maj, min);

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    ImGui::StyleColorsDark();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;   // Enable Gamepad Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;      // IF using Docking Branch
    // io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

    // Setup Platform/Renderer backends
    ImGui_ImplSDL2_InitForOpenGL(Window, glcontext);
    ImGui_ImplOpenGL3_Init();

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

int my_poll() {
    SDL_Event event;
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
    // (Your code calls SDL_GL_SwapWindow() etc.)
}

void my_imgui_demo() {
    // Show demo window! :)
    ImGui::ShowDemoWindow();
}

void my_imgui_stupid_win() {
    float speed = 0.;
    bool param;
    ImGui::Begin("stupid window");
    ImGui::Checkbox("Boolean property", &param);
    if (ImGui::Button("Reset Speed")) {
        // This code is executed when the user clicks the button
        speed = 0;
    }
    ImGui::SliderFloat("Speed", &speed, 0.0f, 10.0f);
    ImGui::End();
}
