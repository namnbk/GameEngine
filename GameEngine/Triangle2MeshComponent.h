#pragma once
#include "MeshComponent.h"
class Triangle2MeshComponent :
    public MeshComponent
{
public:
	Triangle2MeshComponent(GLuint shaderProgram)
		: MeshComponent(shaderProgram, 100)
	{
		componentType = MESH;
	};



protected:
	virtual void buildMesh() override;
};

