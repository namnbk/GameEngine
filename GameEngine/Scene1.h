#pragma once

#include "GameEngine.h"

class Scene1 : public Game
{
	void loadScene() override
	{
		
		// Add GameObjects and Components here
		gameObject = make_shared<GameObject>();
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

		// Allocate the buffer for the uniform variable values and set
		// up binding points.
		SharedTransformations::setUniformBlockForShader(shaderProgram);

		// Bind the shader program
		glUseProgram(shaderProgram);

		// Add a trianlge mesh component
		ComponentPtr triangle =
			std::make_shared<Triangle3MeshComponent>(shaderProgram);
		gameObject->addComponent(triangle);

		// Game object added
		this->addChildGameObject(gameObject);
	} // end loadScene

	virtual void processGameInput()
	{
		Game::processGameInput();
		// Check if the '0' key is pressed and wasn't pressed before
		if (GLFW_PRESS == glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_0) && !zero_keyDown) {
			// Toggle rendering triangle
			if (gameObject.get()->getState() == ACTIVE) {
				gameObject.get()->setState(PAUSED);
			}
			else if (gameObject.get()->getState() == PAUSED) {
				gameObject.get()->setState(ACTIVE);
			}
			// set flag to true to avoid repeating while key is held down
			zero_keyDown = true;
		}
		else if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_0) == GLFW_RELEASE) {
			// reset flag to allow printing again when the key is pressed
			zero_keyDown = false;
		}
	}


protected:
	std::shared_ptr<GameObject> gameObject;
	bool zero_keyDown = false;

};
