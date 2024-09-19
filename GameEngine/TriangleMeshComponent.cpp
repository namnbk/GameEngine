#include "TriangleMeshComponent.h"

void TriangleMeshComponent::buildMesh()
{
	SubMesh subMesh;
	// Generate and bind a vertex array object.
	// Store the identifier for the vertex array object in the subMesh
	glGenVertexArrays(1, &subMesh.vao);
	glBindVertexArray(subMesh.vao);

	subMesh.primitiveMode = GL_TRIANGLES;
	subMesh.renderMode = ORDERED;
	subMesh.count = 3;

	// Add to the subMeshes that are part of the mesh component
	subMeshes.push_back(subMesh);

}