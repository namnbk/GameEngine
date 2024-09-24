#pragma once

#include "GameEngine.h"

class Scene1 : public Game
{
	void loadScene() override
	{
		
		// Add GameObjects and Components here
		GameObjectPtr  gameObject = make_shared<GameObject>();
		/*
		// Nam component
		ComponentPtr myFirstComponent = make_shared<NamComponent>();
		gameObject->addComponent(myFirstComponent);
		// Camera component
		ComponentPtr cameraComponent = make_shared<CameraComponent>();
		gameObject->addComponent(cameraComponent);
		*/

		// Build shader program
		ShaderInfo shaders[] = {
			{ GL_VERTEX_SHADER, "Shaders/vertexShader.glsl" },
			{ GL_FRAGMENT_SHADER, "Shaders/fragmentShader.glsl" },
			{ GL_NONE, NULL } // signals that there are no more shaders 
		};

		// Build the shader program
		GLuint shaderProgram = BuildShaderProgram(shaders);

		// Bind the shader program
		glUseProgram(shaderProgram);

		// Add a trianlge mesh component
		ComponentPtr triangle =
			std::make_shared<TriangleMeshComponent>(shaderProgram);
		gameObject->addComponent(triangle);

		// Game object added
		this->addChildGameObject(gameObject);
	} // end loadScene
	
};
