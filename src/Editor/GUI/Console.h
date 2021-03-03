#ifndef CONSOLE_H
#define CONSOLE_h

#include "ImGuiImpl.h"

ImGuiTextBuffer  textBuffer;
// Index to lines offset. We maintain this with AddLog() calls.
ImVector<int>    lineOffsets;

inline void DrawConsole(ImGuiID layoutId)
{
    ImGui::SetNextWindowDockID(layoutId, ImGuiCond_Once);
    if (ImGui::Begin("Console"))
    {
        //ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));
        char const* buf = textBuffer.begin();
        char const* bufEnd = textBuffer.end();
        for (int lineNro = 0; lineNro < lineOffsets.Size; lineNro++)
        {
            char const* lineStart = buf + lineOffsets[lineNro];
            char const* lineEnd = (lineNro + 1 < lineOffsets.Size) ? (buf + lineOffsets[lineNro + 1] - 1) : bufEnd;
            // TODO: Add filter text like demo
            ImGui::TextUnformatted(lineStart, lineEnd);
        }

    }
    ImGui::End();
}

#undef UI_LOG
#define UI_LOG(format, ...) UILog(format, __VA_ARGS__) 

inline void UILog(const char* fmt, ...)
{
    const u32 textSize = ArrayCount(fmt);
    int oldSize = textBuffer.size();
    va_list args;
    va_start(args, fmt);
    textBuffer.appendfv(fmt, args);
    va_end(args);
    lineOffsets.push_back(oldSize + 1);
    /*for (int newSize = textBuffer.size(); oldSize < newSize; oldSize++)
    {
        if (oldSize == textSize || textBuffer[oldSize] == '\n')
        {
            lineOffsets.push_back(oldSize + 1);
        }
    }*/
}




inline void Clear()
{
    textBuffer.clear();
    lineOffsets.clear();
    lineOffsets.push_back(0);
}

#endif // CONSOLE_h