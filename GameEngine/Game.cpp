#include "GameEngine.h"
// #include <GL/glew.h> // Must be included before glfw
// #include <GLFW/glfw3.h>
// #include <stdexcept>


#define VERBOSE false

//********************* Initialization Methods *****************************************

Game::Game(std::string windowTitle)
	: windowTitle(windowTitle)
{

} // end Game Constructor

void Game::runGame()
{
	// Initialize the game
	bool success = initializeGame();

	// Enter the game loop
	if (success) {
		gameLoop();
	}

	// Free up resources
	shutdown();

} // end runGame

Game::~Game()
{
	if (VERBOSE) cout << "Game destructor " << endl;

} // end Game Destructor

bool Game::initializeGame()
{
	// Initialize the various libararies and Engines
	bool windowInit = initializeRenderWindow();
	bool graphicsInit = initializeGraphics();

	// Check if all libraries initialized correctly
	if (windowInit && graphicsInit)
	{
		// Set the owner of all the GameObject (temporary)
		GameObject::SetOwningGame(this);

		// Build the scene graph
		loadScene();

		// Explicitly call the resize method to set the initial projection transformation


		// Start an initialize all of the GameObjects in the game
		for (auto& gameObject : this->children) {

			gameObject->initialize();
		}

		if (VERBOSE) cout << "Game Initialized." << endl;

		// Return true to indicate the game has initialized
		return true;
	}
	else
	{
		std::cerr << "Game Initialization Failure." << endl;

		// Return false to indicate the game did not initialize correctly
		return false;
	}

} // end initialize

bool Game::initializeRenderWindow()
{
	// Initialize the GLFW and create a rendering window. If a failure, then exit

	if (!glfwInit()) {
		throw std::runtime_error("Could not initilize GLFW!");
	}

	// Specify that OpenGL will be the client API for the rendering context
	glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);

	// Specify the OpenGL major and minor version and use the core OpenGL profile
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create window in debug mode for additional error and diagnostic reporting 
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);

	// Flush the rendering pipeline when the context is released from being current
	glfwWindowHint(GLFW_CONTEXT_RELEASE_BEHAVIOR, GLFW_RELEASE_BEHAVIOR_FLUSH);

	// Explicitly request double buffers i.e. two frame buffers
	glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE);

	// Register function to get GLFW error messages displayed on the console
	glfwSetErrorCallback(glfw_error_callback);

	// Create rendering window and the OpenGL context.
	renderWindow = glfwCreateWindow(initialScreenWidth, initialScreenHeight, windowTitle.c_str(), NULL, NULL);

	if (!renderWindow) {

		std::cerr << "Render Window Creation Failure." << endl;
		std::cerr << "Make sure requested OpenGL version is supported." << endl;
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(renderWindow);

	// Set the swap interval for the OpenGL context i.e. the number of screen 
	// updates to wait between before swapping the buffer and returning.
	glfwSwapInterval(1);

	// Register window resize callback function
	glfwSetFramebufferSizeCallback(renderWindow, framebufferResizeCallback);

	// Register window close function
	glfwSetWindowCloseCallback(renderWindow, windowCloseCallback);

	// Register mouse callback function
	glfwSetCursorPosCallback(renderWindow, cursorPositionCallback);

	// Register mouse enter/leave callback function
	glfwSetCursorEnterCallback(renderWindow, cursorEnterCallback);

	// Register mouse press/released
	glfwSetMouseButtonCallback(renderWindow, mouseButtonCallback);

	// Set this game as the user application associated with the rendering window.
	glfwSetWindowUserPointer(renderWindow, this);

	if (VERBOSE) cout << "Render Window Initialized" << endl;

	return true;

} // end initializeRenderWindow

bool Game::initializeGraphics()
{
	// ****** Initialize GLEW *********

	// Prevent possible initialization error when using the core context
	glewExperimental = GL_TRUE;

	GLenum res = glewInit(); // Must be done after glut is initialized!

	if (res != GLEW_OK) {

		fprintf(stderr, "Error: '%s'\n", glewGetErrorString(res));
		return false;
	}

	// On some platforms, GLEW will emit a benign error code. So clear it.
	glGetError();

	// ********* Initialize OpenGL **************

	// Register OpenGL error callback to print error 
	// messages to the console
	glEnable(GL_DEBUG_OUTPUT);
	glDebugMessageCallback(openglMessageCallback, 0);

	// Enable Depth testing
	glEnable(GL_DEPTH_TEST);

	// Cull back faces of polygons
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);

	// Render "filled in" polygons
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	// Set source and destination blending functions
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Display info
	displayOpenGlInfo();

	// Clear color 
	glClearColor(LIGHT_PINK_RGBA.r, LIGHT_PINK_RGBA.g, LIGHT_PINK_RGBA.b, LIGHT_PINK_RGBA.a);

	if (VERBOSE) cout << "Graphics Initialized" << endl;
	
	return true;

} // end initializeGraphics

