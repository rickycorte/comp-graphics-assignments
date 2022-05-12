#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(binding = 1) uniform sampler2D texSampler;

layout(binding = 2) uniform GlobalUniformBufferObject {
	// Direct lights parameters (for diffuse and specular)
	vec3 lightDir0;
	vec3 lightColor0;
	vec3 lightDir1;
	vec3 lightColor1;
	vec3 lightDir2;
	vec3 lightColor2;
	vec3 lightDir3;
	vec3 lightColor3;

	// Ambient light parameters
	vec3 AmbColor;	// also Bottom color for Hemispheric light,
					//      Constant term for Spherical Harmonics light
	vec3 TopColor;	// also DyColor for Spherical Harmonics light
	vec3 DzColor;
	vec3 DxColor;
	
	// Other parameters (not relevant for the exercise)
	vec3 eyePos;
	vec4 selector;
} gubo;

/**** Modify from here *****/

layout(location=0) in vec3 fragPos;
layout(location=1) in vec3 fragNorm;
layout(location=2) in vec2 fragTexCoord;


layout(location=0) out vec4 outColor;


vec3 Case1_Color(vec3 N, vec3 V, vec3 Cd, vec3 Ca, float sigma) {
	// Oren Nayar Diffuse + Ambient
	// No Specular
	// One directional light (lightDir0 and lightColor0)
	//
	// Parameters are:
	//
	// vec3 N : normal vector
	// vec3 V : view direction
	// vec3 Cd : main color (diffuse color)
	// vec3 Ca : ambient color
	// float sigma : roughness of the material

	float sigma_sqr = pow(sigma, 2);

	float gamma_i = acos(dot(gubo.lightDir0, N));
	float gamma_r = acos(dot(V, N));

	float alpha = max(gamma_i, gamma_r);
	float beta = min(gamma_i, gamma_r);

	float a = 1 - 0.5 * (sigma_sqr / (sigma_sqr + 0.33));
	float b = 0.45 * (sigma_sqr / (sigma_sqr + 0.09));

	vec3 v_i = normalize(gubo.lightDir0 - dot(gubo.lightDir0,N) * N);
	vec3 v_r = normalize(V - dot(V, N) * N);

	float g = max(dot(v_i, v_r), 0);

	vec3 col = Cd * clamp(dot(gubo.lightDir0,N), 0, 1);

	vec3 oren = col * (a + b * g * sin(alpha) * tan(beta));

	return oren * gubo.lightColor0 + Ca * gubo.AmbColor;
	
}

vec3 Case2_Color(vec3 N, vec3 V, vec3 Cd, vec3 Ca) {
	// Lambert Diffuse + Hemispheric
	// No Specular
	// One directional light (lightDir0 and lightColor0)
	// Hemispheric light oriented along the y-axis
	//
	// Parameters are:
	//
	// vec3 N : normal vector
	// vec3 V : view direction
	// vec3 Cd : main color (diffuse color)
	// vec3 Ca : ambient color

	vec3 diffuse = Cd * max(dot(gubo.lightDir0,N), 0);

	float angle = dot(N, gubo.lightDir0);

	vec3 Hemi = (angle + 1)/2 * gubo.TopColor + (1-angle)/2 * gubo.AmbColor;
	
	return diffuse + Hemi * Ca;
}

vec3 blinn(vec3 N, vec3 V, vec3 Ldir, float gamma, vec3 color) {
	vec3 h = normalize(V + Ldir);
	return color * pow(clamp(dot(N,h), 0, 1), gamma);
}

vec3 Case3_Color(vec3 N, vec3 V, vec3 Cs, vec3 Ca, float gamma)  {
	// Spherical Harmonics
	// Blinn Specular
	// Four directional lights (lightDir0 to lightDir3, and lightColor0 to lightColor3)
	//
	// Parameters are:
	//
	// vec3 N : normal vector
	// vec3 V : view direction
	// vec3 Cs : specular color
	// vec3 Ca : ambient color
	// float gamma : Blinn exponent

	vec3 lights = gubo.lightColor0 * blinn(N, V, gubo.lightDir0, gamma, Cs) +
		gubo.lightColor1 * blinn(N, V, gubo.lightDir1, gamma, Cs) +
		gubo.lightColor2 * blinn(N, V, gubo.lightDir2, gamma, Cs) +
		gubo.lightColor3 * blinn(N, V, gubo.lightDir3, gamma, Cs);
		
	vec3 spher = gubo.AmbColor + N.x * gubo.DxColor + N.y * gubo.TopColor + N.z * gubo.DzColor;

	return lights + Ca * spher;
}



/**** To here *****/




void main() {
	vec3 Norm = normalize(fragNorm);
	vec3 EyeDir = normalize(gubo.eyePos.xyz - fragPos);
	
	float AmbFact = 0.025;
	
	vec3 DifCol = texture(texSampler, fragTexCoord).rgb * gubo.selector.w +
				  vec3(1,1,1) * (1-gubo.selector.w);

	vec3 CompColor = gubo.selector.x *
						Case1_Color(Norm, EyeDir, DifCol, DifCol, 1.2f) +
					 gubo.selector.y *
						Case2_Color(Norm, EyeDir, DifCol, DifCol) +
					 gubo.selector.z *
						Case3_Color(Norm, EyeDir, vec3(1.0f,1.0f,1.0f), DifCol, 200.0f);
	
	outColor = vec4(CompColor, 1.0f);	
}