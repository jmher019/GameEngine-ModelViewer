#ifndef MESH_FACTORY_HPP
#define MESH_FACTORY_HPP

#include <Mesh.hpp>
#include <MeshConstants.hpp>
#include <OBJLoader.hpp>

#include <unordered_map>

class MeshFactory {
private:
    static unordered_map<MeshConstants, shared_ptr<Mesh>> meshMap;
    static OBJLoader objLoader;

public:
    static void loadAndCacheMesh(const string& fileName, const MeshConstants& key) noexcept;

    static shared_ptr<Mesh> getMesh(const MeshConstants& key) noexcept;
};

#endif // !MESH_FACTORY_HPP
