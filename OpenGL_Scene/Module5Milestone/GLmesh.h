#ifndef GL_MESH_H
#define GL_MESH_H

#include <glad/glad.h>

//Stores the variable data for the mesh
struct GLMesh {
    GLuint vao; //Handle for the vertex array object
    GLuint vbo;
    GLuint vbos[2]; //Handle for the vertex buffer object
    GLuint nIndices;    // Number of indices of the mesh
};

#endif