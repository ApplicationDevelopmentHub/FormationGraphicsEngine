#include"ShaderManager.h"

//constructor
ShaderManager::ShaderManager(const std::string& vertexShaderPath, const std::string& fragmentShaderPath) {
	//load vertex shader
	std::string vertexCode = loadShader(vertexShaderPath);
	const char* vShaderCode = vertexCode.c_str();

	//load fragment shader
	std::string fragmentCode = loadShader(fragmentShaderPath);
	const char* fShaderCode = fragmentCode.c_str();

	//compile shaders
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1,&vShaderCode,nullptr);
	compileShader(vertexShader); //custom function, not glcompileshader

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fShaderCode, nullptr);
	compileShader(fragmentShader); //custom function, not gl compile shader

	//create shader program and link shaders
	shaderProgramID = glCreateProgram();
	glAttachShader(shaderProgramID, vertexShader);
	glAttachShader(shaderProgramID, fragmentShader);
	glLinkProgram(shaderProgramID);

	GLint success;
	glGetProgramiv(shaderProgramID, GL_LINK_STATUS, &success);
	if (!success) {
		char infoLog[512];
		glGetProgramInfoLog(shaderProgramID, 512, nullptr, infoLog);
		throw std::runtime_error("Shader program linking failed: " + std::string(infoLog));
	}
	else {
		cout << "Shader program linking success." << endl;
	}

	//clean up shaders after linking the program
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

//method to use the shader program
void ShaderManager::use() {
	//std::cout << "Using shader program ID: " << shaderProgramID << std::endl;
	if (shaderProgramID > 0) {
		glUseProgram(shaderProgramID);
	}
	else {
		std::cout << "ERROR::SHADER::USE::PROGRAM_ID_IS_INVALID" << std::endl;
		throw std::runtime_error("Invalid shader program ID");
	}
}

std::string ShaderManager::loadShader(const std::string& path) {
	std::ifstream shaderFile(path);
	if (!shaderFile.is_open()) {
		throw std::runtime_error("Could not open shader file: " + path);
	}

	std::stringstream shaderStream;
	shaderStream << shaderFile.rdbuf(); // Read the shader code
	return shaderStream.str();
}

//compiling shaders
void ShaderManager::compileShader(GLuint shader) {
	glCompileShader(shader);

	// Check for compile errors
	GLint success;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		char infoLog[512];
		glGetShaderInfoLog(shader, 512, nullptr, infoLog);
		throw std::runtime_error("Shader compilation failed: " + std::string(infoLog));
	}
	else {
		cout << "Shader compiled successfully" << endl;
	}
}