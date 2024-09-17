#pragma once
#include "MeshComponent.h"
class MyMesh :
    public MeshComponent
{
public:
	MyMesh(GLuint shaderProgram)
		: MeshComponent(shaderProgram, 100)
	{
		componentType = MESH;
	};

protected:
    virtual void buildMesh() override;
};

