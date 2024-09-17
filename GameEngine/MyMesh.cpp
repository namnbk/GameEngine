#include "MyMesh.h"

void MyMesh::buildMesh()
{
	SubMesh subMesh;
	glGenVertexArrays(1, &subMesh.vao);
	glBindVertexArray(subMesh.vao);
}