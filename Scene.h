#pragma once
#include<memory>
#include"Shapes.h"
#include"Triangle.h"
#include"Rectangle.h"
#include"SceneObjectType.h"
#include"functional"

//Scene graph: holds scene data
//subject for subject observer pattern to select scene objects and display in inspector
//observer will the imgui manager class
class Scene {
private:
	int itemCount; //total number of items, all types of items

	//individual primitive type lists
	//2D
	vector<std::unique_ptr<Triangle>> triangleList;
	//vector<std::unique_ptr<Rectangle>> rectangleList;
	//vector<std::unique_ptr<Circle>> polygonList;
	/*vector<std::unique_ptr<Polygon>> polygonList;
	
	//3D
	vector<std::unique_ptr<Prism>> polygonList;
	vector<std::unique_ptr<Cylinder>> polygonList;
	vector<std::unique_ptr<Capsule>> polygonList;
	vector<std::unique_ptr<Cuboid>> cubeList;
	vector<std::unique_ptr<Cone>> coneList;
	vector<std::unique_ptr<Sphere>> sphereList;
	vector<std::unique_ptr<Floor>> floorList;*/

	//selected object details
	SceneObjectType selectedObjectType;
	int selectedObjectID;

	//list of observers: imgui manager
	vector<std::function<void()>> observers;
public:
	//Subject-observer pattern for selection-inspector
	void notifyObservers(); //subject-observer pattern for inspector with ImguiManager
	void registerObservers(std::function<void()> observer); //observer pattern: register observers: imgui manager

	void renderAllShapes(); //this will be called in the main function in the glfw game loop

	int getItemCount(); //select number of active objects in the scene

	//Selected object in hierarchy
	SceneObjectType getSelectedItemType() { return selectedObjectType; } 	//return the selected item type
	int getSelectedItemIndex() { return selectedObjectID; } 	//return the selected item index

	//primitives created used shape factory, recorded here
	void addTriangle(std::unique_ptr<Shapes> triangle);
	//void addRectangle(std::unique_ptr<Shapes> rectangle);

	//how many specific primitives are in current session
	int getTriangleCount();

	//get triangle id by index, retunrns ID
	int getTriangleIdByIndex(int index);

	//getting triangle by ID
	Triangle* getTriangleById(int id);

	//select triangle and notify, called in ImguiManager during selectable
	void selectTriangle(int index);

	//delete shapes
	//set the selected object to none
	void deleteTrinagleById(int id);
	
	//a parametrized constructor to assign selected type
	Scene(SceneObjectType type, int index);
};
