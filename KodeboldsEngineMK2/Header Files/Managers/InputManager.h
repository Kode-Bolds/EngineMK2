#pragma once
#include <windows.h>
#include <DirectXMath.h>
#include <vector>
#include <string>
#include <Keyboard.h>
#include <Mouse.h>
#include <memory>

class InputManager
{
private:
	std::unique_ptr<DirectX::Keyboard> mKeyboard;
	DirectX::Keyboard::KeyboardStateTracker mKeyboardTracker;

	std::unique_ptr<DirectX::Mouse> mMouse;
	DirectX::Mouse::ButtonStateTracker mMouseTracker;

	DirectX::XMFLOAT2 mMousePosition;
	int mMouseWheelValue;
	
	const void CenterCursor() const;
	const void CursorVisible(bool pVisible) const;

	LRESULT CALLBACK WndProc(const HWND hWnd, const UINT message, const WPARAM wParam, const LPARAM lParam);

	void Update();
	void KeyboardInput();
	const void SinglePressKeys() const;
	const void HeldDownKeys(DirectX::Keyboard::State &state) const;
	const void MouseInput();
public:
	InputManager();
	~InputManager();
};

