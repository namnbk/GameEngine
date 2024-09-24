// Targeting version 4.5 of GLSL. 
#version 460 core

layout(location = 100) uniform mat4 projectionMatrix;
layout(location = 101) uniform mat4 viewMatrix;
layout(location = 102) uniform mat4 modelMatrix;

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