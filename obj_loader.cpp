#include "obj_loader.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include "vertex.hpp"

/// <summary>
/// Loads vertex, texture, normal, and index data from an OBJ file.
/// </summary>
/// <param name="path">
/// The path to the OBJ file.
/// </param>
/// <returns>
/// The mesh data parsed from the file, or empty mesh data if the file cannot be opened.
/// </returns>
MeshData ObjLoader::LoadFromOBJ(const std::filesystem::path& path)
{
    MeshData data;

    std::ifstream file(path);
    std::string line;

    if (!file.is_open()) {
        std::cerr << "File with path " << path
            << " could not be opened / read successfully!\n";
        return data;
    }

    std::cout << "File with path " << path
        << " opened successfully!\n";

    std::vector<glm::vec3> objRawVertices;
    std::vector<glm::vec2> objRawUvs;
    std::vector<glm::vec3> objRawNormals;

    std::vector<Vertex> objFinalVertices;

    try {
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
                    std::stringstream vs(vertex);

                    char slash;
                    int vIdx = 0, vtIdx = 0, vnIdx = 0;

                    if (!(vs >> vIdx >> slash) || slash != '/' ||
                        !(vs >> vtIdx >> slash) || slash != '/' ||
                        !(vs >> vnIdx)) {
                        throw std::runtime_error("Invalid face format: " + vertex);
                    }

                    vIdx--;
                    vtIdx--;
                    vnIdx--;

                    objFinalVertices.emplace_back(
                        objRawVertices.at(vIdx),
                        objRawUvs.at(vtIdx),
                        objRawNormals.at(vnIdx)
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
        }

        return data;
    }
    catch (const std::exception& e) {
        std::cerr << "OBJ Loading Error: " << e.what() << '\n';
        return MeshData{};
    }
}