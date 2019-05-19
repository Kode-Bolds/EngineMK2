#pragma once


class GUIManager {
protected:

	//Private constructor for singleton pattern
	GUIManager() = default;
private:
public:
	virtual ~GUIManager();
	void Update();

	//Singleton pattern
	//Deleted copy constructor and assignment operator so no copies of the singleton instance can be made
	GUIManager(GUIManager const&) = delete;
	GUIManager& operator=(GUIManager const&) = delete;

	//virtual void Init() = 0;
};