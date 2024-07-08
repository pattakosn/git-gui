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
#include "stb_image.h"
#include "draw.h"
#include "git.h"
// clang-format on

SDL_Surface* LoadTextureFromFile(const char* filename, int& width, int& height);

static SDL_Window* Window = nullptr;
static SDL_Renderer* Renderer = nullptr;
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
    int icon_width;
    int icon_length;
    SDL_Surface* icon = IMG_Load(
        "/home/pattakosn/github.com/git-gui/assets/git64-1.png");  // LoadTextureFromFile("D:/github.com/git-gui/assets/slack-penguin-bw-255x300.png", icon_width, icon_length);
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

    // Setup Platform/Renderer backends
    EXIT_ON_FALSE(!ImGui_ImplSDL2_InitForOpenGL(Window, glcontext), "Error Initializing ImGuiImplSDL2_OGL\n");
    EXIT_ON_FALSE(!ImGui_ImplOpenGL3_Init(), "Error Initializing ImGuiImplOGL\n");

    glClearColor(GL_GREY);
}

void basic_info() {
    // ImGuiContext& g = *ImGui::GetCurrentContext();
    ImGuiIO& io = ImGui::GetIO();

    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
    ImGui::Text("%d vertices, %d indices (%d triangles)", io.MetricsRenderVertices, io.MetricsRenderIndices, io.MetricsRenderIndices / 3);
    // ImGui::Text("%d visible windows, %d current allocations", io.MetricsRenderWindows, g.DebugAllocInfo.TotalAllocCount - g.DebugAllocInfo.TotalFreeCount);
}

void graphics_shutdown() {
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
    // (Your code calls SDL_GL_SwapWindow() etc.)
    SDL_GL_SwapWindow(Window);
}

void my_imgui_demo() { ImGui::ShowDemoWindow(); }

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

static bool show_demo_window = false;
static bool show_another_window = false;
void my_imgui_more_stupid_win() {
    std::cout << "\t\t SKATA\n";
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

void OpenMenu() {
    static char open_dir[128];
    static bool once = true;
    if (once) {
        std::strncpy(open_dir, std::filesystem::current_path().c_str(), 127);
        open_dir[127] = '\0';
        once = false;
    }

    ImGui::SetWindowSize({300, 60});
    if (ImGui::Begin("Open Repository in")) {
        ImGui::InputText("directory", open_dir, IM_ARRAYSIZE(open_dir));
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
            if (0 == open_repo(open_dir)) {
                std::cout << "FOUND and opened repo in: " << open_dir << "\n";
            } else {
                std::cout << "Couldn't find or open repo in: " << open_dir << "\n";
            }
            show_open_menu = false;
        }
        ImGui::End();
    }
}

void menu() {
    if (ImGui::BeginMainMenuBar()) {
        if (ImGui::BeginMenu("File")) {
            // ImGui::MenuItem("sample", NULL, false, false);
            if (ImGui::MenuItem("Open repository", "Ctrl+O", &show_open_menu)) {
                std::cout << "Open\n";
            }
            if (ImGui::MenuItem("Create repository", "Ctrl+N")) {
                my_imgui_more_stupid_win();
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
        ImGui::EndMainMenuBar();
    }

    if (show_open_menu) OpenMenu();
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

// const float toolbarSize = 50;
//
// void DockSpaceUI()
//{
//	ImGuiViewport* viewport = ImGui::GetMainViewport();
//	ImGui::SetNextWindowPos(viewport->Pos + ImVec2(0, toolbarSize));
//	ImGui::SetNextWindowSize(viewport->Size - ImVec2(0, toolbarSize));
//	ImGui::SetNextWindowViewport(viewport->ID);
//	ImGuiWindowFlags window_flags = 0
//		| ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking
//		| ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse
//		| ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove
//		| ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
//
//	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
//	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
//	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
//	ImGui::Begin("Master DockSpace", NULL, window_flags);
//	ImGuiID dockMain = ImGui::GetID("MyDockspace");
//
//	// Save off menu bar height for later.
//	menuBarHeight = ImGui::GetCurrentWindow()->MenuBarHeight();
//
//	ImGui::DockSpace(dockMain);
//	ImGui::End();
//	ImGui::PopStyleVar(3);
// }
//
// void ToolbarUI()
//{
//	ImGuiViewport* viewport = ImGui::GetMainViewport();
//	ImGui::SetNextWindowPos(ImVec2(viewport->Pos.x, viewport->Pos.y + menuBarHeight));
//	ImGui::SetNextWindowSize(ImVec2(viewport->Size.x, toolbarSize));
//	ImGui::SetNextWindowViewport(viewport->ID);
//
//	ImGuiWindowFlags window_flags = 0
//		| ImGuiWindowFlags_NoDocking
//		| ImGuiWindowFlags_NoTitleBar
//		| ImGuiWindowFlags_NoResize
//		| ImGuiWindowFlags_NoMove
//		| ImGuiWindowFlags_NoScrollbar
//		| ImGuiWindowFlags_NoSavedSettings
//		;
//	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0);
//	ImGui::Begin("TOOLBAR", NULL, window_flags);
//	ImGui::PopStyleVar();
//
//	ImGui::Button("Toolbar goes here", ImVec2(0, 37));
//
//	ImGui::End();
// }