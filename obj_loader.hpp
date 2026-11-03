#pragma once

#include "mesh.hpp"
#include <filesystem>

class ObjLoader {
public:
	MeshData LoadFromOBJ(const std::filesystem::path& path);
};