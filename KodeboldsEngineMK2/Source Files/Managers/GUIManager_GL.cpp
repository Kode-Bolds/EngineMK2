#include "GUIManager_GL.h"

GUIManager_GL::~GUIManager_GL()
{
}

std::shared_ptr<GUIManager_GL> GUIManager_GL::Instance()
{
	static std::shared_ptr<GUIManager_GL> instance{ new GUIManager_GL };
	return instance;
}
