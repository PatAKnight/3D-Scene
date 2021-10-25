#include "lightSource.h"

/*
* Constructor that takes in the GLMesh struct as a parameters
* The constructor also handles the creation of the object to be drawn
* Sets the matrices for the vertices and indices that hold locations of the shape
*/
Light::Light(GLMesh& mesh) {
    GLfloat verts[] =
    {
        //Back Face          //Negative Z Normals
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 0.0f,  0.0f,
        0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 0.0f,  0.0f,
        0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 0.0f,  0.0f,
        0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 0.0f,  0.0f,

        //Front Face         //Positive Z Normals
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f, 0.0f,  0.0f,
        0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f, 0.0f,  0.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f, 0.0f,  0.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f, 0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f, 0.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f, 0.0f,  0.0f,

        //Left Face          //Negative X Normals
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f, 0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f, 0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f, 0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f, 0.0f,  0.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f, 0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f, 0.0f,  0.0f,

        //Right Face         //Positive X Normals
        0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f, 0.0f,  0.0f,
        0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f, 0.0f,  0.0f,
        0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f, 0.0f,  0.0f,
        0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f, 0.0f,  0.0f,
        0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f, 0.0f,  0.0f,
        0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f, 0.0f,  0.0f,

        //Bottom Face        //Negative Y Normals
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f, 0.0f,  0.0f,
        0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f, 0.0f,  0.0f,
        0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f, 0.0f,  0.0f,
        0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f, 0.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f, 0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f, 0.0f,  0.0f,

        //Top Face           //Positive Y Normals
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f, 0.0f,  0.0f,
        0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f, 0.0f,  0.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f, 0.0f,  0.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f, 0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f, 0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f, 0.0f,  0.0f,

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
void Light::transformation(GLint modelLoc, glm::vec3 gLightPosition, glm::vec3 gLightScale) {
    // 1. Scales the object's x and y down and stretches the object on the z axis
    glm::mat4 scale = glm::scale(gLightScale);
    // 2. Rotates shape by 90 degrees in the x axis
    glm::mat4 rotation = glm::rotate(0.0f, glm::vec3(0.0, 1.0f, 0.0f));
    // 3. Place object at the origin
    glm::mat4 translation = glm::translate(gLightPosition);
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
void Light::destroyMesh(GLMesh& mesh)
{
    glDeleteVertexArrays(1, &mesh.vao);
    glDeleteBuffers(2, mesh.vbos);
}