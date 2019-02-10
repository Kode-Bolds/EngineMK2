#pragma once
#include <string>
#include <vector>
#include "../../Vertex.h"
#include <fstream>

static class ObjLoader
{
public:

	static std::pair<std::vector<unsigned>, std::vector<Vertex>> LoadObject(std::string& pFilename);
};

