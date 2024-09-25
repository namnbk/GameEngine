#include "Triangle3MeshComponent.h"



void Triangle3MeshComponent::buildMesh()
{
	// Submess define
	SubMesh subMesh;

	// Generate and bind a vertex array object.
	// Store the identifier for the vertex array object in the subMesh
	glGenVertexArrays(1, &subMesh.vao);
	glBindVertexArray(subMesh.vao);

    // Define 8 unique positions
    std::vector<glm::vec4> positions = {
        glm::vec4(0.0f,  0.75f,  0.0f, 1.0f),  // Top
        glm::vec4(0.75f, 0.0f,   0.0f, 1.0f),  // Right
        glm::vec4(0.0f,  -0.75f, 0.0f, 1.0f),  // Bottom
        glm::vec4(-0.75f, 0.0f,  0.0f, 1.0f),  // Left
        glm::vec4(-0.25f, 0.25f, 0.0f, 1.0f),  // Upper-left
        glm::vec4(0.25f,  0.25f, 0.0f, 1.0f),  // Upper-right
        glm::vec4(-0.25f, -0.25f, 0.0f, 1.0f), // Lower-left
        glm::vec4(0.25f,  -0.25f, 0.0f, 1.0f)  // Lower-right
    };

    // Define indices (18 total) for 6 triangles
    std::vector<GLuint> indices = {
        // Triangle 1 (Top-Upper-right-Upper-left)
        0, 4, 5,
        // Triangle 2 (Upper-right-Right-Lower-right)
        5, 7, 1,
        // Triangle 3 (Upper-left-Upper-right-Lower-right)
        4, 7, 5,
        // Triangle 4 (Upper-left-Lower-right-Lower-left)
        4, 6, 7,
        // Triangle 5 (Lower-right-Bottom-Lower-left)
        7, 6, 2,
        // Triangle 6 (Upper-left-Lower-left-Left)
        4, 3, 6
    };

    // Create a buffer and load the vertex positions and colors into it.
    // Store the identifier for the buffer in the subMesh.
    glGenBuffers(1, &subMesh.vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, subMesh.vertexBuffer);

    // Copy the data into the buffer object
    glBufferData(GL_ARRAY_BUFFER, positions.size() * sizeof(vec4), &positions[0], GL_STATIC_DRAW);

    // Specify the location and data format of the vertex positions
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(vec4), 0);

    // Enable the flow of the positions into the vertex shader
    glEnableVertexAttribArray(0);

    // Generate and bind EBO (Element Buffer Object)
    glGenBuffers(1, &subMesh.indexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, subMesh.indexBuffer);

    // Copy data
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices[0], GL_STATIC_DRAW);

    // Unbind VAO
    glBindVertexArray(0);

	subMesh.primitiveMode = GL_TRIANGLES;
	subMesh.renderMode = INDEXED;
	subMesh.count = indices.size();
	subMesh.material.basicColor = BLUE_RGBA;

	// Add to the subMeshes that are part of the mesh component
	subMeshes.push_back(subMesh);
}