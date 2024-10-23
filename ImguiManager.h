#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include<imgui.h>
#include<imgui_impl_glfw.h>
#include<imgui_impl_opengl3.h>
#include<iostream>
#include<vector>
#include"ShapeFactory.h"
#include"ShapeFactory.h"
#include"Scene.h"
#include<string>
#include"SceneObjectType.h"
#include"Triangle.h"
using namespace std;

class ImguiManager {
private:
	Scene& scene;
	ShapeFactory& shapeFactory;
	vector<bool> triangleSelectBoolean;

	//variables to store input text data for vertices handling of shapes
	//triangle 9 vertex positions
	char inputBuffer1[256] = "0.0";
	char inputBuffer2[256] = "0.0";
	char inputBuffer3[256] = "0.0";
	char inputBuffer4[256] = "0.0";
	char inputBuffer5[256] = "0.0";
	char inputBuffer6[256] = "0.0";
	char inputBuffer7[256] = "0.0";
	char inputBuffer8[256] = "0.0";
	char inputBuffer9[256] = "0.0";

	//handling menu windows with help of booleans
	bool creditsWindow=false;
	bool documentationWindow=false;
	bool featureWindow = false;
public:
	//init imgui
	void initImgui(GLFWwindow* window);

	//clean up after glfw window is destroyed
	void cleanUp();

	//Init hierarchy panel
	void createHierarchyPanel(const char* title, float x, float y, float width, float height);

	//init inspector panel
	void createInspectorPanel(const char* title, float x, float y, float width, float height);

	//create menu items
	void createMenuItems();

	//create a imgui frame and the inspector and hierarchy windows along with it: static windows
	void createFrame();

	//parametrized construcor
	//initializes instances of scene and shape factory
	ImguiManager(Scene& scene, ShapeFactory& shapeFactory)
		: scene(scene), shapeFactory(shapeFactory) {}

	//set all selectable boolean to false
	//we do this every time before we select an object
	void setSelectablesFalse();

};