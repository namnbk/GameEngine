// Targeting version 4.5 of GLSL. 
#version 460 core

layout(location = 500) uniform vec4 objectColor;

out vec4 fragmentColor;

void main()
{
	fragmentColor = objectColor;
}