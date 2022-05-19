#version 460 core

layout (location = 0) in vec3 iPosition;

uniform mat4 model;
uniform mat4 viev;
uniform mat4 projection;

void main()
{
	gl_Position = projection * viev * model * vec4(iPosition, 1.0f);
}