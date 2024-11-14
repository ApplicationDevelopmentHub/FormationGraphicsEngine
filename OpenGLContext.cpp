#include"OpenGLContext.h"

//Constructor
OpenGLContext::OpenGLContext(GLFWwindow* window) {
	//if window is not there, throw an error
	//window must be created before OpenGL context
	if (!window) {
		throw std::runtime_error("Window must be created before OpenGL context.");
	}

	glewExperimental = true; //for core profile

	//initialize glew
	//throw error if not initialized correctly
	if (glewInit()!=GLEW_OK) {
		throw std::runtime_error("Failed to initialize GLEW");
	}
}
