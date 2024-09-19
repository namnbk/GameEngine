// Targeting version 4.5 of GLSL. 
#version 460 core

mat4 projectionMatrix; 
mat4 viewMatrix; 
mat4 modelMatrix;

out vec4 vertexColor;

// Declare a hard-coded array of positions
const vec4 vertices[3] = vec4[3](vec4(-0.25, -0.25, 0.0, 1.0),
								 vec4(0.25, -0.25, 0.0, 1.0),
                                 vec4(0.0, 0.25, 0.0, 1.0));

// Declare a hard-coded array of colors
const vec4 colors[3] = vec4[3](vec4(0.9, 0.1, 0.1, 1.0),
                                 vec4(0.1, 0.9, 0.1, 1.0),
                                 vec4(0.1, 0.1, 0.9, 1.0));

void main()
{
     // Index into our array using gl_VertexID
     gl_Position = vertices[gl_VertexID];
	 vertexColor = colors[gl_VertexID];

}