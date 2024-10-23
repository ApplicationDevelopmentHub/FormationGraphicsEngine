#include"Rectangle.h"

//default rectangle constructor
Rectangle::Rectangle() {

}

//Rectangle constructor
Rectangle::Rectangle(float vertices[12]) {
	//create VAO and VBO
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	//bind VAO and VBO
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	//fill buffer data
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 9, vertices, GL_DYNAMIC_DRAW);

	//speccify the layout of vertex data
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//unbind VAO and VBO to prevent any modification
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

//triangle destructor
Rectangle::~Rectangle() {
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
}

//override keyword does not go in cpp, enough in header file
void Rectangle::draw() {
	cout << "Drawing a new OpenGL triangle" << endl;
	glBindVertexArray(VAO);  //bind VAO
	glDrawArrays(GL_TRIANGLES, 0, 3); //draw triangle
	glBindVertexArray(0); //unbind VAO
}
