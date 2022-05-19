#version 460 core

#define PARALLAX_MAPPING
#define MATERIAL_RANDOMIZE
const float PI = 3.1415926535;
const int pointLights = 0;
const int directLights = 1;
const int projectedLights = 0;

struct Material
{
	sampler2D albedoMap1;
	sampler2D normalMap1;
	sampler2D armMap1;
	sampler2D depthMap1;
};

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

uniform Material material;
uniform float heightScale;

uniform highp mat4 projection;
uniform vec2 iResolution;
uniform float iUVScale;
uniform vec2 iUVOffsetMult;
uniform float iUVRotate;

out vec4 FragCol;

in VS_OUT
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
} fs_in;

//prototypes
vec3 BRDF(vec3 C, vec3 L, vec3 H, vec3 V, vec3 N, vec3 F0, vec3 albedo, float roughness, float metallic, float attenuation);
float DistributionGGX(vec3 n, vec3 h, float roughness); //D
vec3 FrenselSchlick(float hvDot, vec3 F0); //F
float GeometrySmith(vec3 n, vec3 v, vec3 l, float roughness); //G
vec2 ParallaxMapping(vec2 texCoords, vec3 V, vec3 N, vec3 VF);
vec3 voronoi(vec2 x);

//PBR
void main()
{
	vec3 L0 = vec3(0.0f);
	vec3 V = normalize(fs_in.vievPosition - fs_in.fragPos);
	vec3 N = normalize(fs_in.normal);
	vec3 VF = normalize(fs_in.viewForward);	

	vec2 texCoords = fs_in.texCoords;
	vec2 texCoords2 = texCoords;
	vec3 tmp = vec3(texCoords, 0.0);
	float blend = 1.0f;
	float offset = 0;

	#ifdef MATERIAL_RANDOMIZE
	tmp = fs_in.fragPos;
	vec3 voron = voronoi(tmp.xy * iUVScale);
	offset = dot(voron.yz, vec2(0.3f, 0.5f)) + 0.25;
	blend -= mix(vec3(0.75), vec3(0.0), smoothstep( 0.04, 0.08, voron.x )).r;	
	float angle = offset * iUVRotate;
	float tcos = cos(angle), tsin = sin(angle); 
	tmp.x = texCoords.x * tcos - texCoords.y * tsin;
	tmp.y = texCoords.x * tsin + texCoords.y * tcos;
	texCoords = tmp.xy + offset * iUVOffsetMult;
	#endif

	#ifdef PARALLAX_MAPPING
	texCoords = ParallaxMapping(texCoords, V, N, VF);
	texCoords2 = ParallaxMapping(texCoords2, V, N, VF);
	#endif

	//material data
	tmp = texture(material.albedoMap1, texCoords2).rgb;
	vec3 albedo = texture(material.albedoMap1, texCoords).rgb;
	albedo = mix(tmp, albedo, blend);	
	tmp = texture(material.normalMap1, texCoords2).rgb;
	vec3 normal = texture(material.normalMap1, texCoords).rgb;
	normal = mix(tmp, normal, blend);	
	tmp = texture(material.armMap1, texCoords2).rgb;
	vec3 arm = texture(material.armMap1, texCoords).rgb;
	arm = mix(tmp, arm, blend);	
	float ao = arm.r;
	float roughness = arm.g;
	float metallic = arm.b;
	albedo = pow(albedo, vec3(2.2f));//sRGB => linear
	normal = normalize(normal * 2.0f - vec3(1.0f));

	N = normalize(N + normal);	
	vec3 F0 = vec3(0.04); //constant 4% for non-metall
	F0 = mix(F0, albedo, metallic);
	
	
	#ifdef pointLights
	for (int i = 0; i < pointLights; i++)
	{
		vec3 L = normalize(fs_in.pointLight[i].position - fs_in.fragPos);
		vec3 H = normalize(V + L); //mediane between ray and view direction
		float dist = length(fs_in.pointLight[i].position - fs_in.fragPos);
		float attenuation = 1.0f / (fs_in.pointLight[i].constant + fs_in.pointLight[i].linear * dist + fs_in.pointLight[i].quadratic * dist * dist);
		L0 += BRDF(fs_in.pointLight[i].color, L, H, V, N, F0, albedo, roughness, metallic, attenuation);
	}
	#endif
	#ifdef directLights
	vec3 C = fs_in.directLight.color;
	vec3 L = fs_in.directLight.direction;
	vec3 H = normalize(V + L);
	L0 += BRDF(C, L, H, V, N, F0, albedo, roughness, metallic, 1.0);
	#endif
	vec3 ambient = vec3(0.03f) * albedo * ao;
	vec3 color = L0 + ambient;
	//Gamma correction(linear => sRGB)
	color = color / (color + vec3(1.0));
    color = pow(color, vec3(1.0/2.2));
	FragCol = vec4(color, 1.0f);//vec3(offset * blend)
}

