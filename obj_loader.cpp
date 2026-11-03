#include "obj_loader.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include "vertex.hpp"

MeshData ObjLoader::LoadFromOBJ(const std::filesystem::path& path)
{
	MeshData data;

	std::ifstream file(path);
	std::string line;

	if (!file.is_open()) {
		std::cerr << "File with path " << path << " could not be opened / read sucessfully!\n";
		return data;
	}
	else {
		std::cout << "File with path " << path << " opened successfully!\n";
	}

	std::vector<glm::vec3> objRawVertices;
	std::vector<glm::vec2> objRawUvs;
	std::vector<glm::vec3> objRawNormals;

	std::vector<Vertex> objFinalVertices;

	while (std::getline(file, line)) {
		std::stringstream ss(line);
		std::string type;

		ss >> type;

		if (type == "v") {
			float x, y, z;
			ss >> x >> y >> z;
			objRawVertices.emplace_back(x, y, z);
		}
		else if (type == "vt") {
			float x, y;
			ss >> x >> y;
			objRawUvs.emplace_back(x, y);
		}
		else if (type == "vn") {
			float x, y, z;
			ss >> x >> y >> z;
			objRawNormals.emplace_back(x, y, z);
		}
		else if (type == "f") {
			std::string vertex;

			while (ss >> vertex) {
				std::stringstream vs;
				vs << vertex;

				char slash;

				int vIdx, vtIdx, vnIdx;
				vs >> vIdx >> slash >> vtIdx >> slash >> vnIdx;

				vIdx--;
				vtIdx--;
				vnIdx--;

				objFinalVertices.emplace_back(
					objRawVertices[vIdx],
					objRawUvs[vtIdx],
					objRawNormals[vnIdx]
				);
			}
		}
	}

	for (int i = 0; i < objFinalVertices.size(); i++) {
		data.vertices.push_back(objFinalVertices[i].position.x);
		data.vertices.push_back(objFinalVertices[i].position.y);
		data.vertices.push_back(objFinalVertices[i].position.z);

		data.indices.push_back(i);

		data.uvs.push_back(objFinalVertices[i].uvCoords.x);
		data.uvs.push_back(objFinalVertices[i].uvCoords.y);

		data.normals.push_back(objFinalVertices[i].normal.x);
		data.normals.push_back(objFinalVertices[i].normal.y);
		data.normals.push_back(objFinalVertices[i].normal.z);

		std::cout
			<< "Position: "
			<< objFinalVertices[i].position.x << ", "
			<< objFinalVertices[i].position.y << ", "
			<< objFinalVertices[i].position.z << "\n"

			<< "UV: "
			<< objFinalVertices[i].uvCoords.x << ", "
			<< objFinalVertices[i].uvCoords.y << "\n"

			<< "Normal: "
			<< objFinalVertices[i].normal.x << ", "
			<< objFinalVertices[i].normal.y << ", "
			<< objFinalVertices[i].normal.z << "\n"

			<< "--------------------\n";
	}

    return data;
}
