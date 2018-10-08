#version 460 core
layout (location = 0) in vec3 pos; // position
layout (location = 1) in vec3 norm; // normal
layout (location = 2) in vec3 color; // color
layout (location = 3) in vec2 texCoord; // texture position

out vec4 outColor; // specify a color output to the fragment shader;

uniform mat4 PVM;
uniform mat4 model;

void main() {
	gl_Position = PVM * vec4(pos, 1.f); // see how we directly give a vec3 to vec4's constructor
    outColor = vec4((norm + vec3(1.f, 1.f, 1.f)) * 0.5f, 1.f);
}