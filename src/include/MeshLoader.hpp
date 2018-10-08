#ifndef MESH_LOADER_HPP
#define MESH_LOADER_HPP

#include <vector>
#include <string>

#include <Vertex.hpp>

class MeshLoader {
public:
    virtual ~MeshLoader(void) {};

    virtual vector<Vertex> loadMesh(const string& fileName) const noexcept = 0;
};

#endif // !MESH_LOADER_HPP
