#pragma once
#include<GL/glew.h>
#include<iostream>
#include<string>
#include<Windows.h>

class GraphicsDebugger {
private:
	//converts error code to string for better user experience
	std::string getGLErrorString(GLenum error) const;

	//error callback function
	static void APIENTRY glErrorCallback(GLenum source, GLenum type,
		GLuint id, GLuint severity, GLsizei length,
		const GLchar* message, const void* userParam);
public:
	//constructor
	GraphicsDebugger();

	//setting up debug output
	void SetupDebugOutput();

	//method to check for OpenGL errors
	void checkOpenGLErrors(const std::string& context) const;
};
