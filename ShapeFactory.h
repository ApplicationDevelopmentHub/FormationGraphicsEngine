#pragma once
#include<memory>
#include<stdexcept>
#include"Shapes.h"
#include"PrimitiveShapeTypes.h"
#include"Triangle.h"
#include"Rectangle.h"

using namespace std;

class ShapeFactory {
private:
public:
	//constructor to draw a primitive using the given set of vertices
	static unique_ptr<Shapes> createShape(PrimitiveShapeTypes type, float vertices[45]);

	//using default constructor of each primitive with default vertices set
	static unique_ptr<Shapes> createShape(PrimitiveShapeTypes type);
};
