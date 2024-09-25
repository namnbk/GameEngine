#pragma once

#include "GameEngine.h"

class Scene1 : public Game
{
	void loadScene() override
	{
		
		// Add GameObjects and Components here
		for (int i = 0; i < numberOfObj; i++) {
			gameObjects.push_back(make_shared<GameObject>());
		}
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

		// Add triangle mesh component
		for (int i = 0; i < numberOfObj; i++) {
			// add component for each game object
			ComponentPtr triangle;
			if (i == 0) {
				triangle = std::make_shared<TriangleMeshComponent>(shaderProgram);
			}
			else if (i == 1) {
				triangle = std::make_shared<Triangle1MeshComponent>(shaderProgram);
			}
			else if (i == 2) {
				triangle = std::make_shared<Triangle2MeshComponent>(shaderProgram);
			}
			else if (i == 3) {
				triangle = std::make_shared<Triangle3MeshComponent>(shaderProgram);
			}
			gameObjects[i]->addComponent(triangle);
			// only the first object is active
			if (i > 0) {
				gameObjects[i].get()->setState(PAUSED);
			}
		}

		// Game object added
		for (int i = 0; i < numberOfObj; i++) {
			this->addChildGameObject(gameObjects[i]);
		}
	} // end loadScene

	virtual void processGameInput()
	{
		Game::processGameInput();

		for (int i = 0; i < numberOfObj; i++) {
			// Check if the '0' key is pressed and wasn't pressed before
			if (GLFW_PRESS == glfwGetKey(glfwGetCurrentContext(), keys[i]) && !keydowns[i]) {
				// Toggle rendering state for current object
				if (gameObjects[i].get()->getState() == ACTIVE) {
					gameObjects[i].get()->setState(PAUSED);
				}
				else if (gameObjects[i].get()->getState() == PAUSED) {
					gameObjects[i].get()->setState(ACTIVE);
				}
				// Set other game object to PAUSE
				for (int j = 0; j < numberOfObj; j++) {
					if (j == i) {
						continue;
					}
					gameObjects[j].get()->setState(PAUSED);
				}
				// set flag to true to avoid repeating while key is held down
				keydowns[i] = true;
			}
			else if (glfwGetKey(glfwGetCurrentContext(), keys[i]) == GLFW_RELEASE) {
				// reset flag to allow printing again when the key is pressed
				keydowns[i] = false;
			}
		}
		
	}

protected:
	std::vector<std::shared_ptr<GameObject>> gameObjects;
	std::vector<bool> keydowns = { false, false, false, false };
	std::vector<GLuint> keys = { GLFW_KEY_0, GLFW_KEY_1, GLFW_KEY_2, GLFW_KEY_3 };
	int numberOfObj = 4;
};
