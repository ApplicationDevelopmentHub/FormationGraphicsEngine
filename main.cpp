#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include<iostream>
#include<memory>

#include"Window.h"
#include"OpenGLContext.h"
#include"Renderer.h"
#include"ShapeFactory.h"
#include"GraphicsDebugger.h"
#include"UIWindow.h"
#include"ImguiManager.h"
#include"Scene.h"
#include"SceneObjectType.h"

using namespace std;

int main() {
	try {
		//window object: GLFW
		Window window(1920, 1080);

		//opengl object: GLEW
		OpenGLContext currentContext(window.getNativeWindow());

		
		//OpenGL debugger
		GraphicsDebugger graphicsDebugger;
		graphicsDebugger.SetupDebugOutput();

		//Shape factory object
		ShapeFactory shapeFactory;

		//instance of the scene class
		//stores all primitive shapes and renders them
		//selectable object type and index
		SceneObjectType type = SceneObjectType::NONE;
		Scene scene(type,0);

		//create Imgui context and init after glew and glfw
		ImguiManager imguiManager(scene,shapeFactory);
		imguiManager.initImgui(window.getNativeWindow());

		//Renderer object
		//shader manager is initalized with renderer's parameter
		Renderer renderer("vertex_shader_1.glsl", "fragment_shader_1.glsl");
		renderer.initShaders();	

		//DEMONSTRATION: false error checking for error logging program
		//glBindBuffer(GL_ARRAY_BUFFER, 999);  // Invalid buffer ID to generate an error
		//graphicsDebugger.checkOpenGLErrors("Buffer");

		while (!window.shouldClose()) {
			
			//uniform color
			//rendering logic before each frame
			renderer.clear(0.0f, 0.0f, 0.0f, 1.0f);

			//create imgui frame and render inspector and hierarchy windows
			//updates every frame
			imguiManager.createFrame();

			//check for OpenGL errors
			graphicsDebugger.checkOpenGLErrors("Clear");

			renderer.initShaders();
			// Draw the triangle: default constructor
			//if (triangle) {
			//	static_cast<Triangle*>(triangle.get())->draw(); // Draw the triangle
			//}
			//Render all shapes stored in the Scene class
			scene.renderAllShapes();

			window.swapBuffers();
			window.pollEvents();
		}
		imguiManager.cleanUp();
	}
	catch(const std::exception& e){
		cout << e.what() << endl;
		return -1;
	}
	return 0;
}