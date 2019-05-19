#pragma once
#include "GUIManager.h"
#include <memory>

class GUIManager_GL : public GUIManager {
private:
	//Private constructor for singleton pattern
	GUIManager_GL();
protected:
public:
	~GUIManager_GL();

	//Singleton pattern
	//Deleted copy constructor and assignment operator so no copies of the singleton instance can be made
	GUIManager_GL(GUIManager_GL const&) = delete;
	GUIManager_GL& operator=(GUIManager_GL const&) = delete;
	static std::shared_ptr<GUIManager_GL> Instance();
};