#ifndef MAIN_WINDOW_B
#define MAIN_WINDOW_B

#include "MainWindow.h"

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
#endif // MAIN_WINDOW_B