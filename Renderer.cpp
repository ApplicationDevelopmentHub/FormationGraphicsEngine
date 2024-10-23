#include"Renderer.h"

//public: setup bg color
void Renderer::clear(float r, float g, float b, float a) {
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

//generates a random bg color every frame
void Renderer::clear() {
	//generate random values and assign to r,g,b, keep a 1
	random_device rd; //obtain a random number from hardware
	default_random_engine engine(rd()); //seed the random number generator

	//define range and distribution of random number
	uniform_int_distribution<int> distribution(1,100);

	//generate random numbers for r,g,b
	float r = distribution(engine)/100;
	float g = distribution(engine) / 100;
	float b = distribution(engine) / 100;

	glClearColor(r, g, b, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::initShaders() {
	if (shaderManager) { // Check if shaderManager is valid
		shaderManager->use(); // Use the shader program
	}
	else {
		std::cerr << "ShaderManager is not initialized!" << std::endl;
		throw std::runtime_error("ShaderManager is not initialized");
	}
}