void Game::addChildGameObject(GameObjectPtr gameObject)
{
	if (gameObject != NULL) {

		// Add directly to the vector of game objects in the game.
		children.emplace_back(gameObject);

	}

} // end addGameObject


//********************* Run Methods *****************************************

void Game::gameLoop()
{
	isRunning = true;

	while (isRunning) {
		processGameInput();
		updateGame();
		renderScene();
	}

	if (VERBOSE) cout << "Exited Game Loop" << endl;

} // end gameLoop

void Game::processGameInput()
{
	if (VERBOSE) cout << " Processing Scene Input." << endl;

	// Listening to keyboard input
	if (GLFW_PRESS == glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_ESCAPE) && ESC_KeyDown == false) {
		// exit the program
		isRunning = false;
		// set the flag
		ESC_KeyDown = true;
	}
	else if (GLFW_RELEASE == glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_ESCAPE)) {
		// set the flag
		ESC_KeyDown = false;
	}

	// Check if the 'j' key is pressed and wasn't pressed before
	if (GLFW_PRESS == glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_J) && !J_KeyDown) {
		// print 'j' followed by a space
		cout << "j " << endl;
		// set flag to true to avoid repeating while key is held down
		J_KeyDown = true;
	}
	else if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_J) == GLFW_RELEASE) {
		// reset flag to allow printing again when the key is pressed
		J_KeyDown = false; 
	}

	// Start an input traversal of all GameObjects in the game
	for (auto& gameObject : this->children) {

		gameObject->processInput();
	}

} // end processInput

void Game::updateGame()
{
	if (VERBOSE) cout << " Updating Scene." << endl;

	// Compute delta time
	static double lastRenderTime = glfwGetTime(); // static initilization only occurs once
	double currentTime = glfwGetTime();
	float deltaTime = static_cast<float>(currentTime - lastRenderTime);

	if (deltaTime > 0.05f) {
		deltaTime = 0.05f;
	}

	if (deltaTime >= FRAME_INTERVAL) {

		// Call callback functions for registered events

		// Processes events that are already in the event queue by 
		// calling registered window and input callback functions 
		glfwPollEvents();


		// Start an update traversal of all GameObjects in the game
		for (auto& gameObject : this->children) {
			gameObject->update(deltaTime);
		}


		// Update the last time the game was updated
		lastRenderTime = currentTime;
	}

} // end updateGame()

void Game::renderScene()
{
	if (VERBOSE) cout << " Rendering Scene!" << endl;

	// Clear the color and depth buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Render loop
	// TODO

	// Swap the front and back buffers
	glfwSwapBuffers(renderWindow);
} // end renderScene

//********************* Shutdown Methods *****************************************

void Game::shutdown()
{
	// Destroy the window
	glfwDestroyWindow(renderWindow);

	// Frees GLFW allocated resources
	glfwTerminate();
	
	if (VERBOSE) cout << "Game Shutdown Complete" << endl;

} // end shutDown

//********************* Accessor Methods *****************************************



//********************* Event Handlers *****************************************
void Game::window_close_callback()
{
	cout << "window close" << endl;
	// Stop the game loop
	this->isRunning = false;
} // end window_close_callback

void Game::framebuffer_size_callback(int width, int height)
{
	cout << "Window resized to" << width << "x" << height << "pixels." << endl;
	// Set parameters for the window transformation ...
	glViewport(0, 0, width, height);
	
	// Set the projection transformation ...
	// TODO

} // end framebuffer_size_callback



//********************* static function definitions *****************************************
static void framebufferResizeCallback(GLFWwindow* window, int width, int height) {
	// Cast the user point to a Game* type
	Game* that = static_cast<Game*>(glfwGetWindowUserPointer(window));

	// Call the Game class method
	that->framebuffer_size_callback(width, height);
}

static void windowCloseCallback(GLFWwindow* window) {
	// Cast the user point to a Game* type
	Game* that = static_cast<Game*>(glfwGetWindowUserPointer(window));

	// Call the Game class method
	that->window_close_callback();
}

static void cursorPositionCallback(GLFWwindow* window, double xpos, double ypos) {
	cout << "The (x, y) position is (" << xpos << ", " << ypos << ")" << endl;
}

static void cursorEnterCallback(GLFWwindow* window, int entered)
{
	if (entered)
	{
		// The cursor entered the content area of the window
		cout << "The cursor entered the content area of the window" << endl;
	}
	else
	{
		// The cursor left the content area of the window
		cout << "The cursor left the content area of the window" << endl;
	}
}

static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS) {
		cout << "Mouse button right is pressed." << endl;
	}
	else if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE) {
		cout << "Mouse button right is released." << endl;
	}
	else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
		cout << "Mouse button left is pressed." << endl;
	}
	else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {
		cout << "Mouse button left is released." << endl;
	}
}