#include "Managers.h"
#include <windows.h>
#include <memory>
#include "Systems.h"
#include "GameScene.h"
#include "CustomComp1.h"
#include "CustomComp2.h"

#pragma comment(lib, "KodeboldsEngineMK2.lib")

using namespace KodeboldsMath;

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

	//Managers
	std::shared_ptr<ECSManager> ecsManager = ECSManager::Instance();
	std::shared_ptr<SceneManager> sceneManager = SceneManager::Instance();
	std::shared_ptr<ThreadManager> threadManager = ThreadManager::Instance();
	std::shared_ptr<NetworkManager> networkManager = NetworkManager::Instance();
	std::shared_ptr<AntTweakManager> anttweakManager = AntTweakManager::Instance();

	//Initialise winsock
	networkManager->InitWinSock(9171);

	//Get window height and width for scene manager
	RECT rc;
	GetClientRect(hWnd, &rc);
	float width = static_cast<float>(rc.right - rc.left);
	float height = static_cast<float>(rc.bottom - rc.top);
	sceneManager->SetWindowWidthHeight(width, height);

	//Render systems
#ifdef DIRECTX
	ecsManager->AddRenderSystem(std::make_shared<RenderSystem_DX>(hWnd));
#elif OPENGL
	ecsManager->AddRenderSystem(std::make_shared<RenderSystem_DX>(hWnd));
#endif

	ecsManager->AddUpdateSystem(std::make_shared<MovementSystem>());

	//Create camera
	int entityID = ecsManager->CreateEntity();
	Camera cam{Vector4(0, 40, 1, 1), Vector4(0, 1, 0, 1), 60, 1, 200};
	ecsManager->AddCameraComp(cam, entityID);
	Transform trans{};
	trans.translation = Vector4(0, 40, -100, 1);
	ecsManager->AddTransformComp(trans, entityID);

	//Create light
	entityID = ecsManager->CreateEntity();
	Light light{Vector4(1, 1, 1, 1)};
	ecsManager->AddLightComp(light, entityID);
	Transform transL{};
	transL.translation = Vector4(0, 5, -2, 1);
	ecsManager->AddTransformComp(transL, entityID);

	//Create moving cube
	entityID = ecsManager->CreateEntity();
	Geometry geo{ L"cube.obj" };
	ecsManager->AddGeometryComp(geo, entityID);
	Shader shader{L"defaultShader.fx"};
	ecsManager->AddShaderComp(shader, entityID);
	Transform transC{};
	transC.scale = Vector4(1, 1, 1, 1);
	ecsManager->AddTransformComp(transC, entityID);
	Velocity vel{};
	vel.acceleration = Vector4(0, 12.0f, 0, 1);
	vel.maxSpeed = 50;
	ecsManager->AddVelocityComp(vel, entityID);
	Gravity grav{};
	ecsManager->AddGravityComp(grav, entityID);

	//Testing custom components
	ecsManager->CreateComponentType<CustomComp1>();
	ecsManager->CreateComponentType<CustomComp2>();

	CustomComp1 CC1{};
	if (!ecsManager->AddComponent<CustomComp1>(CC1, entityID))
	{
		OutputDebugString(L"REEEEEE");
	}

	CustomComp2 CC2{};
	if (!ecsManager->AddComponent<CustomComp2>(CC2, entityID))
	{
		OutputDebugString(L"REEEEEE");
	}

	CustomComp1* CC1Ptr = ecsManager->GetComponent<CustomComp1>(entityID);
	CustomComp2* CC2Ptr = ecsManager->GetComponent<CustomComp2>(entityID);

	//Scenes
	sceneManager->LoadScene<GameScene>();

	//AntTweak
	anttweakManager->AddBar("Testing");
	TwDefine(" Testing size='300 320' valueswidth=200 ");
	anttweakManager->AddVariable("Testing", "Velocity", TW_TYPE_DIR3F, &ecsManager->VelocityComp(entityID)->velocity, "");
	anttweakManager->AddVariable("Testing", "Acceleration", TW_TYPE_DIR3F, &ecsManager->VelocityComp(entityID)->acceleration, "");
	anttweakManager->AddVariable("Testing", "Max Speed", TW_TYPE_FLOAT, &ecsManager->VelocityComp(entityID)->maxSpeed, "");

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
			//Update scenes
			sceneManager->Update();
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
	//Register class
	WNDCLASSEX wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
#ifdef  DIRECTX
	wcex.lpfnWndProc = InputManager_DX::WndProc;
#elif OPENGL
	wcex.lpfnWndProc = InputManager_GL::WndProc;
#endif
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = pHInstance;
	wcex.hIcon = LoadIcon(pHInstance, nullptr);
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = nullptr;
	wcex.lpszMenuName = nullptr;
	wcex.lpszClassName = L"Canvas Painter";
	wcex.hIconSm = LoadIcon(wcex.hInstance, nullptr);
	if (!RegisterClassEx(&wcex))
	{
		return static_cast<HRESULT>(0x80004005L);
	}

	//Create window
	hInst = pHInstance;
	RECT rc = { 0, 0, 1920, 1080 };
	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);
	hWnd = CreateWindow(L"Canvas Painter", L"Canvas Painter",
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