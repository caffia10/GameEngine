#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include "ImGuiImpl.h"
#include "MainMenuBar.h"
#include "Console.h"

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

ImGuiContext* InitializeGUI(HWND const& windowHandle)
{
    IMGUI_CHECKVERSION();
    ImGuiContext* imGuiContext = ImGui::CreateContext();

    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    // Setup Platform/Renderer bindings
    ImGui_ImplWin32_Init(windowHandle);
    const char* glslVersion = "#version 450";
    ImGui_ImplOpenGL3_Init(glslVersion);

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

    ImVec2 const sceneWindow(sceneWindowWidth, sceneWindowHeight);

    ImGuiViewport* const viewport = ImGui::GetMainViewport();
    // Create a DockSpace node where any window can be docked
    ImGuiID dockspaceId = ImGui::DockSpaceOverViewport(viewport);
    if (createDocking)
    {
        createDocking = false;

        // Clear out existing layout
        ImGui::DockBuilderRemoveNode(dockspaceId);
        // Add empty node
        ImGuiID dockIdMain = ImGui::DockBuilderAddNode(dockspaceId, ImGuiDockNodeFlags_DockSpace);
        ImGui::DockBuilderSetNodeSize(dockIdMain, viewport->GetWorkSize());

        ImGuiID const dockIdBottom = ImGui::DockBuilderSplitNode(dockIdMain, ImGuiDir_Down, 0.20f, NULL, &dockIdMain);
        ImGui::DockBuilderSetNodeSize(dockIdBottom, ImVec2{ viewport->GetWorkSize().x, 300 });

        ImGuiID const dockIdLeft = ImGui::DockBuilderSplitNode(dockIdMain, ImGuiDir_Left, 0.20f, NULL, &dockIdMain);
        ImGui::DockBuilderSetNodeSize(dockIdLeft, ImVec2(200, 100));

        ImGuiID const dockIdRight = ImGui::DockBuilderSplitNode(dockIdMain, ImGuiDir_Right, 0.20f, NULL, &dockIdMain);
        ImGui::DockBuilderSetNodeSize(dockIdRight, ImVec2(300, 100));


        ImGui::DockBuilderFinish(dockspaceId);

        appLayout.dockIdLeft = dockIdLeft;
        appLayout.dockIdBottom = dockIdBottom;
        appLayout.dockIdMain = dockIdMain;
        appLayout.dockIdRight = dockIdRight;
    }
    else{
        static int count = 0;
        if (count == 0)
        {
            count++;
            UI_LOG(" Docking creation finished");
        }
    }

    ImGui::SetNextWindowDockID(appLayout.dockIdLeft, ImGuiCond_Once);
    if (ImGui::Begin("Scene Explorer"))
    {

    }
    ImGui::End();

    ImGui::SetNextWindowDockID(appLayout.dockIdMain, ImGuiCond_Once);
    if (ImGui::Begin("Scene"))
    {
        ImGui::Image((void*)renderedTexture, ImGui::GetWindowSize());
    }
    ImGui::End();

    ImGui::SetNextWindowDockID(appLayout.dockIdRight, ImGuiCond_Once);
    if (ImGui::Begin("Properties"))
    {
    }
    ImGui::End();

    DrawConsole(appLayout.dockIdBottom);

    // render dear imgui into screen
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
#endif