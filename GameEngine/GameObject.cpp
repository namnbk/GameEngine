#include "GameObject.h"

#include "Component.h"
//#include "MeshComponent.h"

#include "Game.h"

#define VERBOSE false

// ***** Definition of static members of the Game Object class *****
Game* GameObject::owningGame;

// ********************************************************************

GameObject::GameObject()
	: gameObjectState(ACTIVE)
{
	if (VERBOSE) cout << gameObjectName << "game object constructed" << endl;
}


GameObject::~GameObject()
{
	// Remove the game object from the game
	if (VERBOSE) cout << "GameObject destructor called on " << gameObjectName << "game object" << endl;
	 
} // end GameObject destructor


void GameObject::initialize()
{
	// Initialize the components that are attached to this game object
	for (auto & component : components) {

		component->initialize();
	}

} // end initialize

void GameObject::update(const float & deltaTime)
{
	// Check to see if this game object is active
	if (gameObjectState == ACTIVE) {

		// Update the components that are attached to to this game object
		for (auto & component : this->components) {

			component->update(deltaTime);
		}

	}

} // end update

void GameObject::processInput()
{
	// Check to see if this game object is active
	if (gameObjectState == ACTIVE) {

		// First process input for components
		for (auto & component : this->components) {
			component->processInput();
		}
	}

} // end processInput


void GameObject::addComponent(std::shared_ptr<Component> component)
{
	// Dependency injection (give the Component a reference to this GameObject
	component->owningGameObject = shared_from_this();

	// Add the component to the components vector
	components.emplace_back(component);

	// Sort the components vector based on their update order.
	std::sort(components.begin(), components.end(), Component::CompareUpdateOrder);

	// Check if the component is a MeshComponent
	if (component->getComponentType() == MESH) {

		// Add the mesh to the static vector of MeshComponents
		// TODO
	}

} // end addComponent



void GameObject::setState(STATE state)
{
	gameObjectState = state;
}




