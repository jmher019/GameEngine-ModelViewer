#ifndef SHADER_FACTORY_HPP
#define SHADER_FACTORY_HPP

#include <Shader.hpp>
#include <ShaderConstants.hpp>
#include <unordered_map>

class ShaderFactory {
private:
    static unordered_map<ShaderConstants, shared_ptr<Shader>> shaderMap;

public:
    static void loadAndCacheShader(const string& vertexPath, const string& fragmentPath, const ShaderConstants& key) noexcept;

    static shared_ptr<Shader> getShader(const ShaderConstants& key) noexcept;
};

#endif // !SHADER_FACTORY_HPP
