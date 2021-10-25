#include "shaderClass.h"

/*
* Helper function that will load the file for the vertex and fragment shaders
* and read them in the function to be used as shaders in the scene
*/
std::string get_file_contents(const char* filename) {
	std::ifstream in(filename, std::ios::binary);
	if (in) {
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return(contents);
	}
	throw(errno);
}

/*
* Creates the shaders that will handle the look of the objects in the scene
* The first is the vertex shader that will render the vertices of the object that is passed to it
* The second is the fragment shader that will render the pieces of the object with color
* 
* Parameters are the vertex file and the fragment file 
*/
Shader::Shader(const char* vertexFile, const char* fragmentFile) {
	std::string vertexCode = get_file_contents(vertexFile);
	std::string fragmentCode = get_file_contents(fragmentFile);

	const char* vertexSource = vertexCode.c_str();
	const char* fragmentSource = fragmentCode.c_str();

	// Create a Shader program object.
	ID = glCreateProgram();

	// Create the vertex and fragment shader objects
	GLuint vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);

	// Retrive the shader source
	glShaderSource(vertexShaderId, 1, &vertexSource, NULL);
	glShaderSource(fragmentShaderId, 1, &fragmentSource, NULL);

	// Compile both shaders
	glCompileShader(vertexShaderId);
	glCompileShader(fragmentShaderId);

	// Attached compiled shaders to the shader program
	glAttachShader(ID, vertexShaderId);
	glAttachShader(ID, fragmentShaderId);

	glLinkProgram(ID);
}

/*
* Activates the shader programs with the ID
*/
GLuint Shader::Activate() {
	glUseProgram(ID);
	return ID;
}

/*
* Deletes the shader programs with the ID
*/
void Shader::Delete() {
	glDeleteProgram(ID);
}