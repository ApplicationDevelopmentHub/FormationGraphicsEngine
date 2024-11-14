#pragma once
#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include<iostream>
#include<random>
#include<thread>
#include<chrono>
#include<ctime>
#include"ShaderManager.h"

using namespace std;

class Renderer {
private:
	//instance of shader manager to init shaders
	std::unique_ptr<ShaderManager> shaderManager;
public:
	//setting up the screen background color in game loop
	void clear(float r, float g, float b, float a);

	//generates random background at a specified time interval
	void clear();

	//init shaders
	void initShaders();

	//constructor to use parameters in shadermanager
	Renderer(const std::string& vertexShaderPath, const std::string& fragmentShaderPath) {
		// Initialize shader manager in the constructor
		shaderManager = std::make_unique<ShaderManager>(vertexShaderPath, fragmentShaderPath);
	}
};