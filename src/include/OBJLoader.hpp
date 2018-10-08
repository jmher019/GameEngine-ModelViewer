#ifndef OBJ_LOADER_HPP
#define OBJ_LOADER_HPP

#include <fstream>

#include <MeshLoader.hpp>
#include <StringUtils.hpp>

class OBJLoader : public MeshLoader {
public:
    OBJLoader(void);

    vector<Vertex> loadMesh(const string& fileName) const noexcept override;
};

#endif // !OBJ_LOADER_HPP
