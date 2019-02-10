#version 330 
layout (location = 0) in vec4 vertPos; 
void main(){ 	
	gl_Position = vertPos;
	gl_PointSize = 10; 
}
