// https://libgit2.org/docs/guides/101-samples/
#include <iostream>
#include "mygit.h"

#include <glad/gl.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>

#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_opengl3.h"


SDL_Window *Window = nullptr;
SDL_Renderer *Renderer = nullptr;
SDL_GLContext glcontext = nullptr;
static constexpr int width = 1080;
static constexpr int height = (width/16.) * 9.;
#define GL_GREY .5, .5, .5, 1
float speed = 0.;
bool param;

int main()
{
        std::cout << "\n\tgit gui 0.0.0\n";
        atexit(deinit);
        atexit(deinit);
        atexit(deinit);
        init();
        init();

        find_repo();
       
        std::cout << "libgit2: Initializing\n";
        git_libgit2_init();
        std::cout << "libgit2: Initializes\n";

        {
        SDL_Init(SDL_INIT_EVERYTHING);
        Window = SDL_CreateWindow("", 0, 0, 0, 0, SDL_WINDOW_HIDDEN|SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
        glcontext = SDL_GL_CreateContext(Window);
      //  SDL_Surface *icon;
      //  icon=IMG_Load("./../assets/gfx/icon.png");
      //  SDL_SetWindowIcon(Window, icon);
      //  SDL_FreeSurface(icon);
        }
        SDL_SetWindowSize(Window, width, height);
        SDL_SetWindowPosition(Window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
        SDL_SetWindowTitle(Window, "Context 4.6 with GLAD");
        SDL_ShowWindow(Window);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);

int version = gladLoadGL((GLADloadfunc) SDL_GL_GetProcAddress);
printf("GL %d.%d\n", GLAD_VERSION_MAJOR(version), GLAD_VERSION_MINOR(version));
    SDL_Log("Vendor   : %s", glGetString(GL_VENDOR));
    SDL_Log("Renderer : %s", glGetString(GL_RENDERER));
    SDL_Log("Version  : %s", glGetString(GL_VERSION));
    SDL_Log("GLSL     : %s", glGetString(GL_SHADING_LANGUAGE_VERSION));
    int maj;
    int min;
    SDL_GL_GetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, &maj);
    SDL_GL_GetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, &min);
    SDL_Log("Context  : %d.%d", maj, min);

    glGetIntegerv(GL_MAJOR_VERSION, &maj);
    glGetIntegerv(GL_MINOR_VERSION, &min);
    SDL_Log("Context  : %d.%d", maj, min);


// Setup Dear ImGui context
IMGUI_CHECKVERSION();
ImGui::CreateContext();
ImGuiIO& io = ImGui::GetIO();
    ImGui::StyleColorsDark();
io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // IF using Docking Branch
io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

// Setup Platform/Renderer backends
ImGui_ImplSDL2_InitForOpenGL(Window, glcontext);
ImGui_ImplOpenGL3_Init();



    glClearColor(GL_GREY);

    SDL_Event event;
    int running = 1;
    while (running) {
                glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

        while (SDL_PollEvent(&event)) {
                // (Where your code calls SDL_PollEvent())
ImGui_ImplSDL2_ProcessEvent(&event); // Forward your event to backend
            if (event.type == SDL_QUIT) {
                running =0;
            }
            if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                case SDLK_ESCAPE:
                case SDLK_q:
                    running =0;
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
// (After event loop)
// Start the Dear ImGui frame
ImGui_ImplOpenGL3_NewFrame();
ImGui_ImplSDL2_NewFrame();
ImGui::NewFrame();
ImGui::ShowDemoWindow(); // Show demo window! :)

ImGui::Begin("MyWindow");
ImGui::Checkbox("Boolean property", &param);
if(ImGui::Button("Reset Speed")) {
    // This code is executed when the user clicks the button
    speed = 0;
}
ImGui::SliderFloat("Speed", &speed, 0.0f, 10.0f);
ImGui::End();


// Rendering
// (Your code clears your framebuffer, renders your other stuff etc.)
ImGui::Render();
ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
// (Your code calls SDL_GL_SwapWindow() etc.)

        SDL_GL_SwapWindow(Window);
    }


        std::cout << "libgit2: Shutting down\n";
        git_libgit2_shutdown();
        std::cout << "libgit2: Shut down\n";

ImGui_ImplOpenGL3_Shutdown();
ImGui_ImplSDL2_Shutdown();
ImGui::DestroyContext();
        {
            SDL_GL_DeleteContext(glcontext);
            SDL_DestroyWindow(Window);
            SDL_Quit();
        }
        return EXIT_SUCCESS;
}
