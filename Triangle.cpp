#include"Triangle.h"

//start the trinagle ID generation from 1
int Triangle::nextID = 1;

//default triangle constructor
Triangle::Triangle() {
	//assign id
	id = nextID++;

	//define the default vertex values
	float vertices[45] = {
		//vertex 1
		//position
		0.0f,0.0f,0.0f,
		//color
		1.0f,1.0f,1.0f,1.0f,
		//texture coordinates: 0,0
		0.0f,0.0f,
		//normals/: 0,0,1
		0.0f,0.0f,1.0f,
		//tangents: 1,0,0
		1.0f,0.0f,0.0f,

		//vertex 2
		//position
		0.5f,0.0f,0.0f,
		//color
		1.0f,1.0f,1.0f,1.0f,
		//texture coordinates: 0,0
		0.0f,0.0f,
		//normals/: 0,0,1
		0.0f,0.0f,1.0f,
		//tangents: 1,0,0
		1.0f,0.0f,0.0f,

		//vertex 3
		//position
		0.0f,0.5f,0.0f,
		//color
		1.0f,1.0f,1.0f,1.0f,
		//texture coordinates: 0,0
		0.0f,0.0f,
		//normals/: 0,0,1
		0.0f,0.0f,1.0f,
		//tangents: 1,0,0
		1.0f,0.0f,0.0f
	};

	//use the above default vertices data
	for (int i = 0; i < 45; i++) {
		this->vertices[i] = vertices[i];
	}

	std::cout << "Default constructor used for triangle." << endl;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER,VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 45, vertices, GL_DYNAMIC_DRAW);

	//specify the layout of vertex data: for all 5 parameters
	//position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 15 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//color
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 15 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	//texture coordinates
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 15 * sizeof(float), (void*)(7 * sizeof(float)));
	glEnableVertexAttribArray(2);

	//normal
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 15 * sizeof(float), (void*)(9 * sizeof(float)));
	glEnableVertexAttribArray(3);

	//tangent
	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, 15 * sizeof(float), (void*)(12 * sizeof(float)));
	glEnableVertexAttribArray(4);

	//unbind VAO and VBO to prevent any modification
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

//Triangle constructor
Triangle::Triangle(float vertices[45]) {

	//assign id
	id = nextID++;

	//vertex data from parameters
	for (int i = 0; i < 45; i++) {
		this->vertices[i] = vertices[i];
	}

	//create VAO and VBO
	glGenVertexArrays(1,&VAO);
	glGenBuffers(1, &VBO);

	//bind VAO and VBO
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	//fill buffer data
	glBufferData(GL_ARRAY_BUFFER,sizeof(float)*45,vertices,GL_DYNAMIC_DRAW);

	//speccify the layout of vertex data: for all 5 parameters
	//position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//color
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 15 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	//texture coordinates
	glVertexAttribPointer(5, 2, GL_FLOAT, GL_FALSE, 15 * sizeof(float), (void*)(7 * sizeof(float)));
	glEnableVertexAttribArray(2);

	//normal
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 15 * sizeof(float), (void*)(9 * sizeof(float)));
	glEnableVertexAttribArray(3);

	//tangent
	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, 15 * sizeof(float), (void*)(12 * sizeof(float)));
	glEnableVertexAttribArray(4);

	//unbind VAO and VBO to prevent any modification
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

//triangle destructor
Triangle::~Triangle() {
	glDeleteVertexArrays(1,&VAO);
	glDeleteBuffers(1,&VBO);

	std::cout << "Triangle with ID " << id << " is deleted" << endl;
}

//override keyword does not go in cpp, enough in header file
void Triangle::draw(){
	glBindVertexArray(VAO);  //bind VAO
	glDrawArrays(GL_TRIANGLES, 0, 3); //draw triangle
	glBindVertexArray(0); //unbind VAO
}

//function to return triangle ID
int Triangle::getID() const {
	return id;
}

//function to return vertex data of triangle
float Triangle::getVertices(int index) {
	return vertices[index];
}

//function to get the next ID 
//static and const keywords need to be defined only in header files
int Triangle::getNextID(){
	return nextID;
}

//method to update vertices
//We will use imgui for this modification
//updates only floats corresponding to vertices
void Triangle::updateVertices(float updatedVertices[9]) {

	//updating the vertex points
	for (int i = 0; i < 3; i++) {
		this->vertices[i * 15] = updatedVertices[i * 3]; //for the first float of each vertex:x
		this->vertices[i * 15 + 1] = updatedVertices[i * 3 + 1]; //y
		this->vertices[i * 15 + 2] = updatedVertices[i * 3 + 2]; //z
	}

	//bind VAO and VBO again
	//update vertex buffer
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	//update only a part of buffer data- vertex
	glBufferSubData(GL_ARRAY_BUFFER,0,sizeof(float)*45,this->vertices);

	//unbind VAO and VBO
	glBindBuffer(GL_ARRAY_BUFFER,0);
	glBindVertexArray(0);
}

//method to update vertices color
//we will use imgui for this modification
void Triangle::updateColors(float updatedColors[12]) {
	// Update only the vertex colors (4 floats for each vertex starting at index 3)
	for (int i = 0; i < 3; i++) {
		// Vertex 1 color
		this->vertices[i * 15 + 3] = updatedColors[i * 4];      // r
		this->vertices[i * 15 + 4] = updatedColors[i * 4 + 1];  // g
		this->vertices[i * 15 + 5] = updatedColors[i * 4 + 2];  // b
		this->vertices[i * 15 + 6] = updatedColors[i * 4 + 3];  // a
	}

	//bind VAO and VBO to update vertex colors
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	//update the sub buffer data: only a part of it for vertex colors only
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(this->vertices), &this->vertices);

	//unind vao and vbo
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

//method to update a single vertex color
void Triangle::updateSingleVertexColor(float updatedColors[4], int index) {
	// Update only the vertex colors (4 floats for each vertex starting at index 3)
		this->vertices[index * 15 + 3] = updatedColors[0];      // r
		this->vertices[index * 15 + 4] = updatedColors[1];  // g
		this->vertices[index * 15 + 5] = updatedColors[2];  // b
		this->vertices[index * 15 + 6] = updatedColors[3];  // a

	//bind VAO and VBO to update vertex colors
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	//update the sub buffer data: only a part of it for vertex colors only
	//updated all vertex points later, as the modified ones only did not work
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(this->vertices), &this->vertices);

	//unbind vao and vbo
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

//delete instance of a triangle by its id
void Triangle::deleteTriangle(int index) {
	//delete triangle
}


