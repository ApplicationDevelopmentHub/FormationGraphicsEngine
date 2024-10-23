#pragma once
#include<GL/glew.h>
#include<string>
#include<stdexcept>
#include<string>
#include<fstream>
#include<sstream>
#include<iostream>

using namespace std;

class ShaderManager {
private:
	GLuint shaderProgramID;
	std::string loadShader(const std::string& path);
	void compileShader(GLuint shader);
public:
	//constructor
	ShaderManager(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
	void use();	
	GLuint getID() const { return shaderProgramID; }
};
