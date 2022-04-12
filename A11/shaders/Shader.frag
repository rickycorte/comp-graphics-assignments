#version 450

#define M_PI 3.1415926535897932384626433832795

layout(location = 0) out vec4 outColor;

layout(set = 0, binding = 1) uniform GlobalUniformBufferObject {
	float time;
} gubo;

void main() {
	outColor.r = gubo.time;
	outColor.g = 1 - gubo.time;
	outColor.b = gubo.time * gubo.time;
	outColor.a = 1.0f;
}