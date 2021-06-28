#ifndef CONSOLE_H
#define CONSOLE_h

#include "ImGuiImpl.h"

ImGuiTextBuffer  textBuffer;
// Index to lines offset. We maintain this with AddLog() calls.
ImVector<int>    lineOffsets;

#undef UI_LOG
#define UI_LOG(format, ...) UILog(format, __VA_ARGS__) 


void Clear()
{
    textBuffer.clear();
    lineOffsets.clear();
    lineOffsets.push_back(0);
}

#endif // CONSOLE_h