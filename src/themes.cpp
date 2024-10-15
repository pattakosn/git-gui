// clang-format off
#include "themes.h"
#include "imgui.h"
#include "imgui_spectrum.h"
// clang-format on

bool show_theme_win = true;

void adobe_spectrum() {
    ImGuiStyle* style = &ImGui::GetStyle();
    style->GrabRounding = 4.0f;

    ImVec4* colors = style->Colors;
    using namespace ImGui;
    colors[ImGuiCol_Text] = ColorConvertU32ToFloat4(Spectrum::GRAY800);  // text on hovered controls is gray900
    colors[ImGuiCol_TextDisabled] = ImGui::ColorConvertU32ToFloat4(Spectrum::GRAY500);
    colors[ImGuiCol_WindowBg] = ColorConvertU32ToFloat4(Spectrum::GRAY100);
    colors[ImGuiCol_ChildBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    colors[ImGuiCol_PopupBg] = ColorConvertU32ToFloat4(Spectrum::GRAY50);  // not sure about this. Note: applies to tooltips too.
    colors[ImGuiCol_Border] = ColorConvertU32ToFloat4(Spectrum::GRAY300);
    colors[ImGuiCol_BorderShadow] = ColorConvertU32ToFloat4(Spectrum::Static::NONE);  // We don't want shadows. Ever.
    colors[ImGuiCol_FrameBg] = ColorConvertU32ToFloat4(Spectrum::GRAY75);             // this isnt right, spectrum does not do this, but it's a good fallback
    colors[ImGuiCol_FrameBgHovered] = ColorConvertU32ToFloat4(Spectrum::GRAY50);
    colors[ImGuiCol_FrameBgActive] = ColorConvertU32ToFloat4(Spectrum::GRAY200);
    colors[ImGuiCol_TitleBg] = ColorConvertU32ToFloat4(Spectrum::GRAY300);  // those titlebar values are totally made up, spectrum does not have this.
    colors[ImGuiCol_TitleBgActive] = ColorConvertU32ToFloat4(Spectrum::GRAY200);
    colors[ImGuiCol_TitleBgCollapsed] = ColorConvertU32ToFloat4(Spectrum::GRAY400);
    colors[ImGuiCol_MenuBarBg] = ColorConvertU32ToFloat4(Spectrum::GRAY100);
    colors[ImGuiCol_ScrollbarBg] = ColorConvertU32ToFloat4(Spectrum::GRAY100);  // same as regular background
    colors[ImGuiCol_ScrollbarGrab] = ColorConvertU32ToFloat4(Spectrum::GRAY400);
    colors[ImGuiCol_ScrollbarGrabHovered] = ColorConvertU32ToFloat4(Spectrum::GRAY600);
    colors[ImGuiCol_ScrollbarGrabActive] = ColorConvertU32ToFloat4(Spectrum::GRAY700);
    colors[ImGuiCol_CheckMark] = ColorConvertU32ToFloat4(Spectrum::BLUE500);
    colors[ImGuiCol_SliderGrab] = ColorConvertU32ToFloat4(Spectrum::GRAY700);
    colors[ImGuiCol_SliderGrabActive] = ColorConvertU32ToFloat4(Spectrum::GRAY800);
    colors[ImGuiCol_Button] = ColorConvertU32ToFloat4(Spectrum::GRAY75);  // match default button to Spectrum's 'Action Button'.
    colors[ImGuiCol_ButtonHovered] = ColorConvertU32ToFloat4(Spectrum::GRAY50);
    colors[ImGuiCol_ButtonActive] = ColorConvertU32ToFloat4(Spectrum::GRAY200);
    colors[ImGuiCol_Header] = ColorConvertU32ToFloat4(Spectrum::BLUE400);
    colors[ImGuiCol_HeaderHovered] = ColorConvertU32ToFloat4(Spectrum::BLUE500);
    colors[ImGuiCol_HeaderActive] = ColorConvertU32ToFloat4(Spectrum::BLUE600);
    colors[ImGuiCol_Separator] = ColorConvertU32ToFloat4(Spectrum::GRAY400);
    colors[ImGuiCol_SeparatorHovered] = ColorConvertU32ToFloat4(Spectrum::GRAY600);
    colors[ImGuiCol_SeparatorActive] = ColorConvertU32ToFloat4(Spectrum::GRAY700);
    colors[ImGuiCol_ResizeGrip] = ColorConvertU32ToFloat4(Spectrum::GRAY400);
    colors[ImGuiCol_ResizeGripHovered] = ColorConvertU32ToFloat4(Spectrum::GRAY600);
    colors[ImGuiCol_ResizeGripActive] = ColorConvertU32ToFloat4(Spectrum::GRAY700);
    colors[ImGuiCol_PlotLines] = ColorConvertU32ToFloat4(Spectrum::BLUE400);
    colors[ImGuiCol_PlotLinesHovered] = ColorConvertU32ToFloat4(Spectrum::BLUE600);
    colors[ImGuiCol_PlotHistogram] = ColorConvertU32ToFloat4(Spectrum::BLUE400);
    colors[ImGuiCol_PlotHistogramHovered] = ColorConvertU32ToFloat4(Spectrum::BLUE600);
    colors[ImGuiCol_TextSelectedBg] = ColorConvertU32ToFloat4((Spectrum::BLUE400 & 0x00FFFFFF) | 0x33000000);
    colors[ImGuiCol_DragDropTarget] = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
    colors[ImGuiCol_NavHighlight] = ColorConvertU32ToFloat4((Spectrum::GRAY900 & 0x00FFFFFF) | 0x0A000000);
    colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
    colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
    colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.20f, 0.20f, 0.20f, 0.35f);
}

