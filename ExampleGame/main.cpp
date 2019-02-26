#include <windows.h>
#include <memory>
#include "Managers.h"
#include "Vector4.h"
#include "Systems.h"
#include "Components.h"
#include "Matrix4.h"
#include "TestScene.h"
#include "TestScene2.h"
#include "KodeBoldsMath.h"

#pragma comment(lib, "KodeboldsEngineMK2.lib")

HINSTANCE hInst = nullptr;
HWND hWnd = nullptr;

HRESULT InitWindow(HINSTANCE pHInstance, int pNCmdShow);

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
	
	// Testing Input Manager
	std::shared_ptr<InputManager> inputManager = InputManager::Instance();
	

	//Testing vector4 class
	Vector4 v1(1.0f, 1.0f, 1.0f, 0.0f);
	Vector4 v2(1.0f, 1.0f, 1.0f, 0.0f);

	v2.X = 1;
	v2.Y = 1;
	v2.Z = 1;

	v1 = v2 + v1;
	//v2 = v1 + ((v1 * 2) - v2);

	//Testing matrix4 class
	Matrix4 m1;
	m1 = KodeBoldsMath::Transpose(m1);

	//Testing ECS Manager and movement system
	std::shared_ptr<ECSManager> ecsManager = ECSManager::Instance();
	std::shared_ptr<ISystem> systPointer = std::make_shared<MovementSystem>();
	std::shared_ptr<ISystem> renderer = std::make_shared<RenderSystem>(hWnd);
	ecsManager->AddUpdateSystem(systPointer);
	ecsManager->AddRenderSystem(renderer);

	ecsManager->CreateEntity("Test");
	ecsManager->CreateEntity("Test1");
	ecsManager->CreateEntity("Test2");
	ecsManager->CreateEntity("Test3");

	//Testing transform component
	Transform transform;
	transform.mTranslation = v1;

	ecsManager->AddTransformComp(transform, "Test");
	ecsManager->AddTransformComp(transform, "Test1");
	ecsManager->AddTransformComp(transform, "Test2");
	ecsManager->AddTransformComp(transform, "Test3");

	//Testing velocity component
	Vector4 velocityV(0.0f, 0.0f, 0.0f, 0.0f);
	Vector4 acceleration(10.0f, 0.0f, 0.0f, 0.0f);
	Velocity velocity{velocityV, acceleration, 1.0f};

	ecsManager->AddVelocityComp(velocity, "Test");
	ecsManager->AddVelocityComp(velocity, "Test1");
	ecsManager->AddVelocityComp(velocity, "Test2");
	ecsManager->AddVelocityComp(velocity, "Test3");

	Gravity gravity;
	ecsManager->AddGravityComp(gravity, "Test");

	ecsManager->RemoveTransformComp("Test1");


	//Testing scene manager
	std::shared_ptr<SceneManager> sceneManager = SceneManager::Instance();

	sceneManager->LoadScene<TestScene>();

	sceneManager->LoadScene<TestScene2>();



	Velocity velocity2;

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
			//Testing movement system
			ecsManager->ProcessSystems();

			velocity2 = *ecsManager->VelocityComp("Test");

			//Testing scene manager
			sceneManager->Update();
			sceneManager->Render();

			double dt = sceneManager->DeltaTime();
			int fps = sceneManager->Fps();
			double time = sceneManager->Time();
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
	wcex.lpfnWndProc = InputManager::WndProc;
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
	hInst = pHInstance;
	RECT rc = { 0, 0, 1600, 900 };
	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);
	hWnd = CreateWindow(L"Example Game", L"Example Game",
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
		CW_USEDEFAULT, CW_USEDEFAULT, rc.right - rc.left, rc.bottom - rc.top, nullptr, nullptr, pHInstance,
		nullptr);
	if (!hWnd)
	{
		return static_cast<HRESULT>(0x80004005L);
	}

	ShowWindow(hWnd, pNCmdShow);

	return static_cast<HRESULT>(0L);
}