#version 450

layout(location = 0) in vec3 fragPos;
layout(location = 1) in vec3 fragNorm;
layout(location = 2) in vec2 fragTexCoord;

layout(binding = 1) uniform sampler2D texSampler;

layout(binding = 2) uniform GlobalUniformBufferObject {
	vec3 lightDir;
	vec3 lightPos;
	vec3 lightColor;
	vec4 lightParams;
	vec3 eyePos;
} gubo;

layout(binding = 3) uniform sampler2D specSampler;

layout(location = 0) out vec4 outColor;

//-------------------------------------------------------------

vec3 Lambert_Diffuse_BRDF(vec3 L, vec3 N, vec3 C) {
	// Lambert Diffuse BRDF model
	// in all BRDF parameters are:
	// vec3 L : light direction (d)
	// vec3 N : normal vector
	// vec3 C : main color (diffuse color, or specular color)
	
	vec3 diffuse = C * max(dot(L,N), 0);
	
	return diffuse;
}

vec3 Phong_Specular_BRDF(vec3 L, vec3 N, vec3 V, vec3 C, float gamma)  {
	// Phong Specular BRDF model
	// additional parameter:
	// float gamma : exponent of the cosine term
	vec3 r = -reflect(L, N);
	return C * pow(clamp(dot(V, r), 0, 1), gamma);
}

//-------------------------------------------------------------

vec3 point_light_color(vec3 pos) {
	// Point light color
	float decay = gubo.lightParams.w / length(gubo.lightPos - pos);
	decay = pow(decay, gubo.lightParams.z);
	return decay * gubo.lightColor;
}

vec3 spot_light_dir(vec3 pos) {
	// Spot light direction
	return normalize(gubo.lightPos - pos);
}

vec3 spot_light_color(vec3 pos) {
	// Spot light color
	vec3 point_l = point_light_color(pos);
	float alpha_cos = dot(spot_light_dir(pos), gubo.lightDir);
	float w = clamp( (alpha_cos - gubo.lightParams.y) / (gubo.lightParams.x  -gubo.lightParams.y ), 0 , 1);
	return point_l * w;
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
    vec3 color = Lambert_Diffuse_BRDF(gubo.lightDir, Norm, albedo);
    color += Phong_Specular_BRDF(gubo.lightDir, Norm, EyeDir, specular, specular_pow);

    // compure light
    color *= spot_light_color(fragPos);

    //output 
	outColor = vec4(color, 1.0f);
}