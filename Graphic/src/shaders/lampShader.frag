#version 460 core

out vec4 FragCol;

uniform vec3 lightColor;

void main()
{
	FragCol = vec4(lightColor, 1.0f);
}