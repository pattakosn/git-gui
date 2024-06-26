#find_package(libgit2 CONFIG REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_check_modules(LIBGIT2 REQUIRED IMPORTED_TARGET libgit2)
#target_link_libraries(main PRIVATE PkgConfig::LIBGIT2)
#find_package(unofficial-libgit2 CONFIG REQUIRED)
#target_link_libraries(main PRIVATE unofficial::libgit2::libgit2)

find_package(OpenGL REQUIRED)
find_package(SDL2 CONFIG REQUIRED)
#find_package(SDL2_image REQUIRED)

add_library(glad glad/src/gl.c)
target_include_directories(glad PUBLIC glad/include)

add_library(stb_image stb/stb_image.cpp)
target_include_directories(glad PUBLIC stb)

set(IMGUI_SRC     imgui/imgui.cpp imgui/imgui.h
imgui/imgui_draw.cpp
imgui/imgui_tables.cpp
imgui/imgui_widgets.cpp
imgui/imgui_demo.cpp
imgui/backends/imgui_impl_sdl2.cpp imgui/backends/imgui_impl_sdl2.h
imgui/backends/imgui_impl_opengl3.cpp imgui/backends/imgui_impl_opengl3.h
imgui/misc/cpp/imgui_stdlib.cpp imgui/misc/cpp/imgui_stdlib.h
)
#add_library(imgui ${IMGUI_SRC})
#target_include_directories(imgui PUBLIC imgui imgui/backends imgui/misc/cpp)
#target_link_libraries(imgui
#    PUBLIC
##    $<TARGET_NAME_IF_EXISTS:SDL2::SDL2main>
#    $<IF:$<TARGET_EXISTS:SDL2::SDL2>,SDL2::SDL2,SDL2::SDL2-static>
##    OpenGL::GL
#)
#target_compile_definitions(imgui PUBLIC IMGUI_IMPL_OPENGL_LOADER_CUSTOM=<SDL_opengl.h>  GL_GLEXT_PROTOTYPES=1)


set(SOURCES git-gui.cpp my_git.cpp my_git.h draw.cpp draw.h)
add_executable(git-gui ${SOURCES} ${IMGUI_SRC})
target_include_directories(git-gui PRIVATE imgui imgui/backends imgui/misc/cpp)
target_link_libraries(git-gui
    PRIVATE
        unofficial::libgit2::libgit2
        #PkgConfig::LIBGIT2
        glad
        OpenGL::GL
        $<TARGET_NAME_IF_EXISTS:SDL2::SDL2main>
        $<IF:$<TARGET_EXISTS:SDL2::SDL2>,SDL2::SDL2,SDL2::SDL2-static>
        stb_image
)
