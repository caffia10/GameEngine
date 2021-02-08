#define IMGUI_IMPL_OPENGL_LOADER_CUSTOM "Engines/Renderer/OpenGL.h"
#include <imgui/imgui_impl_win32.cpp>
#include <imgui/imgui_impl_opengl3.cpp>
#include <imgui/imgui.h>
#include "MainMenuBar.h"

static i32 sceneWindowWidth;
static i32 sceneWindowHeight;

ImGuiContext* InitializeGUI(HWND const& windowHandle)
{
    IMGUI_CHECKVERSION();
    ImGuiContext* imGuiContext = ImGui::CreateContext();

    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

    // Setup Platform/Renderer bindings
    ImGui_ImplWin32_Init(windowHandle);
    const char* glslVersion = "#version 450";
    ImGui_ImplOpenGL3_Init(glslVersion);

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    sceneWindowWidth = 800;
    sceneWindowHeight = 400;

    return imGuiContext;
}


void NewFrameGUI()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();
}

void RenderGUI()
{
    RenderMainMenuBar();

    f32 const width = (f32)sceneWindowWidth;
    f32 const height = (f32)sceneWindowHeight;

    ImGui::SetNextWindowSize(ImVec2(width,height));
    ImGui::SetNextWindowPos(ImVec2(1110,20));
    ImGui::Begin("Game");
    ImGui::Image((void*)renderedTexture, ImVec2(width, height));
    ImGui::End();

    // render dear imgui into screen
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}