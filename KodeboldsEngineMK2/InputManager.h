#pragma once
#include <vector>
#include <string>
#include <DirectXMath.h>
#include <Keyboard.h>
#include <Mouse.h>
#include <Windows.h>

class InputManager
{
private:
	std::unique_ptr<DirectX::Keyboard> mKeyboard;
	DirectX::Keyboard::KeyboardStateTracker mKeyboardTracker;
	std::unique_ptr<DirectX::Mouse> mMouse;

	DirectX::XMFLOAT4 mMousePosition;
	
	void CenterCursor();
	void CursorVisible(bool pVisibility);

	LRESULT CALLBACK WndProc(const HWND hWnd, const UINT message, const WPARAM wParam, const LPARAM lParam);

	void Update();
	void KeyboardInput();
	void MouseInput();
public:
	InputManager();
	~InputManager();
};

