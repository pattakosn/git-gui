// clang-format off
#include "video_player.h"
#include <glad/gl.h>
#include <SDL.h>
#include <SDL_opengl.h>
extern "C" {
#include <libavformat/avformat.h>
}
#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_opengl3.h"
// clang-format on

bool load_video(const char* path) {
    // Load the video file using FFmpeg
    AVFormatContext* formatContext;
    avformat_open_input(&formatContext, path, NULL, NULL);
    avformat_find_stream_info(formatContext, NULL);

    // Create an OpenGL texture from the video frames
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, formatContext->streams[0]->codecpar->width, formatContext->streams[0]->codecpar->height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);

    // Draw the video in a Dear ImGui window
    ImGui::Begin("Video Player");
    ImGui::Image((void*)(intptr_t)texture, ImVec2(formatContext->streams[0]->codecpar->width, formatContext->streams[0]->codecpar->height));
    ImGui::End();
    glDeleteTextures(1, &texture);
    return true;
}
