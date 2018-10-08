#include <ShaderFactory.hpp>

unordered_map<ShaderConstants, shared_ptr<Shader>> ShaderFactory::shaderMap;

void ShaderFactory::loadAndCacheShader(const string& vertexPath, const string& fragmentPath, const ShaderConstants& key) noexcept {
    shared_ptr<Shader> shader = make_shared<Shader>(vertexPath, fragmentPath);

    if (shaderMap.count(key) != 0) {
        shaderMap.erase(shaderMap.find(key));
    }

    shaderMap[key] = shader;
}

shared_ptr<Shader> ShaderFactory::getShader(const ShaderConstants& key) noexcept {
    return shaderMap[key];
}