#pragma once

#include <algorithm>

#include "MathLibsConstsFuncs.h"

using namespace constants_and_types;

/**
 * @enum	State
 *
 * @brief	An enumeration of the states of a game object.
 *
 * 			ACTIVE - Game object is in scene graph, and is is updated and "rendered"
 * 			PAUSED - Game object is in scene graph, but is not updated or "rendered"
 * 			DEAD - Game object will be removed from the game.
 */
enum STATE { ACTIVE, PAUSED, DEAD };


class GameObject : public std::enable_shared_from_this<GameObject>
{
public:

	friend class Component;

	/**
	 * @fn	GameObject();
	 *
	 * @brief	Constructor
	 *
	 */
	GameObject();

	/**
	 * @fn	virtual ~GameObject();
	 *
	 * @brief	Destructor. Deletes all dynamically allocated memory.
	 */
	virtual ~GameObject();

	/**
	 * @fn	void GameObject::addComponent(std::shared_ptr<class Component> component);
	 *
	 * @brief	Attaches a component to this game object
	 *
	 * @param 	component	If non-null, the component to attached.
	 */
	void addComponent(std::shared_ptr<class Component> component);

	/**
	 * @fn	void GameObject::initialize();
	 *
	 * @brief	Initializes this game object and all attached components and any
	 * 			children of the game object.
	 */
	void initialize();

	/**
	 * @fn	void GameObject::processInput();
	 *
	 * @brief	ProcessInput method called from Game (not overridable). Processes
	 * 			input for this game object and all attached.
	 */
	void processInput();

	/**
	 * @fn	virtual void GameObject::update(const float& deltaTime);
	 *
	 * @brief	Update function called from Game (not overridable). Updates this
	 * 			game object and all attached components.
	 *
	 * @param 	deltaTime	The time since the last update in seconds.
	 */
	virtual void update(const float& deltaTime);

	/**
	 * @fn	STATE GameObject::getState() const
	 *
	 * @brief	Gets the state of the game object.
	 *
	 * @returns	The state of the game object.
	 */
	STATE getState() const { return gameObjectState; }

	/**
	 * @fn	void GameObject::setState(STATE state);
	 *
	 * @brief	Sets a state of the game object. Only ACTIVE game objects are
	 * 			updated and rendered. When the state of an object is set to DEAD,
	 * 			it will be deleted on the next update cycle.
	 *
	 * @param 	state	The state to which the object is being set.
	 */
	void setState(STATE state);

	/**
	 * @fn	static void GameObject::SetOwningGame(class Game* owningGame)
	 *
	 * @brief	Sets owning game for this Component
	 *
	 * @param [in,out]	owningGame	If non-null, the owning game.
	 */
	static void SetOwningGame(class Game* owningGame) { GameObject::owningGame = owningGame; }

	/**
	 * @class	Game*
	 *
	 * @brief	A game*.
	 */
	static class Game* getOwningGame() { return owningGame; }

	/** @brief	Name of the game object */
	std::string gameObjectName = "GameObject";


	// (TEMPORARY) Modeling transformation for the GameObject 
	mat4 modelingTransformation;

protected:

	/** @brief	Current state of the game object */
	STATE gameObjectState = ACTIVE;

	/** @brief	The components that are attached to this game object. */
	std::vector<std::shared_ptr<class Component>> components;

	/**
	 * @class	Game*
	 *
	 * @brief	The game that this game object is part of.
	 */
	static class Game* owningGame;

}; // end GameObject class


