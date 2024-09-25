#pragma once
#include "MeshComponent.h"
class Triangle3MeshComponent :
    public MeshComponent
{
public:
	Triangle3MeshComponent(GLuint shaderProgram)
		: MeshComponent(shaderProgram, 100)
	{
		componentType = MESH;
	};



protected:
	virtual void buildMesh() override;
};

