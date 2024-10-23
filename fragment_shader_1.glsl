#version 330 core
in vec4 fragmentColor;  //input from vertex shader
out vec4 color;			//output color
void main(){
	color=fragmentColor;
}