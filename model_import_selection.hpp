#pragma once

#include <filesystem>

struct ModelImportSelection {
	std::filesystem::path objPath;
	std::filesystem::path vertPath;
	std::filesystem::path fragPath;
	std::filesystem::path texturePath;
};
