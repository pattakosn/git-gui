// clang-format off
#include "bottom_bar.h"
#include "imgui.h"
// clang-format on

void bottom_bar() {
    auto text_size = ImGui::CalcTextSize("FPS");
    auto toolbar_size_y = text_size.y + ImGui::GetStyle().FramePadding.y;
    ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(ImVec2(viewport->Pos.x, ImGui::GetIO().DisplaySize.y - 2.f * toolbar_size_y));  // ));  // menuBarHeight));
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