#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>

#include "MathLibsConstsFuncs.h"
#include "GameObject.h"

#include "StaticGraphicsFunctions.h"
#include "SharedTransformations.h"

//The initial screen width when the game starts.
static const int initialScreenWidth = 1024;

//The initial screen height when the game starts.
static const int initialScreenHeight = 768;

// Desired maximum number of frames per second.
static const GLint FRAMES_PER_SECOND = 60; 

// Interval in milliseconds between frames.
static const GLdouble FRAME_INTERVAL = 1.0 / FRAMES_PER_SECOND;

using namespace constants_and_types;

class Game : public GameObject//, public std::enable_shared_from_this<Game>
{

public:

	// Allow GameObject methods to access protected and private members of the 
	// this class
	friend class GameObject;

	/**
	 * @fn	Game::Game(std::string windowTitle = "CSE489/589");
	 *
	 * @brief	Constructor
	 *
	 * @param 	windowTitle	(Optional) title for the rendering window.
	 */
	Game(std::string windowTitle = "Lab 3 CSE489/589");

	/**
	 * @fn	void Game::runGame();
	 *
	 * @brief	Initializes the game. Starts and runs the game loop. Frees
	 * 			resources after the game has ended.
	 */
	void runGame();

	/**
	 * @fn	Game::~Game();
	 *
	 * @brief	Destructor. Deletes all dynamically allocated memory and releases
	 * 			all resources.
	 */
	~Game();

	/**
	 * @fn	bool Game::gameIsInitialized()
	 *
	 * @brief	Determines if we can game is initialized and is 
	 * 			actively "running."
	 *
	 * @returns	True if it succeeds, false if it fails.
	 */
	bool gameIsRunning() { return isRunning; }

	/**
	 * @fn	void Game::window_close_callback();
	 *
	 * @brief	Callback, method that is called by a function when the window is
	 * 			closed. Sets isRunning to false to stop the game loop.
	 *
	 */
	void window_close_callback();

	/**
	 * @fn	void Game::framebuffer_size_callback(int width, int height);
	 *
	 * @brief	Callback, method that is called by a function when the
	 * 			framebuffer is resized; usually the	result of the rendering
	 * 			window being resized.
	 *
	 * @param 		  	width 	The width in pixels of the framebuffer.
	 * @param 		  	height	The height in pixels of the framebuffer.
	 *
	 */
	void framebuffer_size_callback(int width, int height);



protected:

	/**
	 * @fn	virtual bool Game::initializeGame();
	 *
	 * @brief	Initializes graphics as well as sound and physics engines. Loads
	 * 			the initial scene and initializes all game objects.
	 *
	 * @returns	True if it succeeds, false if it fails.
	 */
	virtual bool initializeGame();

	/**
	 * @fn	bool Game::initializeRenderWindow();
	 *
	 * @brief	Initializes the rendering window
	 *
	 * @returns	True if it succeeds, false if it fails.
	 */
	bool initializeRenderWindow();

	/**
	 * @fn	bool Game::initializeGraphics();
	 *
	 * @brief	Initializes the rendering API
	 *
	 * @returns	True if it succeeds, false if it fails.
	 */
	bool initializeGraphics();

	/**
	 * @fn	virtual void Game::loadScene() = 0;
	 *
	 * @brief	Creates game objects and attaches components. Created game
	 * 			objects are added to the game.
	 */
	virtual void loadScene() = 0;

	/**
	* @fn	void Game::addChildGameObject(GameObjectPtr gameObject);
	*
	* @brief	Adds a game object the game. The game object must not already be
	* 			parented.
	*
	* @param [in]	gameObject	If non-null, the game object to be added.
	*/
	void addChildGameObject(GameObjectPtr gameObject);

	/**
	 * @fn	void Game::gameLoop();
	 *
	 * @brief	Game loop. Repeatedly processes user input, updates all game
	 * 			objects, and renders the scene until isRunning is false and the
	 * 			game ends.
	 */
	void gameLoop();

	/**
	 * @fn	virtual void Game::processGameInput();
	 *
	 * @brief	Process the input
	 */
	virtual void processGameInput();

	/**
	 * @fn	virtual void Game::updateGame();
	 *
	 * @brief	Updates all game objects and the attached components.
	 */
	virtual void updateGame();

	/**
	 * @fn	void Game::renderScene();
	 *
	 * @brief	Renders the game scene.
	 */
	void renderScene();

	/**
	 * @fn	void Game::shutdown();
	 *
	 * @brief	Deletes all game objects in the game.
	 */
	void shutdown();

	/** @brief	True if the game is running (has been initialized), false if not */
	bool isRunning = false;

	/** @brief	Title for the window */
	std::string windowTitle;

	/** @brief	The rendering window */
	GLFWwindow* renderWindow = NULL;

	/** @brief	All the GameObjects in the Game */
	std::vector<std::shared_ptr<class GameObject>> children;

	/** @brief	A flag for esc key down */
	bool ESC_KeyDown = false;

	/** @brief	A flag for J key down */
	bool J_KeyDown = false;

	/** @brief wireframe mode */
	bool W_KeyDown = false;
	bool wireframeMode = false;

}; // end game class

//********************* static function declarations ********************

/**
 * @fn	static void framebufferResizeCallback(GLFWwindow* window, int width,
 * int height);
 *
 * @brief	Callback function (not method), called when the framebuffer is resized (occurs when the
 * 			window is resized).
 *
 * @param [in,out]	window	If non-null, the window.
 * @param 		  	width 	The width of the framebuffer in pixels.
 * @param 		  	height	The height of the framebuffer in pixels.
 */
static void framebufferResizeCallback(GLFWwindow* window, int width, int height);

/**
 * @fn	static void windowCloseCallback(GLFWwindow* window);
 *
 * @brief	Callback function (not method), called when the window is closed by the "X" in the
 * 			upper right hand window
 *
 * @param [in,out]	window	If non-null, the window.
 */
static void windowCloseCallback(GLFWwindow* window);

/**
 * @fn	static void cursorPositionCallback(GLFWwindow* window, double xpos, double ypos);
 *
 * @brief	Callback function (not method), called when cursor moves over the window
 *
 * @param [in,out]	window	If non-null, the window.
 * @param 		  	xpos 	Cursor position in x-axis, measured in screen coordinates but relative to the top-left corner
 * @param 		  	ypos 	Cursor position in y-axis, measured in screen coordinates but relative to the top-left corner
 */
static void cursorPositionCallback(GLFWwindow* window, double xpos, double ypos);

/**
 * @fn	static void cursorEnterCallback(GLFWwindow* window, int entered);
 *
 * @brief	Callback function (not method), called when cursor enters or leaves the window
 *
 * @param [in,out]	window	If non-null, the window.
 * @param 		  	entered GLFW_TRUE if the cursor entered the window's content area, or GLFW_FALSE if it left it.
 */
static void cursorEnterCallback(GLFWwindow* window, int entered);

/**
 * @fn	static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
 *
 * @brief	Callback function (not method), called when a mouse button is pressed or released
 *
 * @param [in,out]	window	If non-null, the window.
 * @param 		  	button 	The mouse button that was pressed or released.
 * @param 		  	action 	One of GLFW_PRESS or GLFW_RELEASE. Future releases may add more actions.
 * @param 		  	mods 	Bit field describing which modifier keys were held down.
 */
static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);

