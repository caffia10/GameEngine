#ifndef IMGUI_IMPL_H
#define IMGUI_IMPL_H

#define IMGUI_IMPL_OPENGL_LOADER_CUSTOM "Engines/Renderer/OpenGL.h"
#include <imgui/imgui_impl_win32.cpp>
#include <imgui/imgui_impl_opengl3.cpp>
#include <imgui/imgui.h>
#include <imgui/imgui_internal.h>

#define UI_LOG(format, ...)
#endif