#pragma once
#include <windows.h>
#include <Keyboard.h>
#include <DirectXMath.h>
#include <vector>
#include <string>
#include <Mouse.h>
#include <memory>

class InputManager
{
private:
	InputManager();

	std::shared_ptr<DirectX::Keyboard> mKeyboard;
	DirectX::Keyboard::KeyboardStateTracker mKeyboardTracker;

	std::shared_ptr<DirectX::Mouse> mMouse;
	DirectX::Mouse::ButtonStateTracker mMouseTracker;

	DirectX::XMFLOAT2 mMousePosition;
	int mMouseWheelValue;

	const void CenterCursor() const;
	const void CursorVisible(bool pVisible) const;


	void Update();
	void KeyboardInput();
	const void SinglePressKeys() const;
	const void HeldDownKeys(DirectX::Keyboard::State &state) const;
	const void MouseInput();
public:
	static LRESULT CALLBACK WndProc(const HWND hWnd, const UINT message, const WPARAM wParam, const LPARAM lParam);
	~InputManager();

	//Singleton pattern
	//Deleted copy constructor and assignment operator so no copies of the singleton instance can be made
	InputManager(InputManager const&) = delete;
	InputManager& operator=(InputManager const&) = delete;
	static std::shared_ptr<InputManager> Instance();
};