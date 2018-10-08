#include <MeshFactory.hpp>

unordered_map<MeshConstants, shared_ptr<Mesh>> MeshFactory::meshMap;
OBJLoader MeshFactory::objLoader;

void MeshFactory::loadAndCacheMesh(const string& fileName, const MeshConstants& key) noexcept {
    shared_ptr<Mesh> mesh = make_shared<Mesh>(objLoader.loadMesh(string(fileName)));

    if (meshMap.count(key) != 0) {
        meshMap.erase(meshMap.find(key));
    }

    meshMap[key] = mesh;
}

shared_ptr<Mesh> MeshFactory::getMesh(const MeshConstants& key) noexcept {
    return meshMap[key];
}