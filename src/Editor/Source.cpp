#include <Windows.h>
#include <GL/gl.h>
#include <GLES3/gl32.h>
#include <GLES3/glext.h>
#include <GLES3/wglext.h>
#include <GLES3/glcorearb.h>
#include "Common/Common.h"
#include "Maths/MathDef.h"
#include "Engines/Renderer/OpenGL.h"
#include "Engines/Renderer/OpenGL.cpp"
#include "Engines/Renderer/OpenGLRender.cpp"
#include "Common/WindowsCommon.h"
#include "Editor/GUI/MainWindow.cpp"


const i32 WIDTH = 1920;
const i32 HEIGHT = 1080;

bool isRunning;

struct AppContext
{
	HINSTANCE hInstance;
	WNDCLASSEX windowClass;
	HWND windowHandle;
	HDC deviceContext;
	HGLRC glContext;
	ImGuiContext* imGuiContext;
};


LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	ImGui_ImplWin32_WndProcHandler(0, message, wParam, lParam);

	switch (message)
	{
	case WM_KEYDOWN:
	{
		if (wParam == VK_ESCAPE)
		{
			DestroyWindow(hwnd);
		}
		break;
	}
	case WM_DESTROY:
	{
		isRunning = false;
		PostQuitMessage(0);
		break;
	}
	default:
		return DefWindowProc(hwnd, message, wParam, lParam);
	}

	return NULL;
};