void purple() {
    // This work is licensed under the CC0 1.0 Universal (CC0 1.0) Public Domain Dedication.
    ImVec4* colors = ImGui::GetStyle().Colors;
    colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
    colors[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
    colors[ImGuiCol_WindowBg] = ImVec4(0.02f, 0.01f, 0.02f, 0.94f);
    colors[ImGuiCol_ChildBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    colors[ImGuiCol_PopupBg] = ImVec4(0.08f, 0.08f, 0.08f, 0.94f);
    colors[ImGuiCol_Border] = ImVec4(0.71f, 0.60f, 0.91f, 0.33f);
    colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    colors[ImGuiCol_FrameBg] = ImVec4(0.10f, 0.07f, 0.12f, 0.89f);
    colors[ImGuiCol_FrameBgHovered] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
    colors[ImGuiCol_FrameBgActive] = ImVec4(0.29f, 0.28f, 0.34f, 0.94f);
    colors[ImGuiCol_TitleBg] = ImVec4(0.04f, 0.04f, 0.04f, 1.00f);
    colors[ImGuiCol_TitleBgActive] = ImVec4(0.41f, 0.18f, 0.56f, 1.00f);
    colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 0.51f);
    colors[ImGuiCol_MenuBarBg] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
    colors[ImGuiCol_ScrollbarBg] = ImVec4(0.02f, 0.02f, 0.02f, 0.53f);
    colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.31f, 0.31f, 0.31f, 1.00f);
    colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.41f, 0.41f, 0.41f, 1.00f);
    colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.51f, 0.51f, 0.51f, 1.00f);
    colors[ImGuiCol_CheckMark] = ImVec4(0.60f, 0.20f, 0.87f, 1.00f);
    colors[ImGuiCol_SliderGrab] = ImVec4(0.65f, 0.24f, 0.88f, 1.00f);
    colors[ImGuiCol_SliderGrabActive] = ImVec4(0.88f, 0.06f, 0.47f, 1.00f);
    colors[ImGuiCol_Button] = ImVec4(0.86f, 0.18f, 0.61f, 0.40f);
    colors[ImGuiCol_ButtonHovered] = ImVec4(0.76f, 0.21f, 0.74f, 1.00f);
    colors[ImGuiCol_ButtonActive] = ImVec4(0.40f, 0.10f, 0.52f, 1.00f);
    colors[ImGuiCol_Header] = ImVec4(0.97f, 0.21f, 0.49f, 0.31f);
    colors[ImGuiCol_HeaderHovered] = ImVec4(0.87f, 0.37f, 0.65f, 0.80f);
    colors[ImGuiCol_HeaderActive] = ImVec4(0.78f, 0.10f, 0.30f, 1.00f);
    colors[ImGuiCol_Separator] = ImVec4(0.25f, 0.18f, 0.86f, 0.50f);
    colors[ImGuiCol_SeparatorHovered] = ImVec4(0.42f, 0.13f, 0.69f, 0.78f);
    colors[ImGuiCol_SeparatorActive] = ImVec4(0.55f, 0.04f, 0.80f, 1.00f);
    colors[ImGuiCol_ResizeGrip] = ImVec4(0.78f, 0.50f, 0.87f, 0.20f);
    colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.54f, 0.14f, 0.92f, 0.67f);
    colors[ImGuiCol_ResizeGripActive] = ImVec4(0.51f, 0.04f, 0.86f, 0.95f);
    colors[ImGuiCol_Tab] = ImVec4(0.23f, 0.13f, 0.40f, 0.86f);
    colors[ImGuiCol_TabHovered] = ImVec4(0.45f, 0.23f, 0.86f, 0.80f);
    colors[ImGuiCol_TabActive] = ImVec4(0.30f, 0.17f, 0.76f, 1.00f);
    colors[ImGuiCol_TabUnfocused] = ImVec4(0.07f, 0.10f, 0.15f, 0.97f);
    colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.14f, 0.26f, 0.42f, 1.00f);
    colors[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
    colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
    colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
    colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
    colors[ImGuiCol_TableHeaderBg] = ImVec4(0.19f, 0.19f, 0.20f, 1.00f);
    colors[ImGuiCol_TableBorderStrong] = ImVec4(0.31f, 0.31f, 0.35f, 1.00f);
    colors[ImGuiCol_TableBorderLight] = ImVec4(0.23f, 0.23f, 0.25f, 1.00f);
    colors[ImGuiCol_TableRowBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    colors[ImGuiCol_TableRowBgAlt] = ImVec4(1.00f, 1.00f, 1.00f, 0.06f);
    colors[ImGuiCol_TextSelectedBg] = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
    colors[ImGuiCol_DragDropTarget] = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
    colors[ImGuiCol_NavHighlight] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
    colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
    colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
    colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);
}
void maksasj() {
    ImGuiStyle& style = ImGui::GetStyle();
    style.WindowRounding = 5.3f;
    style.FrameRounding = 2.3f;
    style.ScrollbarRounding = 0;

    style.Colors[ImGuiCol_Text] = ImVec4(0.90f, 0.90f, 0.90f, 0.90f);
    style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.60f, 0.60f, 0.60f, 1.00f);
    style.Colors[ImGuiCol_WindowBg] = ImVec4(0.09f, 0.09f, 0.15f, 1.00f);
    style.Colors[ImGuiCol_ChildBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    style.Colors[ImGuiCol_PopupBg] = ImVec4(0.05f, 0.05f, 0.10f, 0.85f);
    style.Colors[ImGuiCol_Border] = ImVec4(0.70f, 0.70f, 0.70f, 0.65f);
    style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    style.Colors[ImGuiCol_FrameBg] = ImVec4(0.00f, 0.00f, 0.01f, 1.00f);
    style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.90f, 0.80f, 0.80f, 0.40f);
    style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.90f, 0.65f, 0.65f, 0.45f);
    style.Colors[ImGuiCol_TitleBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.83f);
    style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.40f, 0.40f, 0.80f, 0.20f);
    style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.00f, 0.00f, 0.00f, 0.87f);
    style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.01f, 0.01f, 0.02f, 0.80f);
    style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.20f, 0.25f, 0.30f, 0.60f);
    style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.55f, 0.53f, 0.55f, 0.51f);
    style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.56f, 0.56f, 0.56f, 1.00f);
    style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.56f, 0.56f, 0.56f, 0.91f);
    style.Colors[ImGuiCol_CheckMark] = ImVec4(0.90f, 0.90f, 0.90f, 0.83f);
    style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.70f, 0.70f, 0.70f, 0.62f);
    style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.30f, 0.30f, 0.30f, 0.84f);
    style.Colors[ImGuiCol_Button] = ImVec4(0.48f, 0.72f, 0.89f, 0.49f);
    style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.50f, 0.69f, 0.99f, 0.68f);
    style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.80f, 0.50f, 0.50f, 1.00f);
    style.Colors[ImGuiCol_Header] = ImVec4(0.30f, 0.69f, 1.00f, 0.53f);
    style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.44f, 0.61f, 0.86f, 1.00f);
    style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.38f, 0.62f, 0.83f, 1.00f);
    style.Colors[ImGuiCol_Separator] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
    style.Colors[ImGuiCol_SeparatorHovered] = ImVec4(0.70f, 0.60f, 0.60f, 1.00f);
    style.Colors[ImGuiCol_SeparatorActive] = ImVec4(0.90f, 0.70f, 0.70f, 1.00f);
    style.Colors[ImGuiCol_ResizeGrip] = ImVec4(1.00f, 1.00f, 1.00f, 0.85f);
    style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(1.00f, 1.00f, 1.00f, 0.60f);
    style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(1.00f, 1.00f, 1.00f, 0.90f);
    style.Colors[ImGuiCol_PlotLines] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
    style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
    style.Colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
    style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
    style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.00f, 0.00f, 1.00f, 0.35f);
    style.Colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.20f, 0.20f, 0.20f, 0.35f);
}
void dracula() {
    auto& colors = ImGui::GetStyle().Colors;
    colors[ImGuiCol_WindowBg] = ImVec4{0.1f, 0.1f, 0.13f, 1.0f};
    colors[ImGuiCol_MenuBarBg] = ImVec4{0.16f, 0.16f, 0.21f, 1.0f};

    // Border
    colors[ImGuiCol_Border] = ImVec4{0.44f, 0.37f, 0.61f, 0.29f};
    colors[ImGuiCol_BorderShadow] = ImVec4{0.0f, 0.0f, 0.0f, 0.24f};

    // Text
    colors[ImGuiCol_Text] = ImVec4{1.0f, 1.0f, 1.0f, 1.0f};
    colors[ImGuiCol_TextDisabled] = ImVec4{0.5f, 0.5f, 0.5f, 1.0f};

    // Headers
    colors[ImGuiCol_Header] = ImVec4{0.13f, 0.13f, 0.17f, 1.0f};
    colors[ImGuiCol_HeaderHovered] = ImVec4{0.19f, 0.2f, 0.25f, 1.0f};
    colors[ImGuiCol_HeaderActive] = ImVec4{0.16f, 0.16f, 0.21f, 1.0f};

    // Buttons
    colors[ImGuiCol_Button] = ImVec4{0.13f, 0.13f, 0.17f, 1.0f};
    colors[ImGuiCol_ButtonHovered] = ImVec4{0.19f, 0.2f, 0.25f, 1.0f};
    colors[ImGuiCol_ButtonActive] = ImVec4{0.16f, 0.16f, 0.21f, 1.0f};
    colors[ImGuiCol_CheckMark] = ImVec4{0.74f, 0.58f, 0.98f, 1.0f};

    // Popups
    colors[ImGuiCol_PopupBg] = ImVec4{0.1f, 0.1f, 0.13f, 0.92f};

    // Slider
    colors[ImGuiCol_SliderGrab] = ImVec4{0.44f, 0.37f, 0.61f, 0.54f};
    colors[ImGuiCol_SliderGrabActive] = ImVec4{0.74f, 0.58f, 0.98f, 0.54f};

    // Frame BG
    colors[ImGuiCol_FrameBg] = ImVec4{0.13f, 0.13f, 0.17f, 1.0f};
    colors[ImGuiCol_FrameBgHovered] = ImVec4{0.19f, 0.2f, 0.25f, 1.0f};
    colors[ImGuiCol_FrameBgActive] = ImVec4{0.16f, 0.16f, 0.21f, 1.0f};

    // Tabs
    colors[ImGuiCol_Tab] = ImVec4{0.16f, 0.16f, 0.21f, 1.0f};
    colors[ImGuiCol_TabHovered] = ImVec4{0.24f, 0.24f, 0.32f, 1.0f};
    colors[ImGuiCol_TabActive] = ImVec4{0.2f, 0.22f, 0.27f, 1.0f};
    colors[ImGuiCol_TabUnfocused] = ImVec4{0.16f, 0.16f, 0.21f, 1.0f};
    colors[ImGuiCol_TabUnfocusedActive] = ImVec4{0.16f, 0.16f, 0.21f, 1.0f};

    // Title
    colors[ImGuiCol_TitleBg] = ImVec4{0.16f, 0.16f, 0.21f, 1.0f};
    colors[ImGuiCol_TitleBgActive] = ImVec4{0.16f, 0.16f, 0.21f, 1.0f};
    colors[ImGuiCol_TitleBgCollapsed] = ImVec4{0.16f, 0.16f, 0.21f, 1.0f};

    // Scrollbar
    colors[ImGuiCol_ScrollbarBg] = ImVec4{0.1f, 0.1f, 0.13f, 1.0f};
    colors[ImGuiCol_ScrollbarGrab] = ImVec4{0.16f, 0.16f, 0.21f, 1.0f};
    colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4{0.19f, 0.2f, 0.25f, 1.0f};
    colors[ImGuiCol_ScrollbarGrabActive] = ImVec4{0.24f, 0.24f, 0.32f, 1.0f};

    // Seperator
    colors[ImGuiCol_Separator] = ImVec4{0.44f, 0.37f, 0.61f, 1.0f};
    colors[ImGuiCol_SeparatorHovered] = ImVec4{0.74f, 0.58f, 0.98f, 1.0f};
    colors[ImGuiCol_SeparatorActive] = ImVec4{0.84f, 0.58f, 1.0f, 1.0f};

    // Resize Grip
    colors[ImGuiCol_ResizeGrip] = ImVec4{0.44f, 0.37f, 0.61f, 0.29f};
    colors[ImGuiCol_ResizeGripHovered] = ImVec4{0.74f, 0.58f, 0.98f, 0.29f};
    colors[ImGuiCol_ResizeGripActive] = ImVec4{0.84f, 0.58f, 1.0f, 0.29f};

    // Docking
    colors[ImGuiCol_DockingPreview] = ImVec4{0.44f, 0.37f, 0.61f, 1.0f};

    auto& style = ImGui::GetStyle();
    style.TabRounding = 4;
    style.ScrollbarRounding = 9;
    style.WindowRounding = 7;
    style.GrabRounding = 3;
    style.FrameRounding = 3;
    style.PopupRounding = 4;
    style.ChildRounding = 4;
}
// void blue_hydrangea() {
//     ImGuiStyle& style = ImGui::GetStyle();
//     // inner windows
//     style.window_border_size = 1.0;
//     style.window_rounding = 4.0;
//     // controls
//     style.frame_rounding = 4.0;
//     // non-modal popups (used for confirmation in this example)
//     style.popup_border_size = 1.0;
//     style.popup_rounding = 4.0;
//
//     // theme colors -- "blue hydrangea"
//     // you can easily generate these values via the built in
//     // file > Toggle Style Editor command in this example.
//     // there are also many in this issue on the C++ imgui
//     // repo: https://github.com/ocornut/imgui/issues/707
//     style.colors[StyleColor::Text as usize] = [1.00, 1.00, 1.00, 1.00];
//     style.colors[StyleColor::TextDisabled as usize] = [0.50, 0.50, 0.50, 1.00];
//     style.colors[StyleColor::WindowBg as usize] = [0.03, 0.07, 0.04, 0.94];
//     style.colors[StyleColor::ChildBg as usize] = [0.00, 0.00, 0.00, 0.00];
//     style.colors[StyleColor::PopupBg as usize] = [0.08, 0.08, 0.08, 0.94];
//     style.colors[StyleColor::Border as usize] = [0.38, 1.00, 0.00, 0.50];
//     style.colors[StyleColor::BorderShadow as usize] = [0.01, 0.13, 0.00, 0.63];
//     style.colors[StyleColor::FrameBg as usize] = [0.17, 0.48, 0.16, 0.54];
//     style.colors[StyleColor::FrameBgHovered as usize] = [0.26, 0.98, 0.32, 0.40];
//     style.colors[StyleColor::FrameBgActive as usize] = [0.26, 0.98, 0.28, 0.67];
//     style.colors[StyleColor::TitleBg as usize] = [0.01, 0.07, 0.01, 1.00];
//     style.colors[StyleColor::TitleBgActive as usize] = [0.0, 0.29, 0.68, 1.0];
//     style.colors[StyleColor::TitleBgCollapsed as usize] = [0.00, 0.56, 0.09, 0.51];
//     style.colors[StyleColor::MenuBarBg as usize] = [0.0, 0.29, 0.68, 1.0];
//     style.colors[StyleColor::ScrollbarBg as usize] = [0.00, 0.15, 0.00, 0.53];
//     style.colors[StyleColor::ScrollbarGrab as usize] = [0.10, 0.41, 0.06, 1.00];
//     style.colors[StyleColor::ScrollbarGrabHovered as usize] = [0.00, 0.66, 0.04, 1.00];
//     style.colors[StyleColor::ScrollbarGrabActive as usize] = [0.04, 0.87, 0.00, 1.00];
//     style.colors[StyleColor::CheckMark as usize] = [0.26, 0.98, 0.40, 1.00];
//     style.colors[StyleColor::SliderGrab as usize] = [0.21, 0.61, 0.00, 1.00];
//     style.colors[StyleColor::SliderGrabActive as usize] = [0.36, 0.87, 0.22, 1.00];
//     style.colors[StyleColor::Button as usize] = [0.00, 0.60, 0.05, 0.40];
//     style.colors[StyleColor::ButtonHovered as usize] = [0.20, 0.78, 0.32, 1.00];
//     style.colors[StyleColor::ButtonActive as usize] = [0.00, 0.57, 0.07, 1.00];
//     style.colors[StyleColor::Header as usize] = [0.12, 0.82, 0.28, 0.31];
//     style.colors[StyleColor::HeaderHovered as usize] = [0.00, 0.74, 0.11, 0.80];
//     style.colors[StyleColor::HeaderActive as usize] = [0.09, 0.69, 0.04, 1.00];
//     style.colors[StyleColor::Separator as usize] = [0.09, 0.67, 0.01, 0.50];
//     style.colors[StyleColor::SeparatorHovered as usize] = [0.32, 0.75, 0.10, 0.78];
//     style.colors[StyleColor::SeparatorActive as usize] = [0.10, 0.75, 0.11, 1.00];
//     style.colors[StyleColor::ResizeGrip as usize] = [0.32, 0.98, 0.26, 0.20];
//     style.colors[StyleColor::ResizeGripHovered as usize] = [0.26, 0.98, 0.28, 0.67];
//     style.colors[StyleColor::ResizeGripActive as usize] = [0.22, 0.69, 0.06, 0.95];
//     style.colors[StyleColor::Tab as usize] = [0.18, 0.58, 0.18, 0.86];
//     style.colors[StyleColor::TabHovered as usize] = [0.26, 0.98, 0.28, 0.80];
//     style.colors[StyleColor::TabActive as usize] = [0.20, 0.68, 0.24, 1.00];
//     style.colors[StyleColor::TabUnfocused as usize] = [0.07, 0.15, 0.08, 0.97];
//     style.colors[StyleColor::TabUnfocusedActive as usize] = [0.14, 0.42, 0.19, 1.00];
//     style.colors[StyleColor::PlotLines as usize] = [0.61, 0.61, 0.61, 1.00];
//     style.colors[StyleColor::PlotLinesHovered as usize] = [1.00, 0.43, 0.35, 1.00];
//     style.colors[StyleColor::PlotHistogram as usize] = [0.90, 0.70, 0.00, 1.00];
//     style.colors[StyleColor::PlotHistogramHovered as usize] = [1.00, 0.60, 0.00, 1.00];
//     style.colors[StyleColor::TableHeaderBg as usize] = [0.19, 0.19, 0.20, 1.00];
//     style.colors[StyleColor::TableBorderStrong as usize] = [0.31, 0.31, 0.35, 1.00];
//     style.colors[StyleColor::TableBorderLight as usize] = [0.23, 0.23, 0.25, 1.00];
//     style.colors[StyleColor::TableRowBg as usize] = [0.00, 0.00, 0.00, 0.00];
//     style.colors[StyleColor::TableRowBgAlt as usize] = [1.00, 1.00, 1.00, 0.06];
//     style.colors[StyleColor::TextSelectedBg as usize] = [0.00, 0.89, 0.20, 0.35];
//     style.colors[StyleColor::DragDropTarget as usize] = [1.00, 1.00, 0.00, 0.90];
////    style.colors[StyleColor::NavHighlight as usize] = [0.26, 0.98, 0.35, 1.00];
////    style.colors[StyleColor::NavWindowingHighlight as usize] = [1.00, 1.00, 1.00, 0.70];
////    style.colors[StyleColor::NavWindowingDimBg as usize] = [0.80, 0.80, 0.80, 0.20];
////    style.colors[StyleColor::ModalWindowDimBg as usize] = [0.80, 0.80, 0.80, 0.35];
////}
// void old_software(){
//     ImGuiStyle& style = ImGui::GetStyle();
// style.Colors[ImGuiCol_Text] = ImVec4(0.31f, 0.25f, 0.24f, 1.00f);
// style.Colors[ImGuiCol_WindowBg] = ImVec4(0.94f, 0.94f, 0.94f, 1.00f);
// style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.74f, 0.74f, 0.94f, 1.00f);
// style.Colors[ImGuiCol_ChildWindowBg] = ImVec4(0.68f, 0.68f, 0.68f, 0.00f);
// style.Colors[ImGuiCol_Border] = ImVec4(0.50f, 0.50f, 0.50f, 0.60f);
// style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
// style.Colors[ImGuiCol_FrameBg] = ImVec4(0.62f, 0.70f, 0.72f, 0.56f);
// style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.95f, 0.33f, 0.14f, 0.47f);
// style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.97f, 0.31f, 0.13f, 0.81f);
// style.Colors[ImGuiCol_TitleBg] = ImVec4(0.42f, 0.75f, 1.00f, 0.53f);
// style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.40f, 0.65f, 0.80f, 0.20f);
// style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.40f, 0.62f, 0.80f, 0.15f);
// style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.39f, 0.64f, 0.80f, 0.30f);
// style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.28f, 0.67f, 0.80f, 0.59f);
// style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.25f, 0.48f, 0.53f, 0.67f);
// style.Colors[ImGuiCol_ComboBg] = ImVec4(0.89f, 0.98f, 1.00f, 0.99f);
// style.Colors[ImGuiCol_CheckMark] = ImVec4(0.48f, 0.47f, 0.47f, 0.71f);
// style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.31f, 0.47f, 0.99f, 1.00f);
// style.Colors[ImGuiCol_Button] = ImVec4(1.00f, 0.79f, 0.18f, 0.78f);
// style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.42f, 0.82f, 1.00f, 0.81f);
// style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.72f, 1.00f, 1.00f, 0.86f);
// style.Colors[ImGuiCol_Header] = ImVec4(0.65f, 0.78f, 0.84f, 0.80f);
// style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.75f, 0.88f, 0.94f, 0.80f);
// style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.55f, 0.68f, 0.74f, 0.80f);//ImVec4(0.46f, 0.84f, 0.90f, 1.00f);
// style.Colors[ImGuiCol_ResizeGrip] = ImVec4(0.60f, 0.60f, 0.80f, 0.30f);
// style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(1.00f, 1.00f, 1.00f, 0.60f);
// style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(1.00f, 1.00f, 1.00f, 0.90f);
// style.Colors[ImGuiCol_CloseButton] = ImVec4(0.41f, 0.75f, 0.98f, 0.50f);
// style.Colors[ImGuiCol_CloseButtonHovered] = ImVec4(1.00f, 0.47f, 0.41f, 0.60f);
// style.Colors[ImGuiCol_CloseButtonActive] = ImVec4(1.00f, 0.16f, 0.00f, 1.00f);
// style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(1.00f, 0.99f, 0.54f, 0.43f);
// style.Colors[ImGuiCol_TooltipBg] = ImVec4(0.82f, 0.92f, 1.00f, 0.90f);
// style.Alpha = 1.0f;
// style.WindowFillAlphaDefault = 1.0f;
////style.FrameRounding = 4;
////style.IndentSpacing = 12.0f;
////}
// void blue(){
//     // From https://github.com/procedural/gpulib/blob/master/gpulib_imgui.h
// struct ImVec3 { float x, y, z; ImVec3(float _x = 0.0f, float _y = 0.0f, float _z = 0.0f) { x = _x; y = _y; z = _z; } };
//
// void imgui_easy_theming(ImVec3 color_for_text, ImVec3 color_for_head, ImVec3 color_for_area, ImVec3 color_for_body, ImVec3 color_for_pops)
//{
//     ImGuiStyle& style = ImGui::GetStyle();
//
//     style.Colors[ImGuiCol_Text] = ImVec4( color_for_text.x, color_for_text.y, color_for_text.z, 1.00f );
//     style.Colors[ImGuiCol_TextDisabled] = ImVec4( color_for_text.x, color_for_text.y, color_for_text.z, 0.58f );
//     style.Colors[ImGuiCol_WindowBg] = ImVec4( color_for_body.x, color_for_body.y, color_for_body.z, 0.95f );
//     style.Colors[ImGuiCol_ChildWindowBg] = ImVec4( color_for_area.x, color_for_area.y, color_for_area.z, 0.58f );
//     style.Colors[ImGuiCol_Border] = ImVec4( color_for_body.x, color_for_body.y, color_for_body.z, 0.00f );
//     style.Colors[ImGuiCol_BorderShadow] = ImVec4( color_for_body.x, color_for_body.y, color_for_body.z, 0.00f );
//     style.Colors[ImGuiCol_FrameBg] = ImVec4( color_for_area.x, color_for_area.y, color_for_area.z, 1.00f );
//     style.Colors[ImGuiCol_FrameBgHovered] = ImVec4( color_for_head.x, color_for_head.y, color_for_head.z, 0.78f );
//     style.Colors[ImGuiCol_FrameBgActive] = ImVec4( color_for_head.x, color_for_head.y, color_for_head.z, 1.00f );
//     style.Colors[ImGuiCol_TitleBg] = ImVec4( color_for_area.x, color_for_area.y, color_for_area.z, 1.00f );
//     style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4( color_for_area.x, color_for_area.y, color_for_area.z, 0.75f );
//     style.Colors[ImGuiCol_TitleBgActive] = ImVec4( color_for_head.x, color_for_head.y, color_for_head.z, 1.00f );
//     style.Colors[ImGuiCol_MenuBarBg] = ImVec4( color_for_area.x, color_for_area.y, color_for_area.z, 0.47f );
//     style.Colors[ImGuiCol_ScrollbarBg] = ImVec4( color_for_area.x, color_for_area.y, color_for_area.z, 1.00f );
//     style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4( color_for_head.x, color_for_head.y, color_for_head.z, 0.21f );
//     style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4( color_for_head.x, color_for_head.y, color_for_head.z, 0.78f );
//     style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4( color_for_head.x, color_for_head.y, color_for_head.z, 1.00f );
//     style.Colors[ImGuiCol_ComboBg] = ImVec4( color_for_area.x, color_for_area.y, color_for_area.z, 1.00f );
//     style.Colors[ImGuiCol_CheckMark] = ImVec4( color_for_head.x, color_for_head.y, color_for_head.z, 0.80f );
//     style.Colors[ImGuiCol_SliderGrab] = ImVec4( color_for_head.x, color_for_head.y, color_for_head.z, 0.50f );
//     style.Colors[ImGuiCol_SliderGrabActive] = ImVec4( color_for_head.x, color_for_head.y, color_for_head.z, 1.00f );
//     style.Colors[ImGuiCol_Button] = ImVec4( color_for_head.x, color_for_head.y, color_for_head.z, 0.50f );
//     style.Colors[ImGuiCol_ButtonHovered] = ImVec4( color_for_head.x, color_for_head.y, color_for_head.z, 0.86f );
//     style.Colors[ImGuiCol_ButtonActive] = ImVec4( color_for_head.x, color_for_head.y, color_for_head.z, 1.00f );
//     style.Colors[ImGuiCol_Header] = ImVec4( color_for_head.x, color_for_head.y, color_for_head.z, 0.76f );
//     style.Colors[ImGuiCol_HeaderHovered] = ImVec4( color_for_head.x, color_for_head.y, color_for_head.z, 0.86f );
//     style.Colors[ImGuiCol_HeaderActive] = ImVec4( color_for_head.x, color_for_head.y, color_for_head.z, 1.00f );
//     style.Colors[ImGuiCol_Column] = ImVec4( color_for_head.x, color_for_head.y, color_for_head.z, 0.32f );
//     style.Colors[ImGuiCol_ColumnHovered] = ImVec4( color_for_head.x, color_for_head.y, color_for_head.z, 0.78f );
//     style.Colors[ImGuiCol_ColumnActive] = ImVec4( color_for_head.x, color_for_head.y, color_for_head.z, 1.00f );
//     style.Colors[ImGuiCol_ResizeGrip] = ImVec4( color_for_head.x, color_for_head.y, color_for_head.z, 0.15f );
//     style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4( color_for_head.x, color_for_head.y, color_for_head.z, 0.78f );
//     style.Colors[ImGuiCol_ResizeGripActive] = ImVec4( color_for_head.x, color_for_head.y, color_for_head.z, 1.00f );
//     style.Colors[ImGuiCol_CloseButton] = ImVec4( color_for_text.x, color_for_text.y, color_for_text.z, 0.16f );
//     style.Colors[ImGuiCol_CloseButtonHovered] = ImVec4( color_for_text.x, color_for_text.y, color_for_text.z, 0.39f );
//     style.Colors[ImGuiCol_CloseButtonActive] = ImVec4( color_for_text.x, color_for_text.y, color_for_text.z, 1.00f );
//     style.Colors[ImGuiCol_PlotLines] = ImVec4( color_for_text.x, color_for_text.y, color_for_text.z, 0.63f );
//     style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4( color_for_head.x, color_for_head.y, color_for_head.z, 1.00f );
//     style.Colors[ImGuiCol_PlotHistogram] = ImVec4( color_for_text.x, color_for_text.y, color_for_text.z, 0.63f );
//     style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4( color_for_head.x, color_for_head.y, color_for_head.z, 1.00f );
//     style.Colors[ImGuiCol_TextSelectedBg] = ImVec4( color_for_head.x, color_for_head.y, color_for_head.z, 0.43f );
//     style.Colors[ImGuiCol_PopupBg] = ImVec4( color_for_pops.x, color_for_pops.y, color_for_pops.z, 0.92f );
//     style.Colors[ImGuiCol_ModalWindowDarkening] = ImVec4( color_for_area.x, color_for_area.y, color_for_area.z, 0.73f );
// }
// void ImGuiEx::SetupImGuiStyle2()
//{
//     static ImVec3 color_for_text = ImVec3(236.f / 255.f, 240.f / 255.f, 241.f / 255.f);
//     static ImVec3 color_for_head = ImVec3(41.f / 255.f, 128.f / 255.f, 185.f / 255.f);
//     static ImVec3 color_for_area = ImVec3(57.f / 255.f, 79.f / 255.f, 105.f / 255.f);
//     static ImVec3 color_for_body = ImVec3(44.f / 255.f, 62.f / 255.f, 80.f / 255.f);
//     static ImVec3 color_for_pops = ImVec3(33.f / 255.f, 46.f / 255.f, 60.f / 255.f);
//     imgui_easy_theming(color_for_text, color_for_head, color_for_area, color_for_body, color_for_pops);
// }
// }

void Themes() {
    static int theme_choice{0};

    if (ImGui::Begin("Theme selector", &show_theme_win)) {  //}, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse)) {
        ImGui::RadioButton("Default", &theme_choice, 0);             // ImGui::SameLine();
        ImGui::RadioButton("Adobe spectrum", &theme_choice, 1);
        ImGui::RadioButton("Purple", &theme_choice, 2);
        ImGui::RadioButton("Maksasj", &theme_choice, 3);
        ImGui::RadioButton("Dracula", &theme_choice, 4);
        //   ImGui::RadioButton("Blue Hydrangea", &num, 5);
    }
    ImGui::End();
    switch (theme_choice) {
        case 0:
            ImGui::GetStyle() = ImGuiStyle();
            break;
        case 1:
            adobe_spectrum();
            break;
        case 2:
            purple();
            break;
        case 3:
            maksasj();
            break;
        case 4:
            dracula();
            break;
            //        case 5:
            //           blue_hydrangea();
            //         break;
    }
}