#include"GraphicsDebugger.h"

GraphicsDebugger::GraphicsDebugger() {
	// You can add any initialization if necessary
}

//method returns string for each error type
//each error type in OpenGL is enum
std::string GraphicsDebugger::getGLErrorString(GLenum error) const {
	switch (error) {
	case GL_NO_ERROR: return "OpenGL error: No error.";
	case GL_INVALID_OPERATION: return "OpenGL error: Invalid operation.";
	case GL_INVALID_ENUM: return "OpenGL error: Invalid Enum.";
	case GL_INVALID_VALUE: return "OpenGL error: Invalid value.";
	case GL_OUT_OF_MEMORY: return "OpenGL error: Out of memory";
	case GL_STACK_UNDERFLOW: return "OpenGL error: Stack underflow.";
	case GL_STACK_OVERFLOW: return "OpenGL error: Stack overflow.";
	default: return "Unknown error.";
	}
}

//error callback function
void APIENTRY GraphicsDebugger::glErrorCallback(GLenum source, GLenum type, GLuint id,
	GLenum severity, GLsizei length,
	const GLchar* message, const void* userParam) {
	std::cerr << "OpenGL Error: " << message << std::endl;
}

// Method to set up the debug output
void GraphicsDebugger::SetupDebugOutput() {
	glEnable(GL_DEBUG_OUTPUT);
	glDebugMessageCallback(glErrorCallback, nullptr);
}

// Method to check for OpenGL errors
void GraphicsDebugger::checkOpenGLErrors(const std::string& context) const {
	GLenum error;
	while ((error = glGetError()) != GL_NO_ERROR) {
		std::cerr << "OpenGL Error in " << context << ": " << getGLErrorString(error) << std::endl;
	}
}