#include "ResourceManager.h"

using namespace std;

//TODO: Test singleton pattern works
ResourceManager::ResourceManager()
{
	if (!mInstance)
	{
		mInstance = make_shared<ResourceManager>(this);
	}
	else
	{
		delete this;
	}
}

ResourceManager::~ResourceManager()
{
}

std::shared_ptr<ResourceManager> ResourceManager::Instance()
{
	return mInstance;
}
