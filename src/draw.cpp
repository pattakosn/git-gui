// clang-format off
#include <iostream>
#include "draw.h"
#include <glad/gl.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_opengl3.h"
#include "stb_image.h"
// clang-format on

SDL_Surface* LoadTextureFromFile(const char* filename, int& width, int& height);

static SDL_Window* Window = nullptr;
static SDL_Renderer* Renderer = nullptr;
static SDL_GLContext glcontext = nullptr;
static constexpr int width = 1080;
static constexpr int height = (width / 16.) * 9.;

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
#define GL_GREY .5, .5, .5, 1

void graphics_initialize() {
    CHECK_SDL_RESULT(SDL_Init(SDL_INIT_EVENTS | SDL_INIT_TIMER | SDL_INIT_VIDEO), "Initialisation failure: ");

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
    SDL_WindowFlags window_flags = (SDL_WindowFlags)(SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);  // SDL_WINDOW_HIDDEN
    CHECK_SDL_RESULT(Window = SDL_CreateWindow("", 0, 0, 0, 0, window_flags); !Window, "Window creation failure: ");
    CHECK_SDL_RESULT(glcontext = SDL_GL_CreateContext(Window); !glcontext, "Context creation failure: ");

    SDL_GL_MakeCurrent(Window, glcontext);
    SDL_GL_SetSwapInterval(1);  // vsync

    // int icon_width;
    // int icon_length;
    //     SDL_Surface *icon = LoadTextureFromFile("D:/github.com/git-gui/assets/slack-penguin-bw-255x300.png", icon_width, icon_length);
    //     if (!icon) std::cerr << "error loading icon\n";
    //     SDL_SetWindowIcon(Window, icon);
    //     SDL_FreeSurface(icon);

    SDL_SetWindowSize(Window, width, height);
    SDL_SetWindowPosition(Window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
    SDL_SetWindowTitle(Window, "Context 4.6 with GLAD");
    SDL_ShowWindow(Window);
    CHECK_SDL_RESULT(SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4), "Error setting GL_MAJOR_VERSION :");
    CHECK_SDL_RESULT(SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6), "Error setting GL_MINOR_VERSION :");

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

int my_poll() {
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
    // (Your code calls SDL_GL_SwapWindow() etc.)
    SDL_GL_SwapWindow(Window);
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

static bool show_demo_window = true;
static bool show_another_window = false;
void my_imgui_more_stupid_win() {
    static ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    if (show_demo_window) ImGui::ShowDemoWindow(&show_demo_window);
    // 2. Show a simple window that we create ourselves. We use a Begin/End pair to create a named window.
    {
        static float f = 0.0f;
        static int counter = 0;

        ImGui::Begin("Hello, world!");  // Create a window called "Hello, world!" and append into it.

        ImGui::Text("This is some useful text.");           // Display some text (you can use a format strings too)
        ImGui::Checkbox("Demo Window", &show_demo_window);  // Edit bools storing our window open/close state
        ImGui::Checkbox("Another Window", &show_another_window);

        ImGui::SliderFloat("float", &f, 0.0f, 1.0f);             // Edit 1 float using a slider from 0.0f to 1.0f
        ImGui::ColorEdit3("clear color", (float*)&clear_color);  // Edit 3 floats representing a color

        if (ImGui::Button("Button"))  // Buttons return true when clicked (most widgets return true when edited/activated)
            counter++;
        ImGui::SameLine();
        ImGui::Text("counter = %d", counter);

        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        ImGui::End();
    }

    // 3. Show another simple window.
    if (show_another_window) {
        ImGui::Begin("Another Window", &show_another_window);  // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
        ImGui::Text("Hello from another window!");
        if (ImGui::Button("Close Me")) show_another_window = false;
        ImGui::End();
    }
}

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