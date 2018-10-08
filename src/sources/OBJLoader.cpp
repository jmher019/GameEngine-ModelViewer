#include <OBJLoader.hpp>

OBJLoader::OBJLoader(void) {}

vector<Vertex> OBJLoader::loadMesh(const string& fileName) const noexcept {
    ifstream inputFile;
    inputFile.open(fileName, ifstream::in);

    vector<vec3> coords;
    vector<vec3> colors;
    vector<vec3> norms;
    vector<vec2> texCoords;
    vector<Vertex> vertices;

    string line;
    while (inputFile) {
        getline(inputFile, line);

        // Skip comments
        if (line.empty() || line.at(0) == '#') {
            continue;
        }

        vector<string> results = move(StringUtils::split(line, ' '));

        // Check if we have a coordinate, texture coordinate, normal, or face
        const string& attribute = results[0];

        // We have a face
        if (attribute.at(0) == 'f' && results.size() == 4) {
            vector<string> ptIndices1 = move(StringUtils::split(results[1], '/'));
            vector<string> ptIndices2 = move(StringUtils::split(results[2], '/'));
            vector<string> ptIndices3 = move(StringUtils::split(results[3], '/'));

            if (ptIndices1.size() == 1) {
                const int index1 = stoi(ptIndices1[0]) - 1;
                const int index2 = stoi(ptIndices2[0]) - 1;
                const int index3 = stoi(ptIndices3[0]) - 1;
                const vec3& pt1 = coords[index1];
                const vec3& pt2 = coords[index2];
                const vec3& pt3 = coords[index3];
                const vec3 n = normalize(cross(pt2 - pt1, pt3 - pt1));
                const vec3& c1 = colors.empty() ? (n + vec3(1.f, 1.f, 1.f)) * 0.5f : colors[index1];
                const vec3& c2 = colors.empty() ? (n + vec3(1.f, 1.f, 1.f)) * 0.5f : colors[index2];
                const vec3& c3 = colors.empty() ? (n + vec3(1.f, 1.f, 1.f)) * 0.5f : colors[index3];

                vertices.push_back(
                    Vertex(
                        pt1,
                        n,
                        c1,
                        vec2(0.f, 0.f)
                    )
                );

                vertices.push_back(
                    Vertex(
                        pt2,
                        n,
                        c2,
                        vec2(0.f, 0.f)
                    )
                );

                vertices.push_back(
                    Vertex(
                        pt3,
                        n,
                        c3,
                        vec2(0.f, 0.f)
                    )
                );
            }
            else if (ptIndices1.size() == 2) {
                const int index1 = stoi(ptIndices1[0]) - 1;
                const int index2 = stoi(ptIndices2[0]) - 1;
                const int index3 = stoi(ptIndices3[0]) - 1;
                const int texCoordIndex1 = stoi(ptIndices1[1]) - 1;
                const int texCoordIndex2 = stoi(ptIndices2[1]) - 1;
                const int texCoordIndex3 = stoi(ptIndices3[1]) - 1;
                const vec3& pt1 = coords[index1];
                const vec3& pt2 = coords[index2];
                const vec3& pt3 = coords[index3];
                const vec2& vt1 = texCoords[texCoordIndex1];
                const vec2& vt2 = texCoords[texCoordIndex1];
                const vec2& vt3 = texCoords[texCoordIndex1];
                const vec3 n = normalize(cross(pt2 - pt1, pt3 - pt1));
                const vec3& c1 = colors.empty() ? (n + vec3(1.f, 1.f, 1.f)) * 0.5f : colors[index1];
                const vec3& c2 = colors.empty() ? (n + vec3(1.f, 1.f, 1.f)) * 0.5f : colors[index2];
                const vec3& c3 = colors.empty() ? (n + vec3(1.f, 1.f, 1.f)) * 0.5f : colors[index3];

                vertices.push_back(
                    Vertex(
                        pt1,
                        n,
                        c1,
                        vt1
                    )
                );

                vertices.push_back(
                    Vertex(
                        pt2,
                        n,
                        c2,
                        vt2
                    )
                );

                vertices.push_back(
                    Vertex(
                        pt3,
                        n,
                        c3,
                        vt3
                    )
                );
            }
            else if (ptIndices1.size() == 3) {
                const int index1 = stoi(ptIndices1[0]) - 1;
                const int index2 = stoi(ptIndices2[0]) - 1;
                const int index3 = stoi(ptIndices3[0]) - 1;
                const int texCoordIndex1 = ptIndices1[1].empty() ? 0 : stoi(ptIndices1[1]) - 1;
                const int texCoordIndex2 = ptIndices2[1].empty() ? 0 : stoi(ptIndices2[1]) - 1;
                const int texCoordIndex3 = ptIndices3[1].empty() ? 0 : stoi(ptIndices3[1]) - 1;
                const int normalIndex1 = stoi(ptIndices1[2]) - 1;
                const int normalIndex2 = stoi(ptIndices2[2]) - 1;
                const int normalIndex3 = stoi(ptIndices3[2]) - 1;
                const vec3& pt1 = coords[index1];
                const vec3& pt2 = coords[index2];
                const vec3& pt3 = coords[index3];
                const vec2& vt1 = texCoords.empty() ? vec2(0.f, 0.f) : texCoords[texCoordIndex1];
                const vec2& vt2 = texCoords.empty() ? vec2(0.f, 0.f) : texCoords[texCoordIndex1];
                const vec2& vt3 = texCoords.empty() ? vec2(0.f, 0.f) : texCoords[texCoordIndex1];
                const vec3& n1 = norms[normalIndex1];
                const vec3& n2 = norms[normalIndex2];
                const vec3& n3 = norms[normalIndex3];
                const vec3& c1 = (n1 + vec3(1.f, 1.f, 1.f)) * 0.5f;// colors.empty() ? (n1 + vec3(1.f, 1.f, 1.f)) * 0.5f : colors[index1];
                const vec3& c2 = (n2 + vec3(1.f, 1.f, 1.f)) * 0.5f;// colors.empty() ? (n2 + vec3(1.f, 1.f, 1.f)) * 0.5f : colors[index2];
                const vec3& c3 = (n3 + vec3(1.f, 1.f, 1.f)) * 0.5f;// colors.empty() ? (n3 + vec3(1.f, 1.f, 1.f)) * 0.5f : colors[index3];

                vertices.push_back(
                    Vertex(
                        pt1,
                        n1,
                        c1,
                        vt1
                    )
                );

                vertices.push_back(
                    Vertex(
                        pt2,
                        n2,
                        c2,
                        vt2
                    )
                );

                vertices.push_back(
                    Vertex(
                        pt3,
                        n3,
                        c3,
                        vt3
                    )
                );
            }
        }
        // We have a vertex (coordinate, texture coordinate, or normal)
        else if (attribute.at(0) == 'v') {
            // We have a coordinate
            if (attribute.length() == 1) {
                // We have x y z or x y z w only
                if (results.size() == 4 || results.size() == 5) {
                    coords.push_back(
                        vec3(
                            stof(results[1]),
                            stof(results[2]),
                            stof(results[3])
                        )
                    );
                }
                // We have x y z r g b only
                else if (results.size() == 7) {
                    coords.push_back(
                        vec3(
                            stof(results[1]),
                            stof(results[2]),
                            stof(results[3])
                        )
                    );

                    colors.push_back(
                        vec3(
                            stof(results[4]),
                            stof(results[5]),
                            stof(results[6])
                        )
                    );
                }
                // We have x y z w r g b
                else if (results.size() == 8) {
                    coords.push_back(
                        vec3(
                            stof(results[1]),
                            stof(results[2]),
                            stof(results[3])
                        )
                    );

                    colors.push_back(
                        vec3(
                            stof(results[5]),
                            stof(results[6]),
                            stof(results[7])
                        )
                    );
                }
            }
            // We have a normal
            else if (attribute.at(1) == 'n' && results.size() == 4) {
                norms.push_back(
                    normalize(
                        vec3(
                            stof(results[1]),
                            stof(results[2]),
                            stof(results[3])
                        )
                    )
                );
            }
            // We have a texture coordinate
            else if (attribute.at(1) == 't' && results.size() == 3) {
                texCoords.push_back(
                    vec2(
                        stof(results[1]),
                        stof(results[2])
                    )
                );
            }
        }
    }

    return vertices;
}