vec3 BRDF(vec3 C, vec3 L, vec3 H, vec3 V, vec3 N, vec3 F0, vec3 albedo, float roughness, float metallic, float attenuation)
{
	vec3 radiance = C * attenuation;
	//dots
	float hvDot = max(dot(H, V), 0.0f);
	float nvDot = max(dot(N, V), 0.0f);
	float nlDot = max(dot(N, L), 0.0f);
		
	//BRDF Cook-Torrance		
	vec3 F = FrenselSchlick(hvDot, F0);
	float NDF = DistributionGGX(N, H, roughness);
	float G = GeometrySmith(N, V, L, roughness);

	vec3 numerator = NDF * G * F;
	// 0.001 to denom never be zero
	float denominator = 4.0f * nvDot * nlDot + 0.001f;
	vec3 specular = numerator / denominator;

	vec3 kS = F;
	vec3 kD = vec3(1.0f) - kS;
	kD *= 1.0f - metallic;

	return (kD * albedo / PI + specular) * radiance * nlDot;
}

//Trowbridge-Reitz GGX
float DistributionGGX(vec3 n, vec3 h, float roughness)
{
	float a = roughness * roughness;
	float a2 = a * a;
	float nhDot = max(dot(n, h), 0.0f);
	float nhDot2 = nhDot * nhDot;

	float denom = nhDot * nhDot * (a2 - 1.0f) + 1.0f;
	denom = PI * denom * denom;
	return a2 / denom;
}

float GeometrySchlickGGX(float nvDot, float roughness)
{
	float r = 1.0f + roughness;
	float k = (r * r) / 8.0f;
	float denom = nvDot * (1.0f - k) + k;
	return nvDot / denom;
}

float GeometrySmith(vec3 n, vec3 v, vec3 l, float roughness)
{
	float nvDot = max(dot(n, v), 0.0f);
	float nlDot = max(dot(n, l), 0.0f);

	float ggx1 = GeometrySchlickGGX(nvDot, roughness); //overlay
	float ggx2 = GeometrySchlickGGX(nlDot, roughness); //ambient occ

	return ggx1 * ggx2;
}

vec3 FrenselSchlick(float hvDot, vec3 F0)
{
	return F0 + (1.0f - F0) * pow(1.0f - hvDot, 5.0f);
}

vec2 ParallaxMapping(vec2 texCoords, vec3 V, vec3 N, vec3 VF)
{
	float minNumLayers = 6.0f;
	float maxNumLayers = 64.0f;
	float d = dot(V, N);
	float c = dot(VF, N);

	float numLayers = mix(maxNumLayers, minNumLayers, abs(d));
	float layerDepth = 1.0f / numLayers;
	float currentDepth = 0.0f;

	vec4 k = projection * vec4(d * N - V, 1.0f);
	vec2 t = vec2(k.x * sign(d) + k.y * sign(-d),  k.x * sign(d) + k.y * sign(d));
	float scale = heightScale;
	vec2 dTexCords = t * scale / numLayers / max(abs(d), 0.75f);
	
	vec2 currentTexCoords = texCoords;
	float depth = 1.0f - texture(material.depthMap1, currentTexCoords).r;

	while (currentDepth < depth)
	{
		currentTexCoords -= dTexCords;
		depth = 1.0f - texture(material.depthMap1, currentTexCoords).r;
		currentDepth += layerDepth;
	}

	vec2 prevTexCoords = currentTexCoords;
	prevTexCoords += dTexCords;

	float afterDepth = depth - currentDepth;
	float beforeDepth = 1.0f - texture(material.depthMap1, prevTexCoords).r - currentDepth + layerDepth;

	float weight = afterDepth / (afterDepth - beforeDepth);
	vec2 finalTexCoords = prevTexCoords * weight + currentTexCoords * (1.0f - weight);

	return finalTexCoords;
}

vec2 hash2( vec2 p )
{
    // procedural white noise	
	return fract(sin(vec2(dot(p,vec2(127.1,311.7)),dot(p,vec2(269.5,183.3))))*43758.5453);
}

//to randomize each fragment
vec3 voronoi(vec2 x)
{
    vec2 n = floor(x);
    vec2 f = fract(x);

    // first pass: regular voronoi
	vec2 mpoint, mdiff, mneig;
    float mdist = 1.0;

    for( int j=-1; j<=1; j++ )
    for( int i=-1; i<=1; i++ )
    {
        vec2 neighbor = vec2(float(i),float(j));
		vec2 point = hash2(n + neighbor);
        vec2 diff = neighbor + point - f;
        float dist = dot(diff, diff);

        if(dist < mdist)
        {
            mdist = dist;
			mdiff = diff;
            mpoint = point;
			mneig = neighbor;
        }
    }

    // second pass: distance to borders
    mdist = 1.0;
    for(int j= -2; j <= 2; j++)
    for(int i= -2; i <= 2; i++)
    {
        vec2 neighbor = mneig + vec2(float(i), float(j));
		vec2 point = hash2(n + neighbor);
        vec2 diff = neighbor + point - f;

        if(dot(mdiff - diff, mdiff - diff) > 0.0001)
        mdist = min(mdist, dot(0.5 * (mdiff + diff), normalize(diff - mdiff)));
    }

    return vec3(mdist, mpoint);
}