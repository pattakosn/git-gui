#windows fucker: choco install pkgconfiglite
find_package(PkgConfig REQUIRED)
pkg_check_modules(LIBGIT2 REQUIRED IMPORTED_TARGET libgit2)
#pkg_check_modules(LIBAV REQUIRED IMPORTED_TARGET libavformat)
 #   libavdevice
 #   libavfilter    
 #   libavcodec
 #   libswresample
 #   libswscale
 #   libavutil

find_package(OpenGL REQUIRED)
find_package(SDL2 CONFIG REQUIRED)
find_package(SDL2_image CONFIG REQUIRED)

add_library(glad glad/src/gl.c)
target_include_directories(glad PUBLIC glad/include)

add_library(stb_image stb/stb_image.cpp)
target_include_directories(glad PUBLIC stb)

set(IMGUI_SRC
    imgui/imgui.cpp imgui/imgui.h
    imgui/imgui_draw.cpp
    imgui/imgui_tables.cpp
    imgui/imgui_widgets.cpp
    imgui/imgui_demo.cpp
    imgui/backends/imgui_impl_sdl2.cpp imgui/backends/imgui_impl_sdl2.h
    imgui/backends/imgui_impl_opengl3.cpp imgui/backends/imgui_impl_opengl3.h
    imgui/misc/cpp/imgui_stdlib.cpp imgui/misc/cpp/imgui_stdlib.h
)

set(SOURCES
    bottom_bar.cpp bottom_bar.h
    draw.cpp draw.h
    git.cpp git.h
    imgui_spectrum.h
    initialization.cpp initialization.h
    main.cpp
    load_texture_from_file.cpp load_texture_from_file.h
    themes.cpp themes.h
    #  video_player.cpp video_player.h
)
add_executable(git-gui ${SOURCES} ${IMGUI_SRC})
target_include_directories(git-gui PRIVATE imgui imgui/backends imgui/misc/cpp)
target_link_libraries(git-gui
    PRIVATE
        glad
        stb_image
        OpenGL::GL
        $<TARGET_NAME_IF_EXISTS:SDL2::SDL2main>
        $<IF:$<TARGET_EXISTS:SDL2::SDL2>,SDL2::SDL2,SDL2::SDL2-static>
        $<IF:$<TARGET_EXISTS:SDL2_image::SDL2_image>,SDL2_image::SDL2_image,SDL2_image::SDL2_image-static>
        PkgConfig::LIBGIT2
    #    PkgConfig::LIBAV
)
target_compile_options(git-gui PRIVATE
  $<$<CXX_COMPILER_ID:MSVC>:/W4;/WX;/permissive->
  $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall;-Wextra;-Wpedantic;-Werror;$<$<CONFIG:Release>:-D_FORTIFY_SOURCE>>
)
