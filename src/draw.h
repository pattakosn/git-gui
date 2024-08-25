#ifndef DRAW_H
#define DRAW_H
void graphics_initialize();
void graphics_shutdown();
int my_poll();
void my_imgui_loop_start();
void my_imgui_loop_end();
void menu_bar();
void tool_bar();
void property_panel();
void main_area();
void bottom_bar();
#endif