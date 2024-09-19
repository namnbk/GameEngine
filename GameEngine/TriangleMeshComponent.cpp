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

void TriangleMeshComponent::draw() {
	// Bind the shader program for the MeshComponent
	glUseProgram(shaderProgram);

	// Render all subMeshes in this MeshComponent
	for (auto& subMesh : subMeshes) {

		// Bind vertex array object for the subMesh
		glBindVertexArray(subMesh.vao);

		// Determine if sequential(ordered) or indexed 
		// rendering will be used to render the sub Mesh
		if (subMesh.renderMode == ORDERED) {

			// Trigger vertex fetch for ordered rendering 					
			glDrawArrays(subMesh.primitiveMode, 0, subMesh.count);
		}
	}
}