#pragma once
#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include<iostream>

using namespace std;

class Window {
private:
	GLFWwindow* window;
public:
	//constructor
	//name of the window will always be predefined as Formation engine
	//init glfw
	//create glfw window
	Window(int width, int height);

	//destructor
	~Window();

	//game loop related functions
	bool shouldClose() const;
	void swapBuffers() const;
	void pollEvents() const;

	GLFWwindow* getNativeWindow() const;
};