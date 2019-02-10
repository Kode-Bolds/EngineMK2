#include "ResourceManager.h"

using namespace std;

//TODO: Test singleton pattern works
ResourceManager::ResourceManager() = default;
ResourceManager::~ResourceManager() = default;

std::pair<std::shared_ptr<ID3D11Buffer>, std::shared_ptr<ID3D11Buffer>> ResourceManager::LoadGeometry(const std::string & pFilename)
{
	auto geometry = ObjLoader::LoadObject(pFilename);
	return std::pair<std::shared_ptr<ID3D11Buffer>, std::shared_ptr<ID3D11Buffer>>();
}

std::shared_ptr<ResourceManager> ResourceManager::Instance()
{
	static shared_ptr<ResourceManager> instance{new ResourceManager};
	return instance;
}
