#version 460 core

const int pointLights = 0;
const int directLights = 1;
const int projectedLights = 0;

layout (location = 0) in vec3 iPosition;
layout (location = 1) in vec3 iNormal;
layout (location = 2) in vec2 iTexCoords;
layout (location = 3) in vec3 iTangent;

struct PointLight
{
	vec3 position;
	vec3 color;
	float constant;
	float linear;
	float quadratic;
};

struct DirectLight
{
	vec3 direction;
	vec3 color;
};

struct ProjectedLight
{
	vec3 direction;
	vec3 position;
	vec3 color;
	float cutOff;
	float outCutOff;
};

uniform vec3 vievPosition;
uniform vec3 viewForward;
#ifdef direcLights
uniform DirectLight directLight;
#endif
#ifdef projectedLights
uniform ProjectedLight projectedLight;
#endif
#ifdef pointLights
uniform PointLight pointLight[pointLights];
#endif

uniform float iRatio;
uniform mat4 model;
uniform mat4 viev;
uniform mat4 projection;

out VS_OUT
{
	vec3 normal;
	vec3 fragPos;
	vec2 texCoords;
	vec3 vievPosition;
	vec3 viewForward;
	#ifdef directLights
	DirectLight directLight;
	#endif
	#ifdef projectedLights
	ProjectedLight projectedLight;
	#endif
	#ifdef pointLights
	PointLight pointLight[pointLights];
	#endif
} vs_out;

void main()
{
	//creating a TBN matrix to convert all vectors in tangent space
	vec3 T = normalize(vec3(model * vec4(iTangent, 0.0f)));
	vec3 N = normalize(vec3(model * vec4(iNormal, 0.0f)));
	T = normalize(T - dot(T, N) * N);//re ortohonalization
	vec3 B = normalize(cross(T, N));
	mat3 TBN = transpose(mat3(T, B, N));
	//textures
	vs_out.texCoords = iTexCoords;
	//translation to tangent space
	vs_out.normal = TBN * N;
	vs_out.fragPos = TBN * vec3(model * vec4(iPosition, 1.0f));
	vs_out.vievPosition = TBN * vievPosition;
	vs_out.viewForward = TBN * viewForward;
	#ifdef pointLight
	for (int i = 0; i < pointLights; i++)
	{
		vs_out.pointLight[i] = pointLight[i];
		vs_out.pointLight[i].position = TBN * pointLight[i].position;
	}
	#endif
	#ifdef projectedLights
	vs_out.projectedLight = projectedLight;
	vs_out.projectedLight.position = TBN * projectedLight.position;
	vs_out.projectedLight.direction = TBN * projectedLight.direction;
	#endif
	#ifdef direcLights
	vs_out.directLight = directLight;
	vs_out.directLight.direction = TBN * directLight.direction;
	#endif
	gl_Position = projection * viev * model * vec4(iPosition, 1.0f) * iRatio;
}