
#include <windows.h>
#include <strsafe.h>

HANDLE g_hStdout;


void Log(const char* format, ...)
{
	char buffer[2048];
	va_list args;
	va_start(args, format);

	StringCbVPrintfA(buffer, sizeof(buffer), format, args);
	OutputDebugStringA(buffer);

	DWORD bytesWritten;
	WriteFile(g_hStdout, buffer, (DWORD)strlen(buffer), &bytesWritten, nullptr);


	va_end(args);
}