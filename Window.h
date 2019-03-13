#pragma once

// Minimize the num of 
// headers from Windows.h
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

// The min/max macros conflict 
// with like-named member functions.
// Only use std::min and std::max 
// defined in <algorithm>.
#if defined(min)
#undef min
#endif

#if defined(max)
#undef max
#endif

// To define a func called CreateWindow,
// the Windows macro needs to be undefined.
#if defined(CreateWindow)
#undef CreateWindow
#endif

// Windows Runtime Library. Needed for 
// Microsoft::WRL::ComPtr<> template class.
#include <wrl.h>
using namespace Microsoft::WRL;

#include <d3d12.h>
#include <dxgi1_6.h>

// Window class name. Used for registering / creating the window.
constexpr wchar_t WINDOW_CLASS_NAME[] = L"DX12RenderWindowClass";

class Window 
{
private:
	//Window(const Window& Window) = delete;
	//Window& operator=(const Window& Window) = delete;

	// By default, use windowed mode.
	// Can be toggled with the Alt+Enter or F11
	bool g_Fullscreen = false;
	// Window rectangle (used to toggle fullscreen state).
	RECT g_WindowRect;
	// Window handle.
	HWND g_hWnd;

public:
	Window() {};
	~Window() {};

	// Variable refresh rate displays (NVidia's G-Sync and AMD's FreeSync) require 
	//		tearing to be enabled in the DirectX 12 application to function correctly. 
	// This feature is also known as "vsync-off".
	bool CheckTearingSupport();
	void SetFullscreen(bool fullscreen); 
	void ToggleFullscreen() { SetFullscreen(!g_Fullscreen); };

	// Before creating an instance of an OS window, the window class corresponding to that window must be registered. 
	// The window class will be automatically unregistered when the application terminates.
	void RegisterWindowClass(HINSTANCE hInst);

	HWND CreateWindow(HINSTANCE hInst, const wchar_t* windowTitle, UINT width, UINT height);

	// The primary purpose of the swap chain is to present the rendered image to the screen. 
	ComPtr<IDXGISwapChain4> CreateSwapChain(
		ComPtr<ID3D12CommandQueue> commandQueue,
		UINT width, UINT height, UINT bufferCount);

	HWND GetHWND() { return g_hWnd; }
	void Show() { ::ShowWindow(g_hWnd, SW_SHOW); }
};