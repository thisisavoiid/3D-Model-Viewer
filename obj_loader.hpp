#pragma once

#include "mesh.hpp"
#include <filesystem>

/// <summary>
/// Loads mesh data from Wavefront OBJ files.
/// </summary>
class ObjLoader {
public:
	MeshData LoadFromOBJ(const std::filesystem::path& path);
};