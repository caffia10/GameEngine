#ifndef MAIN_MENU_BAR_H
#define MAIN_MENU_BAR_H

#include "ImGuiImpl.h"

inline void RenderMainMenuBar()
{
    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::MenuItem("Save"))
            {
                // Save action
            }
            if (ImGui::MenuItem("Load"))
            {
                // Load action
            }
            ImGui::EndMenu();
        }

        ImGui::EndMainMenuBar();
    }

}
#endif // MAIN_MENU_BAR_H