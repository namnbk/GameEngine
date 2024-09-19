#pragma once
#include "MeshComponent.h"
class TriangleMeshComponent :
    public MeshComponent
{
public:
	TriangleMeshComponent(GLuint shaderProgram)
		: MeshComponent(shaderProgram, 100)
	{
		componentType = MESH;
	};



protected:
    virtual void buildMesh() override;

	virtual void draw();
};

