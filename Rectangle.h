#pragma once
#include"Shapes.h"
#include<iostream>
#include<GL/glew.h>
#include<GLFW/glfw3.h>
using namespace std;
class Rectangle :public Shapes {
private:
public:
	GLuint VAO, VBO;
	static int nextID;
	int id;

	//default constructor
	Rectangle();

	//constructor
	Rectangle(float vertices[12]);

	//destructor
	~Rectangle();

	//override draw function of shapes
	void draw() override;

	int getID() const;

	float getVertices(int index);

	static int getNextID;

	void updateVertices(float updateVertieces[12]);

	void updateColors(float updatedColors[16]);

	void updateSingleVertexColor(float updatedVertex[4], int index);

	void deleteRectangle();
};
