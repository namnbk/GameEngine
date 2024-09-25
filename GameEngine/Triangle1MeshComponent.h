#pragma once
#include "MeshComponent.h"

class Triangle1MeshComponent :
	public MeshComponent
{
public:
	Triangle1MeshComponent(GLuint shaderProgram)
		: MeshComponent(shaderProgram, 100)
	{
		componentType = MESH;
	};



protected:
	virtual void buildMesh() override;
};