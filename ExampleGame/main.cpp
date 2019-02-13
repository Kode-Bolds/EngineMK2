#include <windows.h>
#include "Managers/Managers.h"
#include "Systems/Systems.h"
#include "DataStructs/Entity.h"
#include "Components/Components.h"
#include "HelperClasses/Scene.h"

HINSTANCE g_hInst = nullptr;
HWND g_hWnd = nullptr;

HRESULT InitWindow(HINSTANCE pHInstance, int pNCmdShow);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

/// <summary>
/// Entry point to the program. Initializes everything and goes into a message processing loop.
/// </summary>
/// <param name="pHInstance"></param>
/// <param name="pHPrevInstance"></param>
/// <param name="pLpCmdLine"></param>
/// <param name="pNCmdShow"></param>
/// <returns></returns>
int WINAPI wWinMain(_In_ const HINSTANCE pHInstance, _In_opt_ const HINSTANCE pHPrevInstance, _In_ const LPWSTR pLpCmdLine, _In_ const int pNCmdShow)
{
	UNREFERENCED_PARAMETER(pHPrevInstance);
	UNREFERENCED_PARAMETER(pLpCmdLine);

	if (FAILED(InitWindow(pHInstance, pNCmdShow)))
	{
		return 0;
	}

	//Main message loop
	MSG msg = { 0 };
	while (WM_QUIT != msg.message)
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{

		}
	}

	return static_cast<int>(msg.wParam);
}

/// <summary>
/// Register class and create window
/// </summary>
/// <param name="pHInstance"></param>
/// <param name="pNCmdShow"></param>
/// <returns></returns>
HRESULT InitWindow(const HINSTANCE pHInstance, const int pNCmdShow)
{
	// Register class
	WNDCLASSEX wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = pHInstance;
	wcex.hIcon = LoadIcon(pHInstance, nullptr);
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = nullptr;
	wcex.lpszMenuName = nullptr;
	wcex.lpszClassName = L"Example Game";
	wcex.hIconSm = LoadIcon(wcex.hInstance, nullptr);
	if (!RegisterClassEx(&wcex))
	{
		return static_cast<HRESULT>(0x80004005L);
	}

	// Create window
	g_hInst = pHInstance;
	RECT rc = { 0, 0, 1600, 900 };
	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);
	g_hWnd = CreateWindow(L"Example Game", L"Example Game",
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
		CW_USEDEFAULT, CW_USEDEFAULT, rc.right - rc.left, rc.bottom - rc.top, nullptr, nullptr, pHInstance,
		nullptr);
	if (!g_hWnd)
	{
		return static_cast<HRESULT>(0x80004005L);
	}

	ShowWindow(g_hWnd, pNCmdShow);

	return static_cast<HRESULT>(0L);
}

LRESULT CALLBACK WndProc(const HWND hWnd, const UINT message, const WPARAM wParam, const LPARAM lParam)
{

	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_ACTIVATEAPP:
		break;

	case WM_KEYDOWN:
	case WM_SYSKEYDOWN:
	case WM_KEYUP:
	case WM_SYSKEYUP:
		break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}