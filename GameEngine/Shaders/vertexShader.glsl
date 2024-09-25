// Targeting version 4.5 of GLSL. 
#version 460 core

layout(shared) uniform transformBlock
{
	mat4 modelMatrix;
	mat4 normalModelMatrix;
	mat4 viewMatrix;
	mat4 projectionMatrix;
};

in vec4 position;

/**
// Declare a hard-coded array of positions
const vec4 vertices[3] = vec4[3](vec4(-0.25, -0.25, 0.0, 1.0),
								 vec4(0.25, -0.25, 0.0, 1.0),
                                 vec4(0.0, 0.25, 0.0, 1.0));
*/

void main()
{
    // Calculate the position in clip coordinates
     gl_Position = projectionMatrix * viewMatrix * modelMatrix * position;
}