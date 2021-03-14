#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include "ImGuiImpl.h"
#include "Console.cpp"
#include "MainMenuBar.cpp"

static i32 sceneWindowWidth;
static i32 sceneWindowHeight;
static bool createDocking = true;

struct Layout
{
    ImGuiID dockIdMain;
    ImGuiID dockIdLeft;
    ImGuiID dockIdBottom;
    ImGuiID dockIdRight;
} static appLayout;

inline void NewFrameGUI()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();
}
#endif