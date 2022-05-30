#version 450

layout(location = 0) in vec3 fragPos;
layout(location = 1) in vec3 fragNorm;
layout(location = 2) in vec2 fragTexCoord;

layout(binding = 1) uniform sampler2D texSampler;

layout(binding = 2) uniform GlobalUniformBufferObject {
	vec3 lightDir;
	vec3 lightColor;
	vec3 eyePos;
} gubo;

layout(binding = 3) uniform sampler2D specSampler;

layout(location = 0) out vec4 outColor;

//-------------------------------------------------------------

vec3 blinn(vec3 N, vec3 V, vec3 Ldir, float gamma, vec3 color) {
	vec3 h = normalize(V + Ldir);
	return color * pow(clamp(dot(N,h), 0, 1), gamma);
}

//-------------------------------------------------------------

void main() {
    // sample texture
    vec3 albedo = texture(texSampler, fragTexCoord).rgb;
    vec3 specular = texture(specSampler, fragTexCoord).rgb;
    float specular_pow = 200.0f * texture(specSampler, fragTexCoord).a;

    // prepare other required data
    vec3 EyeDir = normalize(gubo.eyePos.xyz - fragPos);
    vec3 Norm = normalize(fragNorm);
    
    //compute color
    vec3 color = albedo;
	color += blinn(Norm, EyeDir, gubo.lightDir, specular_pow, specular);

    // compure light
    color *= gubo.lightColor;

    //output 
	outColor = vec4(color, 1.0f);
}