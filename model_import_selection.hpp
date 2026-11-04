#pragma once

#include <filesystem>

/// <summary>
/// Stores the file paths selected for importing a model and its resources.
/// </summary>
struct ModelImportSelection {
	std::filesystem::path objPath;
	std::filesystem::path vertPath;
	std::filesystem::path fragPath;
	std::filesystem::path texturePath;
};
