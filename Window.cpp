#include"Window.h"

//window constructor
//handles glfw init
Window::Window(int width, int height) {

	//init glfw
	if (!glfwInit()) {
		throw std::runtime_error("GLFW init failed!!");
	}

	//define openGL profiles and version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
	glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);

	//create glfw window
	window = glfwCreateWindow(width, height,"Formation Engine", nullptr, nullptr);

	if (!window) {
		glfwTerminate();
		throw std::runtime_error("Failed to create GLFW window");
	}

	//if window created successfully set it as current context
	glfwMakeContextCurrent(window);
}

//window destructor
Window::~Window() {
	glfwDestroyWindow(window);
	glfwTerminate();
}

//game loop related functions
//public: should close
bool Window::shouldClose() const{
	return glfwWindowShouldClose(window);
}

//public: swap buffers
void Window::swapBuffers() const {
	glfwSwapBuffers(window);
}

//public: pool events
void Window::pollEvents() const {
	glfwPollEvents();
}

GLFWwindow* Window::getNativeWindow() const{
	return window;
}
