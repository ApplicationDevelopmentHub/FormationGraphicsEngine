#pragma once
#include"Shapes.h"
#include<iostream>
#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include<vector>
#include<unordered_map>
using namespace std;
class Triangle :public Shapes {
private:
	unsigned int VAO, VBO;
	static int nextID; //generates unique IDs
	int id; //id of current triangle

	//3 pos, 4 color, 2 texture coordinates, 3 normal, 3 tangent
	float vertices[45]; //5 vertex layout data
public:
	//default constructor
	Triangle();

	//constructor
	//this will not be used for basic instantiation
	Triangle(float vertices[45]);

	//destructor
	~Triangle();

	//override draw function of shapes
	void draw() override;

	//function to get triangle ID
	int getID() const;

	//function to get vertices of triangle
	float getVertices(int index);

	//function to generate next trinagle ID
	static int getNextID();

	//method to modify vertices
	void updateVertices(float updatedVertices[9]);

	//method to update vertex colors: all vertex at once
	void updateColors(float updateColors[12]);

	//method to update one vertex color at once
	void updateSingleVertexColor(float updatedColors[4], int index);

	//delete instance of a triangle by its id
	void deleteTriangle(int index);
};
