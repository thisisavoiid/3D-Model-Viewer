#pragma once

#include <filesystem>

class CubeMap {
public:
	unsigned m_id;
	CubeMap(
		std::filesystem::path right,
		std::filesystem::path left,
		std::filesystem::path top,
		std::filesystem::path bottom,
		std::filesystem::path front,
		std::filesystem::path back
	);
	~CubeMap();
	void Use();
};