// Initialize the window and the context, if you have any errors, return 1 otherwise return 0
i8 Initialize(AppContext* appContext, const i32 nShowCmd)
{

	AttachConsole(ATTACH_PARENT_PROCESS);
	// Handles returned by GetStdHandle can be used by applications that need to read from or write to the console.
	g_hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

	// Initialize windowClass
	WNDCLASSEX wcex;
	ZeroMemory(&wcex, sizeof(wcex));

	wcex.cbSize = sizeof(wcex);
	/**
	 * CS_HREDRAW and CS_VREDRAW indicate that we want to redraw
	 * the entire window if a movement or size adjustment will ocurr.
	 *
	 * CS_OWNDC will get us a unique device context for each window in the class.
	 */
	wcex.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wcex.lpfnWndProc = &WindowProcedure;
	wcex.hInstance = appContext->hInstance;
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.lpszClassName = "Core";

	// If the registration of class will fail, the function will return 1;
	if (!RegisterClassEx(&wcex))
	{
		THROWDEBUGBREAK;
		return 1;
	}

	/** Now we create out temporary window and device context.
	 * 	Thats step is necessary for creating the "real" window after
	 *  with correct advanced pixel format.
	 */
	HWND fakeHwnd = CreateWindowA(
		"Core", // Window Class
		"Fake Window", // Title
		WS_CLIPSIBLINGS | WS_CLIPCHILDREN, // Style
		0, // Position x
		0, // Position  y
		1, // Width
		1, // Height
		NULL, // Parent window
		NULL, // Menu
		appContext->hInstance, // Instance
		NULL // param
	);

	// If the creation fail return false
	if (!fakeHwnd)
	{
		THROWDEBUGBREAK;
		return 1;
	}

	HDC fakeDC = GetDC(fakeHwnd); // Device Context

	/** Let’s choose a suitable pixel format. +
	 * 	Again, it’s important to set correct flags, so we will get a hardware accelerated format.
	 */
	PIXELFORMATDESCRIPTOR fakePFD;
	ZeroMemory(&fakePFD, sizeof(fakePFD));
	fakePFD.nSize = sizeof(fakePFD);
	fakePFD.nVersion = 1;
	fakePFD.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	fakePFD.iPixelType = PFD_TYPE_RGBA;
	fakePFD.cColorBits = 32;
	fakePFD.cAlphaBits = 8;
	fakePFD.cDepthBits = 24;

	const i32 fakePFDID = ChoosePixelFormat(fakeDC, &fakePFD);

	if (fakePFDID == 0)
	{
		THROWDEBUGBREAK;
		return 1;
	}

	// If everything went well, we can associate its ID with our device context.
	if (!SetPixelFormat(fakeDC, fakePFDID, &fakePFD))
	{
		THROWDEBUGBREAK;
		return 1;
	}

	// Finally, we can create temporary rendering context and make it current.
	HGLRC fakeRC = wglCreateContext(fakeDC);

	if (fakeDC == 0)
	{
		THROWDEBUGBREAK;
		return 1;
	}

	if (!wglMakeCurrent(fakeDC, fakeRC))
	{
		THROWDEBUGBREAK;
		return 1;
	}

	LoadOpenGLProcs();

	// We can get pointers to modern OpenGL functions now.
	PFNWGLCHOOSEPIXELFORMATARBPROC wglChoosePixelFormatARB = nullptr;
	wglChoosePixelFormatARB = reinterpret_cast<PFNWGLCHOOSEPIXELFORMATARBPROC>(wglGetProcAddress("wglChoosePixelFormatARB"));
	if (wglChoosePixelFormatARB == nullptr)
	{
		THROWDEBUGBREAK;
		return 1;
	}

	PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB = nullptr;
	wglCreateContextAttribsARB = reinterpret_cast<PFNWGLCREATECONTEXTATTRIBSARBPROC>(wglGetProcAddress("wglCreateContextAttribsARB"));
	if (wglCreateContextAttribsARB == nullptr)
	{
		THROWDEBUGBREAK;
		return 1;
	}

	appContext->windowHandle = CreateWindowA(
		"Core", // class name 
		"OpenGL Window", // window name
		WS_CAPTION | WS_SYSMENU | WS_CLIPSIBLINGS | WS_CLIPCHILDREN, // style
		CW_USEDEFAULT, // posx
		CW_USEDEFAULT, // posy
		WIDTH, // width
		HEIGHT, // height
		NULL, // parent window, 
		NULL, // menu
		appContext->hInstance, // instance
		NULL // param
	);

	appContext->deviceContext = GetDC(appContext->windowHandle);

	const i32 pixelAttribs[] =
	{
		WGL_DRAW_TO_WINDOW_ARB, GL_TRUE,
		WGL_SUPPORT_OPENGL_ARB, GL_TRUE,
		WGL_DOUBLE_BUFFER_ARB, GL_TRUE,
		WGL_PIXEL_TYPE_ARB, WGL_TYPE_RGBA_ARB,
		WGL_ACCELERATION_ARB, WGL_FULL_ACCELERATION_ARB,
		WGL_COLOR_BITS_ARB, 32,
		WGL_ALPHA_BITS_ARB, 8,
		WGL_DEPTH_BITS_ARB, 24,
		WGL_STENCIL_BITS_ARB, 8,
		WGL_SAMPLE_BUFFERS_ARB, GL_TRUE,
		WGL_SAMPLES_ARB, 4,
		0
	};

	i32 pixelFormatId;
	u32 numFormats;

	bool success = wglChoosePixelFormatARB(
		appContext->deviceContext,
		pixelAttribs,
		NULL,
		1,
		&pixelFormatId,
		&numFormats);


	if (!success || numFormats == 0)
	{
		THROWDEBUGBREAK;
		return 1;
	}

	/**
	 * Even if we have a new ID for a pixel format, the standard SetPixelFormat() function
	 * still requires this old PIXELFORMATDESCRIPTOR structure from us.
	 * Let’s create it from pixel format ID
	 */
	PIXELFORMATDESCRIPTOR pfd;
	/*pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 32;
	pfd.cDepthBits = 32;
	pfd.iLayerType = PFD_MAIN_PLANE;*/
	DescribePixelFormat(appContext->deviceContext, pixelFormatId, sizeof(pfd), &pfd);
	SetPixelFormat(appContext->deviceContext, pixelFormatId, &pfd);

	// Time to create our real OpenGL rendering context. 
	const i32 major_min = 4, minor_min = 5;
	i32  contextAttribs[] = {
		WGL_CONTEXT_MAJOR_VERSION_ARB, major_min,
		WGL_CONTEXT_MINOR_VERSION_ARB, minor_min,
		WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
		0
	};

	appContext->glContext = wglCreateContextAttribsARB(appContext->deviceContext, 0, contextAttribs);

	if (!appContext->glContext)
	{
		THROWDEBUGBREAK;
		return 1;
	}

	/** Time to say goodbye to our temporary rendering context, device context and window.
	 *  Let’s make the new rendering context a current one.
	 */
	wglMakeCurrent(NULL, NULL);
	wglDeleteContext(fakeRC);
	ReleaseDC(fakeHwnd, fakeDC);
	DestroyWindow(fakeHwnd);

	if (!wglMakeCurrent(appContext->deviceContext, appContext->glContext))
	{
		THROWDEBUGBREAK;
		return 1;
	}

	LPCSTR const glVersion = (LPCSTR)glGetString(GL_VERSION);

	// Setup Dear ImGui context
	appContext->imGuiContext = InitializeGUI(appContext->windowHandle);


	SetWindowText(appContext->windowHandle, glVersion);
	ShowWindow(appContext->windowHandle, nShowCmd);

	return 0;
}


void Broadcast()
{
	MSG msg;

	// Dispatches incoming sent messages, checks the thread message queue for a posted message,
	// and retrieves the message (if any exist if not return 0).
	while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) > 0)
	{
		// Translates virtual - key messages into character messages.
		// The character messages are posted to the calling thread's message queue,.
		TranslateMessage(&msg);

		// Dispatches a message to a window procedure.
		DispatchMessage(&msg);
	}

	Sleep(1);
}


int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nShowCmd)
{
	(void)hPrevInstance, lpCmdLine;

	AppContext appContext;
	appContext.hInstance = hInstance;

	const i8 result = Initialize(&appContext, nShowCmd);
	if (result == 0)
	{
		isRunning = true;
		ChangeViewPort(sceneWindowWidth, sceneWindowHeight);
		InitializeScene(sceneWindowWidth, sceneWindowHeight);
		while (isRunning)
		{
			Broadcast();

			// feed inputs to dear imgui, start new frame
			NewFrameGUI();

			// render openGL geometries
			RenderScene();

			// render GUI
			RenderGUI();

			SwapBuffers(appContext.deviceContext);

		}

		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplWin32_Shutdown();
		ImGui::DestroyContext();

		ReleaseRender();
		wglDeleteContext(appContext.glContext);
		ReleaseDC(appContext.windowHandle, appContext.deviceContext);
	}

	return result;
}


