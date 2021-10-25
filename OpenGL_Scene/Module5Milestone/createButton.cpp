#include "createButton.h"

/*
* Constructor that takes in the GLMesh struct as a parameters
* The constructor also handles the creation of the object to be drawn
* Sets the matrices for the vertices and indices that hold locations of the shape
*/
Button::Button(GLMesh& mesh) {
    meshPosition = glm::vec3(-1.85f, 0.29f, 1.65f);
    meshScale = glm::vec3(0.25f, 0.25f, 0.25f);
    meshRotation = glm::vec3(0.0, 1.0f, 0.0f);
    degree = 200.0f;
    angle = (degree * (3.1415926f / 180.0f));

    GLfloat verts[] =
    {
        //Button top
        0.1f,  0.1f,  0.3f,  0.0f,  1.0f,  0.0f,  1.0f,  0.67f,
        0.1f,  0.1f, -0.3f,  0.0f,  1.0f,  0.0f,  0.0f,  0.67f,
        -0.1f,  0.1f, -0.3f,  0.0f,  1.0f,  0.0f,  0.0f,  0.33f,
        -0.1f,  0.1f, -0.3f,  0.0f,  1.0f,  0.0f,  0.0f,  0.33f,
        -0.1f,  0.1f,  0.3f,  0.0f,  1.0f,  0.0f,  1.0f,  0.33f,
        0.1f,  0.1f,  0.3f,  0.0f,  1.0f,  0.0f,  1.0f,  0.67f,

        0.3f,  0.1f,  0.1f,  0.0f,  1.0f,  0.0f,  0.67f,  1.0f,
        0.3f,  0.1f, -0.1f,  0.0f,  1.0f,  0.0f,  0.33f,  1.0f,
        -0.3f,  0.1f, -0.1f,  0.0f,  1.0f,  0.0f,  0.33f,  0.0f,
        -0.3f,  0.1f, -0.1f,  0.0f,  1.0f,  0.0f,  0.33f,  0.0f,
        -0.3f,  0.1f,  0.1f,  0.0f,  1.0f,  0.0f,  0.67f,  0.0f,
        0.3f,  0.1f,  0.1f,  0.0f,  1.0f,  0.0f,  0.67f,  1.0f,

        //Sides
        0.1f,  0.1f,  0.3f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
        0.1f,  0.1f,  0.1f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
        0.1f,  0.0f,  0.1f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
        0.1f,  0.0f,  0.1f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
        0.1f,  0.0f,  0.3f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
        0.1f,  0.1f,  0.3f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,

        0.3f,  0.1f,  0.1f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
        0.1f,  0.1f,  0.1f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
        0.1f,  0.0f,  0.1f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
        0.1f,  0.0f,  0.1f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
        0.3f,  0.0f,  0.1f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
        0.3f,  0.1f,  0.1f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,

        0.3f,  0.1f,  0.1f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
        0.3f,  0.1f, -0.1f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
        0.3f,  0.0f, -0.1f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
        0.3f,  0.0f, -0.1f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
        0.3f,  0.0f,  0.1f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
        0.3f,  0.1f,  0.1f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,

        0.1f,  0.1f, -0.1f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
        0.3f,  0.1f, -0.1f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
        0.3f,  0.0f, -0.1f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
        0.3f,  0.0f, -0.1f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
        0.1f,  0.0f, -0.1f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
        0.1f,  0.1f, -0.1f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,

        0.1f,  0.1f, -0.1f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
        0.1f,  0.1f, -0.3f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
        0.1f,  0.0f, -0.3f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
        0.1f,  0.0f, -0.3f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
        0.1f,  0.0f, -0.1f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
        0.1f,  0.1f, -0.1f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,

        -0.1f,  0.1f, -0.3f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
        0.1f,  0.1f, -0.3f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
        0.1f,  0.0f, -0.3f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
        0.1f,  0.0f, -0.3f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
        -0.1f,  0.0f, -0.3f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
        -0.1f,  0.1f, -0.3f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,

        -0.1f,  0.1f, -0.3f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
        -0.1f,  0.1f, -0.1f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
        -0.1f,  0.0f, -0.1f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
        -0.1f,  0.0f, -0.1f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
        -0.1f,  0.0f, -0.3f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
        -0.1f,  0.1f, -0.3f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,

        -0.3f,  0.1f, -0.1f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
        -0.1f,  0.1f, -0.1f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
        -0.1f,  0.0f, -0.1f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
        -0.1f,  0.0f, -0.1f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
        -0.3f,  0.0f, -0.1f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
        -0.3f,  0.1f, -0.1f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,

        -0.3f,  0.1f, -0.1f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
        -0.3f,  0.1f,  0.1f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
        -0.3f,  0.0f,  0.1f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
        -0.3f,  0.0f,  0.1f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
        -0.3f,  0.0f, -0.1f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
        -0.3f,  0.1f, -0.1f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,

        -0.1f,  0.1f,  0.1f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
        -0.3f,  0.1f,  0.1f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
        -0.3f,  0.0f,  0.1f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
        -0.3f,  0.0f,  0.1f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
        -0.1f,  0.0f,  0.1f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
        -0.1f,  0.1f,  0.1f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,

        -0.1f,  0.1f, -0.1f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
        -0.1f,  0.1f,  0.3f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
        -0.1f,  0.0f,  0.3f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
        -0.1f,  0.0f,  0.3f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
        -0.1f,  0.0f, -0.1f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
        -0.1f,  0.1f, -0.1f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,

        0.1f,  0.1f,  0.3f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
        -0.1f,  0.1f,  0.3f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
        -0.1f,  0.0f,  0.3f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
        -0.1f,  0.0f,  0.3f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
        0.1f,  0.0f,  0.3f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
        0.1f,  0.1f,  0.3f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,

    };
    glGenVertexArrays(1, &mesh.vao); // we can also generate multiple VAOs or buffers at the same time
    glBindVertexArray(mesh.vao);

    //Create the buffer that will contain the vertex data of the object
    glGenBuffers(1, &mesh.vbo);
    glBindBuffer(GL_ARRAY_BUFFER, mesh.vbo); // Activates the buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW); // Sends vertex or coordinate data to the GPU

    // Creates the Vertex Attribute Pointer for the creen coordinates
    const GLuint floatsPerVertex = 3; // Number of coordinates per vertex
    const GLuint floatsPerColor = 3; // Number of coordinates per color
    const GLuint floatsPerUV = 2; //Texture Coordinates

    mesh.nIndices = sizeof(verts) / (sizeof(verts[0]) * (floatsPerVertex + floatsPerColor + floatsPerUV));

    //Strides between vertex coordinates is 9 Coordinates, Colors (RGB), Texture Coordinates (x, y, z, r, g, b, xt, yt)
    GLint stride = sizeof(float) * (floatsPerVertex + floatsPerColor + floatsPerUV); //The number of floats before each

    //Instructs the GPU on how to handle the vertex buffer object data
    // Passing the vertex floats from the array
    glVertexAttribPointer(0, floatsPerVertex, GL_FLOAT, GL_FALSE, stride, 0);
    glEnableVertexAttribArray(0);

    //Passing the color floats from the array with the offest information
    glVertexAttribPointer(1, floatsPerColor, GL_FLOAT, GL_FALSE, stride, (void*)(sizeof(float) * floatsPerVertex));
    glEnableVertexAttribArray(1);

    //Passing the texture floats from the array with the offest information
    glVertexAttribPointer(2, floatsPerUV, GL_FLOAT, GL_FALSE, stride, (void*)(sizeof(float) * (floatsPerVertex + floatsPerColor)));
    glEnableVertexAttribArray(2);
}

