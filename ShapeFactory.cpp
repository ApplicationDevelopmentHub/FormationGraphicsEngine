#include"ShapeFactory.h"

//defined as static in header file
//not necessary to define static here
//can provide vertices or not here, if not default constructor will be called.
unique_ptr<Shapes> ShapeFactory::createShape(PrimitiveShapeTypes type, float vertices[45]) {
	switch (type) {
		//more primitive shapes to define
		case PrimitiveShapeTypes::TRIANGLE:
			return make_unique<Triangle>(vertices);
		case PrimitiveShapeTypes::RECTANGLE:
			return std::make_unique<Rectangle>();
		default: throw std::invalid_argument("Invalid shape type");
	}
}

//without vertex data, always default constructor
unique_ptr<Shapes> ShapeFactory::createShape(PrimitiveShapeTypes type) {
	switch (type) {
		//more primitive shapes to define
	case PrimitiveShapeTypes::TRIANGLE:
		return std::make_unique<Triangle>();
	case PrimitiveShapeTypes::RECTANGLE:
		return std::make_unique<Rectangle>();
	default: throw std::invalid_argument("Invalid shape type");
	}
}