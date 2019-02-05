#include "InputManager.h"

InputManager::InputManager()
{
	mKeyboard = std::make_unique<DirectX::Keyboard>();
	mMouse = std::make_unique<DirectX::Mouse>();
	//mMouse->SetWindow(window);
}


InputManager::~InputManager()
{
}


void InputManager::CenterCursor()
{
}

void InputManager::CursorVisible(bool pVisibility)
{

}

////--------------------------------------------------------------------------------------
//// Called every time the application receives a message
////--------------------------------------------------------------------------------------
LRESULT CALLBACK InputManager::WndProc(const HWND hWnd, const UINT message, const WPARAM wParam, const LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_ACTIVATEAPP:
		DirectX::Keyboard::ProcessMessage(message, wParam, lParam);
		break;

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
	if (mKeyboard->GetState().A) {}
	if (mKeyboard->GetState().B) {}
	if (mKeyboard->GetState().C) {}
	if (mKeyboard->GetState().D) {}
	if (mKeyboard->GetState().E) {}
	if (mKeyboard->GetState().F) {}
	if (mKeyboard->GetState().G) {}
	if (mKeyboard->GetState().H) {}
	if (mKeyboard->GetState().I) {}
	if (mKeyboard->GetState().J) {}
	if (mKeyboard->GetState().K) {}
	if (mKeyboard->GetState().L) {}
	if (mKeyboard->GetState().M) {}
	if (mKeyboard->GetState().N) {}
	if (mKeyboard->GetState().O) {}
	if (mKeyboard->GetState().P) {}
	if (mKeyboard->GetState().Q) {}
	if (mKeyboard->GetState().R) {}
	if (mKeyboard->GetState().S) {}
	if (mKeyboard->GetState().T) {}
	if (mKeyboard->GetState().U) {}
	if (mKeyboard->GetState().V) {}
	if (mKeyboard->GetState().W) {}
	if (mKeyboard->GetState().X) {}
	if (mKeyboard->GetState().Y) {}
	if (mKeyboard->GetState().Z) {}

	if (mKeyboard->GetState().NumPad0) {}
	if (mKeyboard->GetState().NumPad1) {}
	if (mKeyboard->GetState().NumPad2) {}
	if (mKeyboard->GetState().NumPad3) {}
	if (mKeyboard->GetState().NumPad4) {}
	if (mKeyboard->GetState().NumPad5) {}
	if (mKeyboard->GetState().NumPad6) {}
	if (mKeyboard->GetState().NumPad7) {}
	if (mKeyboard->GetState().NumPad8) {}
	if (mKeyboard->GetState().NumPad9) {}

	if (mKeyboard->GetState().Add) {}
	if (mKeyboard->GetState().Apps) {}
	if (mKeyboard->GetState().Attn) {}
	if (mKeyboard->GetState().Back) {}
	if (mKeyboard->GetState().BrowserBack) {}
	if (mKeyboard->GetState().BrowserFavorites) {}
	if (mKeyboard->GetState().BrowserForward) {}
	if (mKeyboard->GetState().BrowserHome) {}
	if (mKeyboard->GetState().BrowserRefresh) {}
	if (mKeyboard->GetState().BrowserSearch) {}
	if (mKeyboard->GetState().BrowserStop) {}
	if (mKeyboard->GetState().CapsLock) {}
	if (mKeyboard->GetState().Crsel) {}
	if (mKeyboard->GetState().D0) {}
	if (mKeyboard->GetState().D1) {}
	if (mKeyboard->GetState().D2) {}
	if (mKeyboard->GetState().D3) {}
	if (mKeyboard->GetState().D4) {}
	if (mKeyboard->GetState().D5) {}
	if (mKeyboard->GetState().D6) {}
	if (mKeyboard->GetState().D7) {}
	if (mKeyboard->GetState().D8) {}
	if (mKeyboard->GetState().D9) {}
	if (mKeyboard->GetState().Decimal) {}
	if (mKeyboard->GetState().Delete) {}
	if (mKeyboard->GetState().Divide) {}
	if (mKeyboard->GetState().Down) {}
	if (mKeyboard->GetState().End) {}
	if (mKeyboard->GetState().Enter) {}
	if (mKeyboard->GetState().EraseEof) {}
	if (mKeyboard->GetState().Escape) {}
	if (mKeyboard->GetState().Execute) {}
	if (mKeyboard->GetState().Exsel) {}

	if (mKeyboard->GetState().F1) {}
	if (mKeyboard->GetState().F2) {}
	if (mKeyboard->GetState().F3) {}
	if (mKeyboard->GetState().F4) {}
	if (mKeyboard->GetState().F5) {}
	if (mKeyboard->GetState().F6) {}
	if (mKeyboard->GetState().F7) {}
	if (mKeyboard->GetState().F8) {}
	if (mKeyboard->GetState().F9) {}
	if (mKeyboard->GetState().F10) {}
	if (mKeyboard->GetState().F11) {}
	if (mKeyboard->GetState().F12) {}
	if (mKeyboard->GetState().F13) {}
	if (mKeyboard->GetState().F14) {}
	if (mKeyboard->GetState().F15) {}
	if (mKeyboard->GetState().F16) {}
	if (mKeyboard->GetState().F17) {}
	if (mKeyboard->GetState().F18) {}
	if (mKeyboard->GetState().F19) {}
	if (mKeyboard->GetState().F20) {}

	if (mKeyboard->GetState().Help) {}
	if (mKeyboard->GetState().Home) {}
	if (mKeyboard->GetState().ImeConvert) {}
	if (mKeyboard->GetState().ImeNoConvert) {}
	if (mKeyboard->GetState().Insert) {}
	if (mKeyboard->GetState().Kana) {}
	if (mKeyboard->GetState().Kanji) {}
	if (mKeyboard->GetState().LaunchApplication1) {}
	if (mKeyboard->GetState().LaunchApplication2) {}
	if (mKeyboard->GetState().LaunchMail) {}
	if (mKeyboard->GetState().Left) {}
	if (mKeyboard->GetState().LeftAlt) {}
	if (mKeyboard->GetState().LeftControl) {}
	if (mKeyboard->GetState().LeftShift) {}
	if (mKeyboard->GetState().LeftWindows) {}
	if (mKeyboard->GetState().MediaNextTrack) {}
	if (mKeyboard->GetState().MediaPlayPause) {}
	if (mKeyboard->GetState().MediaPreviousTrack) {}
	if (mKeyboard->GetState().MediaStop) {}
	if (mKeyboard->GetState().Multiply) {}
	if (mKeyboard->GetState().Oem8) {}
	if (mKeyboard->GetState().OemAuto) {}
	if (mKeyboard->GetState().OemBackslash) {}
	if (mKeyboard->GetState().OemClear) {}
	if (mKeyboard->GetState().OemCloseBrackets) {}
	if (mKeyboard->GetState().OemComma) {}
	if (mKeyboard->GetState().OemCopy) {}
	if (mKeyboard->GetState().OemEnlW) {}
	if (mKeyboard->GetState().OemMinus) {}
	if (mKeyboard->GetState().OemOpenBrackets) {}
	if (mKeyboard->GetState().OemPeriod) {}
	if (mKeyboard->GetState().OemPipe) {}
	if (mKeyboard->GetState().OemPlus) {}
	if (mKeyboard->GetState().OemQuestion) {}
	if (mKeyboard->GetState().OemQuotes) {}
	if (mKeyboard->GetState().OemSemicolon) {}
	if (mKeyboard->GetState().OemTilde) {}
	if (mKeyboard->GetState().PageDown) {}
	if (mKeyboard->GetState().Pa1) {}
	if (mKeyboard->GetState().PageUp) {}
	if (mKeyboard->GetState().Pause) {}
	if (mKeyboard->GetState().Play) {}
	if (mKeyboard->GetState().Print) {}
	if (mKeyboard->GetState().PrintScreen) {}
	if (mKeyboard->GetState().ProcessKey) {}
	if (mKeyboard->GetState().Right) {}
	if (mKeyboard->GetState().RightAlt) {}
	if (mKeyboard->GetState().RightControl) {}
	if (mKeyboard->GetState().RightShift) {}
	if (mKeyboard->GetState().RightWindows) {}
	if (mKeyboard->GetState().Scroll) {}
	if (mKeyboard->GetState().Select) {}
	if (mKeyboard->GetState().SelectMedia) {}
	if (mKeyboard->GetState().Separator) {}
	if (mKeyboard->GetState().Sleep) {}
	if (mKeyboard->GetState().Space) {}
	if (mKeyboard->GetState().Subtract) {}
	if (mKeyboard->GetState().Tab) {}
	if (mKeyboard->GetState().Up) {}
	if (mKeyboard->GetState().VolumeDown) {}
	if (mKeyboard->GetState().VolumeUp) {}
	if (mKeyboard->GetState().VolumeMute) {}
	if (mKeyboard->GetState().Zoom) {}
}

void InputManager::MouseInput() {
}