/*
* Handles the transformation of the shape when rendered
* The original locations of the vertices and indices are manipulated to be placed in a different orientation
* Controls the scale, rotation, and transformation of the object in the scene
* GLint model location is passed as a parameter
*/
void Button::transformation(GLint modelLoc) {
    // 1. Scales the object's x and y down and stretches the object on the z axis
    glm::mat4 scale = glm::scale(meshScale);
    // 2. Rotates shape by 90 degrees in the x axis
    glm::mat4 rotation = glm::rotate(angle, meshRotation);
    // 3. Place object at the origin
    glm::mat4 translation = glm::translate(meshPosition);
    // Model matrix: transformations are applied right-to-left order
    glm::mat4 model = translation * rotation * scale;

    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
}

/*
* Function that handles the deletion of the mesh
* Deletes the vertex arrays and the buffers
*
* Takes the mesh as a parameter
*/
void Button::destroyMesh(GLMesh& mesh)
{
    glDeleteVertexArrays(1, &mesh.vao);
    glDeleteBuffers(2, mesh.vbos);
}

/*
* Function that handles coloring, shading, and displaying the light on the object
* Sets the color and displays the correcting lighting based on the light color being shown of the object
*
* Parameters: program: the shader ID, objectColor: the color of the object as a vector, lightColor: color of the light source as a vector, lightPosition: the location of the object as a vector,
* fillColor: color of another light source as a vector, fillPosition: location of the second light source.
*/
void Button::setShaderInfo(GLuint program, glm::vec3 objectColor, glm::vec3 lightColor, glm::vec3 lightPosition) {
    // Reference matrix uniforms from the Cube Shader program for the cub color, light color, light position, and camera position
    GLint objectColorLoc = glGetUniformLocation(program, "objectColor");
    GLint lightColorLoc = glGetUniformLocation(program, "lightColor");
    GLint lightPositionLoc = glGetUniformLocation(program, "lightPos");

    // Pass color, light, and camera data to the Cube Shader program's corresponding uniforms
    glUniform3f(objectColorLoc, objectColor.r, objectColor.g, objectColor.b);
    glUniform3f(lightColorLoc, lightColor.r, lightColor.g, lightColor.b);
    glUniform3f(lightPositionLoc, lightPosition.x, lightPosition.y, lightPosition.z);
}