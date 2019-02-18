#include "InputManager.h"

InputManager::InputManager()
{
	mKeyboard = std::make_shared<DirectX::Keyboard>();
	mMouse = std::make_shared<DirectX::Mouse>();

}


InputManager::~InputManager()
{
}

std::shared_ptr<InputManager> InputManager::Instance()
{
	static std::shared_ptr<InputManager> instance{ new InputManager };
	return instance;
}


const void InputManager::CenterCursor() const
{
	//SetCursorPos(CLIENT_WIDTH / 2, CLIENT_HEIGHT / 2);
}

const void InputManager::CursorVisible(bool pVisible) const
{
	if (pVisible) { mMouse->SetVisible(true); }
	else { mMouse->SetVisible(true); }
}

////--------------------------------------------------------------------------------------
//// Called every time the application receives a message
////--------------------------------------------------------------------------------------
LRESULT CALLBACK InputManager::WndProc(const HWND hWnd, const UINT message, const WPARAM wParam, const LPARAM lParam)
{
	//mMouse->SetWindow(hWnd);

	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_ACTIVATEAPP:
		DirectX::Keyboard::ProcessMessage(message, wParam, lParam);
		DirectX::Mouse::ProcessMessage(message, wParam, lParam);
		break;

		// MOUSE
	case WM_INPUT:
	case WM_MOUSEMOVE:
	case WM_LBUTTONDOWN:
	case WM_LBUTTONUP:
	case WM_RBUTTONDOWN:
	case WM_RBUTTONUP:
	case WM_MBUTTONDOWN:
	case WM_MBUTTONUP:
	case WM_MOUSEWHEEL:
	case WM_XBUTTONDOWN:
	case WM_XBUTTONUP:
	case WM_MOUSEHOVER:
		DirectX::Mouse::ProcessMessage(message, wParam, lParam);
		break;

		// KEYBOARD
	case WM_KEYDOWN:
	case WM_SYSKEYDOWN:
	case WM_KEYUP:
	case WM_SYSKEYUP:
		DirectX::Keyboard::ProcessMessage(message, wParam, lParam);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

void InputManager::Update()
{
	KeyboardInput();
	MouseInput();
}

void InputManager::KeyboardInput()
{
	auto state = mKeyboard->GetState();
	mKeyboardTracker.Update(state);

	HeldDownKeys(state); // Registers every frame that a key is pressed
	SinglePressKeys(); // Registers once

}

const void InputManager::SinglePressKeys() const
{
	if (mKeyboardTracker.pressed.A) {}
	if (mKeyboardTracker.pressed.B) {}
	if (mKeyboardTracker.pressed.C) {}
	if (mKeyboardTracker.pressed.D) {}
	if (mKeyboardTracker.pressed.E) {}
	if (mKeyboardTracker.pressed.F) {}
	if (mKeyboardTracker.pressed.G) {}
	if (mKeyboardTracker.pressed.H) {}
	if (mKeyboardTracker.pressed.I) {}
	if (mKeyboardTracker.pressed.J) {}
	if (mKeyboardTracker.pressed.K) {}
	if (mKeyboardTracker.pressed.L) {}
	if (mKeyboardTracker.pressed.M) {}
	if (mKeyboardTracker.pressed.N) {}
	if (mKeyboardTracker.pressed.O) {}
	if (mKeyboardTracker.pressed.P) {}
	if (mKeyboardTracker.pressed.Q) {}
	if (mKeyboardTracker.pressed.R) {}
	if (mKeyboardTracker.pressed.S) {}
	if (mKeyboardTracker.pressed.T) {}
	if (mKeyboardTracker.pressed.U) {}
	if (mKeyboardTracker.pressed.V) {}
	if (mKeyboardTracker.pressed.W) {}
	if (mKeyboardTracker.pressed.X) {}
	if (mKeyboardTracker.pressed.Y) {}
	if (mKeyboardTracker.pressed.Z) {}

	if (mKeyboardTracker.pressed.NumPad0) {}
	if (mKeyboardTracker.pressed.NumPad1) {}
	if (mKeyboardTracker.pressed.NumPad2) {}
	if (mKeyboardTracker.pressed.NumPad3) {}
	if (mKeyboardTracker.pressed.NumPad4) {}
	if (mKeyboardTracker.pressed.NumPad5) {}
	if (mKeyboardTracker.pressed.NumPad6) {}
	if (mKeyboardTracker.pressed.NumPad7) {}
	if (mKeyboardTracker.pressed.NumPad8) {}
	if (mKeyboardTracker.pressed.NumPad9) {}

	if (mKeyboardTracker.pressed.Add) {}
	if (mKeyboardTracker.pressed.Apps) {}
	if (mKeyboardTracker.pressed.Attn) {}
	if (mKeyboardTracker.pressed.Back) {}
	if (mKeyboardTracker.pressed.BrowserBack) {}
	if (mKeyboardTracker.pressed.BrowserFavorites) {}
	if (mKeyboardTracker.pressed.BrowserForward) {}
	if (mKeyboardTracker.pressed.BrowserHome) {}
	if (mKeyboardTracker.pressed.BrowserRefresh) {}
	if (mKeyboardTracker.pressed.BrowserSearch) {}
	if (mKeyboardTracker.pressed.BrowserStop) {}
	if (mKeyboardTracker.pressed.CapsLock) {}
	if (mKeyboardTracker.pressed.Crsel) {}
	if (mKeyboardTracker.pressed.D0) {}
	if (mKeyboardTracker.pressed.D1) {}
	if (mKeyboardTracker.pressed.D2) {}
	if (mKeyboardTracker.pressed.D3) {}
	if (mKeyboardTracker.pressed.D4) {}
	if (mKeyboardTracker.pressed.D5) {}
	if (mKeyboardTracker.pressed.D6) {}
	if (mKeyboardTracker.pressed.D7) {}
	if (mKeyboardTracker.pressed.D8) {}
	if (mKeyboardTracker.pressed.D9) {}
	if (mKeyboardTracker.pressed.Decimal) {}
	if (mKeyboardTracker.pressed.Delete) {}
	if (mKeyboardTracker.pressed.Divide) {}
	if (mKeyboardTracker.pressed.Down) {}
	if (mKeyboardTracker.pressed.End) {}
	if (mKeyboardTracker.pressed.Enter) {}
	if (mKeyboardTracker.pressed.EraseEof) {}
	if (mKeyboardTracker.pressed.Escape) {}
	if (mKeyboardTracker.pressed.Execute) {}
	if (mKeyboardTracker.pressed.Exsel) {}

	if (mKeyboardTracker.pressed.F1) {}
	if (mKeyboardTracker.pressed.F2) {}
	if (mKeyboardTracker.pressed.F3) {}
	if (mKeyboardTracker.pressed.F4) {}
	if (mKeyboardTracker.pressed.F5) {}
	if (mKeyboardTracker.pressed.F6) {}
	if (mKeyboardTracker.pressed.F7) {}
	if (mKeyboardTracker.pressed.F8) {}
	if (mKeyboardTracker.pressed.F9) {}
	if (mKeyboardTracker.pressed.F10) {}
	if (mKeyboardTracker.pressed.F11) {}
	if (mKeyboardTracker.pressed.F12) {}
	if (mKeyboardTracker.pressed.F13) {}
	if (mKeyboardTracker.pressed.F14) {}
	if (mKeyboardTracker.pressed.F15) {}
	if (mKeyboardTracker.pressed.F16) {}
	if (mKeyboardTracker.pressed.F17) {}
	if (mKeyboardTracker.pressed.F18) {}
	if (mKeyboardTracker.pressed.F19) {}
	if (mKeyboardTracker.pressed.F20) {}

	if (mKeyboardTracker.pressed.Help) {}
	if (mKeyboardTracker.pressed.Home) {}
	if (mKeyboardTracker.pressed.ImeConvert) {}
	if (mKeyboardTracker.pressed.ImeNoConvert) {}
	if (mKeyboardTracker.pressed.Insert) {}
	if (mKeyboardTracker.pressed.Kana) {}
	if (mKeyboardTracker.pressed.Kanji) {}
	if (mKeyboardTracker.pressed.LaunchApplication1) {}
	if (mKeyboardTracker.pressed.LaunchApplication2) {}
	if (mKeyboardTracker.pressed.LaunchMail) {}
	if (mKeyboardTracker.pressed.Left) {}
	if (mKeyboardTracker.pressed.LeftAlt) {}
	if (mKeyboardTracker.pressed.LeftControl) {}
	if (mKeyboardTracker.pressed.LeftShift) {}
	if (mKeyboardTracker.pressed.LeftWindows) {}
	if (mKeyboardTracker.pressed.MediaNextTrack) {}
	if (mKeyboardTracker.pressed.MediaPlayPause) {}
	if (mKeyboardTracker.pressed.MediaPreviousTrack) {}
	if (mKeyboardTracker.pressed.MediaStop) {}
	if (mKeyboardTracker.pressed.Multiply) {}
	if (mKeyboardTracker.pressed.Oem8) {}
	if (mKeyboardTracker.pressed.OemAuto) {}
	if (mKeyboardTracker.pressed.OemBackslash) {}
	if (mKeyboardTracker.pressed.OemClear) {}
	if (mKeyboardTracker.pressed.OemCloseBrackets) {}
	if (mKeyboardTracker.pressed.OemComma) {}
	if (mKeyboardTracker.pressed.OemCopy) {}
	if (mKeyboardTracker.pressed.OemEnlW) {}
	if (mKeyboardTracker.pressed.OemMinus) {}
	if (mKeyboardTracker.pressed.OemOpenBrackets) {}
	if (mKeyboardTracker.pressed.OemPeriod) {}
	if (mKeyboardTracker.pressed.OemPipe) {}
	if (mKeyboardTracker.pressed.OemPlus) {}
	if (mKeyboardTracker.pressed.OemQuestion) {}
	if (mKeyboardTracker.pressed.OemQuotes) {}
	if (mKeyboardTracker.pressed.OemSemicolon) {}
	if (mKeyboardTracker.pressed.OemTilde) {}
	if (mKeyboardTracker.pressed.PageDown) {}
	if (mKeyboardTracker.pressed.Pa1) {}
	if (mKeyboardTracker.pressed.PageUp) {}
	if (mKeyboardTracker.pressed.Pause) {}
	if (mKeyboardTracker.pressed.Play) {}
	if (mKeyboardTracker.pressed.Print) {}
	if (mKeyboardTracker.pressed.PrintScreen) {}
	if (mKeyboardTracker.pressed.ProcessKey) {}
	if (mKeyboardTracker.pressed.Right) {}
	if (mKeyboardTracker.pressed.RightAlt) {}
	if (mKeyboardTracker.pressed.RightControl) {}
	if (mKeyboardTracker.pressed.RightShift) {}
	if (mKeyboardTracker.pressed.RightWindows) {}
	if (mKeyboardTracker.pressed.Scroll) {}
	if (mKeyboardTracker.pressed.Select) {}
	if (mKeyboardTracker.pressed.SelectMedia) {}
	if (mKeyboardTracker.pressed.Separator) {}
	if (mKeyboardTracker.pressed.Sleep) {}
	if (mKeyboardTracker.pressed.Space) {}
	if (mKeyboardTracker.pressed.Subtract) {}
	if (mKeyboardTracker.pressed.Tab) {}
	if (mKeyboardTracker.pressed.Up) {}
	if (mKeyboardTracker.pressed.VolumeDown) {}
	if (mKeyboardTracker.pressed.VolumeUp) {}
	if (mKeyboardTracker.pressed.VolumeMute) {}
	if (mKeyboardTracker.pressed.Zoom) {}
}

const void InputManager::HeldDownKeys(DirectX::Keyboard::State &state)const
{
	if (state.A) {}
	if (state.B) {}
	if (state.C) {}
	if (state.D) {}
	if (state.E) {}
	if (state.F) {}
	if (state.G) {}
	if (state.H) {}
	if (state.I) {}
	if (state.J) {}
	if (state.K) {}
	if (state.L) {}
	if (state.M) {}
	if (state.N) {}
	if (state.O) {}
	if (state.P) {}
	if (state.Q) {}
	if (state.R) {}
	if (state.S) {}
	if (state.T) {}
	if (state.U) {}
	if (state.V) {}
	if (state.W) {}
	if (state.X) {}
	if (state.Y) {}
	if (state.Z) {}

	if (state.NumPad0) {}
	if (state.NumPad1) {}
	if (state.NumPad2) {}
	if (state.NumPad3) {}
	if (state.NumPad4) {}
	if (state.NumPad5) {}
	if (state.NumPad6) {}
	if (state.NumPad7) {}
	if (state.NumPad8) {}
	if (state.NumPad9) {}

	if (state.Add) {}
	if (state.Apps) {}
	if (state.Attn) {}
	if (state.Back) {}
	if (state.BrowserBack) {}
	if (state.BrowserFavorites) {}
	if (state.BrowserForward) {}
	if (state.BrowserHome) {}
	if (state.BrowserRefresh) {}
	if (state.BrowserSearch) {}
	if (state.BrowserStop) {}
	if (state.CapsLock) {}
	if (state.Crsel) {}
	if (state.D0) {}
	if (state.D1) {}
	if (state.D2) {}
	if (state.D3) {}
	if (state.D4) {}
	if (state.D5) {}
	if (state.D6) {}
	if (state.D7) {}
	if (state.D8) {}
	if (state.D9) {}
	if (state.Decimal) {}
	if (state.Delete) {}
	if (state.Divide) {}
	if (state.Down) {}
	if (state.End) {}
	if (state.Enter) {}
	if (state.EraseEof) {}
	if (state.Escape) {}
	if (state.Execute) {}
	if (state.Exsel) {}

	if (state.F1) {}
	if (state.F2) {}
	if (state.F3) {}
	if (state.F4) {}
	if (state.F5) {}
	if (state.F6) {}
	if (state.F7) {}
	if (state.F8) {}
	if (state.F9) {}
	if (state.F10) {}
	if (state.F11) {}
	if (state.F12) {}
	if (state.F13) {}
	if (state.F14) {}
	if (state.F15) {}
	if (state.F16) {}
	if (state.F17) {}
	if (state.F18) {}
	if (state.F19) {}
	if (state.F20) {}

	if (state.Help) {}
	if (state.Home) {}
	if (state.ImeConvert) {}
	if (state.ImeNoConvert) {}
	if (state.Insert) {}
	if (state.Kana) {}
	if (state.Kanji) {}
	if (state.LaunchApplication1) {}
	if (state.LaunchApplication2) {}
	if (state.LaunchMail) {}
	if (state.Left) {}
	if (state.LeftAlt) {}
	if (state.LeftControl) {}
	if (state.LeftShift) {}
	if (state.LeftWindows) {}
	if (state.MediaNextTrack) {}
	if (state.MediaPlayPause) {}
	if (state.MediaPreviousTrack) {}
	if (state.MediaStop) {}
	if (state.Multiply) {}
	if (state.Oem8) {}
	if (state.OemAuto) {}
	if (state.OemBackslash) {}
	if (state.OemClear) {}
	if (state.OemCloseBrackets) {}
	if (state.OemComma) {}
	if (state.OemCopy) {}
	if (state.OemEnlW) {}
	if (state.OemMinus) {}
	if (state.OemOpenBrackets) {}
	if (state.OemPeriod) {}
	if (state.OemPipe) {}
	if (state.OemPlus) {}
	if (state.OemQuestion) {}
	if (state.OemQuotes) {}
	if (state.OemSemicolon) {}
	if (state.OemTilde) {}
	if (state.PageDown) {}
	if (state.Pa1) {}
	if (state.PageUp) {}
	if (state.Pause) {}
	if (state.Play) {}
	if (state.Print) {}
	if (state.PrintScreen) {}
	if (state.ProcessKey) {}
	if (state.Right) {}
	if (state.RightAlt) {}
	if (state.RightControl) {}
	if (state.RightShift) {}
	if (state.RightWindows) {}
	if (state.Scroll) {}
	if (state.Select) {}
	if (state.SelectMedia) {}
	if (state.Separator) {}
	if (state.Sleep) {}
	if (state.Space) {}
	if (state.Subtract) {}
	if (state.Tab) {}
	if (state.Up) {}
	if (state.VolumeDown) {}
	if (state.VolumeUp) {}
	if (state.VolumeMute) {}
	if (state.Zoom) {}
}

const void InputManager::MouseInput() {

	auto state = mMouse->GetState();
	mMouseTracker.Update(state);

	mMousePosition = DirectX::XMFLOAT2(mMouse->GetState().x, mMouse->GetState().y);

	// Scroll wheel
	mMouseWheelValue = mMouse->GetState().scrollWheelValue;

	// Buttons
	using ButtonState = DirectX::Mouse::ButtonStateTracker::ButtonState;

	// Allows mouse buttons to be held down
	if (state.leftButton) {}
	if (state.rightButton) {}
	if (state.middleButton) {}

	// single mouse button presses
	if (mMouseTracker.leftButton == ButtonState::PRESSED) {}
	if (mMouseTracker.rightButton == ButtonState::PRESSED) {}
	if (mMouseTracker.middleButton == ButtonState::PRESSED) {}
}


