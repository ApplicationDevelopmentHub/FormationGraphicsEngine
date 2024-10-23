#pragma once
//interface
class Shapes {
public:
	virtual void draw() = 0; //pure virtual function
	virtual ~Shapes() = default; //virtual destructor, compiler generated implementation of destructor
};
