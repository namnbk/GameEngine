#pragma once

#include "MathLibsConstsFuncs.h"


/**
 * @fn	void glfw_error_callback(int error, const char* description);
 *
 * @brief	Callback function (not method), that is called when there is a GLFW error
 *
 * @param 	error	   	The error.
 * @param 	description	The description.
 */
void glfw_error_callback(int error, const char* description);

/**
 * @fn	void displayOpenGlInfo(void);
 *
 * @brief	Displays an open gl information/
 */
void displayOpenGlInfo(void);

/**
 * @fn	void GLAPIENTRY openglMessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam);
 *
 * @brief	Callback function (not method), that called when an OpenGL error occurs.
 *
 * @param 	source   	Source for the.
 * @param 	type	 	The type.
 * @param 	id		 	The identifier.
 * @param 	severity 	The severity. See
 * 						https://www.khronos.org/registry/OpenGL/extensions/KHR/KHR_debug.txt
 * 						for description.
 * @param 	length   	The length.
 * @param 	message  	The message.
 * @param 	userParam	The user parameter.
 *
 * @returns	A GLAPIENTRY.
 */
void GLAPIENTRY openglMessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity,
	GLsizei length, const GLchar* message, const void* userParam);