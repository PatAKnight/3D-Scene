#include <iostream>
#include <cstdlib>          // EXIT_FAILURE
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "stb_image.h" // Image loading Utility functions

//Personal Headers that are used to handle various tasks throughout the project
#include "shaderClass.h"
#include "createPen.h"
#include "createPlane.h"
#include "camera.h"
#include "createClip.h"
#include "createCylinder.h"
#include "createGBA.h"
#include "createButton.h"
#include "createBinder.h"
#include "createRing.h"
#include "lightSource.h"


using namespace std;

//Unnamed namespace
namespace {
    // settings
    const char* const WINDOW_TITLE = "Patrick Knight"; // Macro for window title

    // Variables for window width and height
    const int SCR_WIDTH = 800;
    const int SCR_HEIGHT = 600;

    //Variables that will be used throughout the project
    // Main GLFW window
    GLFWwindow* window = nullptr;

    // Triangle mesh data
    GLMesh planeMesh;
    GLMesh lightMesh;
    GLMesh penMesh, penClip;
    GLMesh gbaMesh, screenMesh, dButtonMesh;
    GLMesh binderMesh, paperMesh, ringMesh;
    GLMesh cylinderMesh;

    //Shader id
    GLuint programID;
    GLuint lightID;

    // Texture id
    GLuint planeTexture;
    GLuint silverTexture, clipTexture;
    GLuint gbaTexture;
    GLuint whitePlastic, blackPlastic;

    // camera
    Camera gCamera(glm::vec3(0.0f, 2.5f, 8.0f)); //Camera's original position
    float gLastX = SCR_WIDTH / 2.0f;
    float gLastY = SCR_HEIGHT / 2.0f;
    bool gFirstMouse = true;

    // timing
    float gDeltaTime = 0.0f; // time between current frame and last frame
    float gLastFrame = 0.0f;

    // Cube and light color
    glm::vec3 gObjectColor(1.f, 0.2f, 1.0f);
    glm::vec3 gLightColor(1.0f, 1.0f, 1.0f);

    // Light position and scale
    glm::vec3 gLightPosition(-2.5f, 1.5f, 4.0f);
    glm::vec3 gLightScale(0.3f);

}

/*
* Helper functions that are used to keep the project cleaner and easier to read
* Initialize sets up and initializes the creation of the window
* Framebuffer handles any screen resize
* Process Input handles input
* Render is used to draw the objects
* Mouse Position checks for the location of the mouse
* Mouse Scroll checks if the scroll wheel is used
* Mouse Button checks if a mouse button is used
*/
bool initialize(int, char* [], GLFWwindow** window);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
void render(Shader shaderProgram, Shader lightShader, Pen pen, Plane plane, Clip clip, Cylinder cylinder, GBA gba, Plane screen, Button dButton, Binder binder, Binder paper, Ring ring, Light light);
void UMousePositionCallback(GLFWwindow* window, double xpos, double ypos);
void UMouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset);
bool UCreateTexture(const char* filename, GLuint& textureId);
void UDestroyTexture(GLuint textureId);

//Main function that will run the program
int main(int argc, char* argv[])
{
    //Call to the initialize function
    if (!initialize(argc, argv, &window))
        return EXIT_FAILURE;

    //Create the Mesh
    Pen pen(penMesh);
    Plane plane(planeMesh);
    Clip clip(penClip);
    Light light(lightMesh);
    Cylinder cylinder(cylinderMesh);
    GBA gba(gbaMesh);
    Plane screen(screenMesh);
    Button dButton(dButtonMesh);
    Binder binder(binderMesh);
    Binder paper(paperMesh);
    Ring ring(ringMesh);

    //Create the Shader program
    Shader shaderProgram("default.vert", "default.frag");
    Shader lightShader("light.vert", "light.frag");

    //Load the texture (relative to the project's directory
    const char* texFilename = "silver.jpg";
    if (!UCreateTexture(texFilename, silverTexture)) {
        cout << "Failed to load texture" << texFilename << endl;
        return EXIT_FAILURE;
    }

    const char* texFilename2 = "rubber.jpg";
    if (!UCreateTexture(texFilename2, clipTexture)) {
        cout << "Failed to load texture" << texFilename2 << endl;
        return EXIT_FAILURE;
    }

    const char* texFilename3 = "floral.jpg";
    if (!UCreateTexture(texFilename3, planeTexture)) {
        cout << "Failed to load texture" << texFilename3 << endl;
        return EXIT_FAILURE;
    }

    const char* texFilename4 = "whitePlastic.jpg";
    if (!UCreateTexture(texFilename4, whitePlastic)) {
        cout << "Failed to load texture" << texFilename4 << endl;
        return EXIT_FAILURE;
    }

    const char* texFilename5 = "bluePlastic.jpg";
    if (!UCreateTexture(texFilename5, gbaTexture)) {
        cout << "Failed to load texture" << texFilename5 << endl;
        return EXIT_FAILURE;
    }

    const char* texFilename6 = "blackPlastic.jpg";
    if (!UCreateTexture(texFilename6, blackPlastic)) {
        cout << "Failed to load texture" << texFilename6 << endl;
        return EXIT_FAILURE;
    }
    //Tell OpenGL for each sampler to which texture unit it belongs to
    glUseProgram(programID);

    //Set the texture to texture unit 0
    glUniform1i(glGetUniformLocation(programID, "uTexture"), 0);

    //Sets the background color to black
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    // render loop
    // Renders the image so long as the window is open
    while (!glfwWindowShouldClose(window))
    {
        //Get the current frame by finding the current time
        float currentFrame = glfwGetTime();
        gDeltaTime = currentFrame - gLastFrame;
        gLastFrame = currentFrame;

        // Call to the input processor function
        processInput(window);

        // render
        render(shaderProgram, lightShader, pen, plane, clip, cylinder, gba, screen, dButton, binder, paper, ring, light);

        // glfw: Poll IO events (keys pressed/released, mouse moved etc.)
        glfwPollEvents();
    }

    //Release mesh data
    pen.destroyMesh(penMesh);
    plane.destroyMesh(planeMesh);
    clip.destroyMesh(penClip);
    light.destroyMesh(lightMesh);
    cylinder.destroyMesh(cylinderMesh);
    gba.destroyMesh(gbaMesh);
    screen.destroyMesh(screenMesh);
    dButton.destroyMesh(dButtonMesh);
    binder.destroyMesh(binderMesh);
    binder.destroyMesh(paperMesh);
    ring.destroyMesh(ringMesh);

    //Release Texture
    UDestroyTexture(silverTexture);
    UDestroyTexture(clipTexture);
    UDestroyTexture(planeTexture);
    UDestroyTexture(whitePlastic);
    UDestroyTexture(gbaTexture);
    UDestroyTexture(blackPlastic);

    //Release shader program
    shaderProgram.Delete();
    lightShader.Delete();

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // Ends the window 
    glfwTerminate();
    return 0;
}

/*
* Initiliazes GFLW, GLAD and creates the window
*
* Takes the current GLFW window as a parameter
*/
bool initialize(int argc, char* argv[], GLFWwindow** window) {
    // glfw: initialize and configure
    // This is where the GLFW window is initialized
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    /*
    * glfw window creation
    * This is where the GLFW window is created
    * Has error checking built in
    * Needs the Width and Height of the Screen and the title of the Screen
    */
    * window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, WINDOW_TITLE, NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent(*window);
    glfwSetFramebufferSizeCallback(*window, framebuffer_size_callback); //Handles the resizing of the window

    //Calls to find the location of the mouse and the buttons that are pressed
    glfwSetCursorPosCallback(*window, UMousePositionCallback);
    glfwSetScrollCallback(*window, UMouseScrollCallback);

    // glad: load all OpenGL function pointers
    // Initialize GLAD
    // XX Ensure that the glad.c file is added to the project
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return false;
    }

}

/*
* Function that will flip images 
* Images are loading with different X and Y coordinate locations compared to OpenGL
*/
void flipImageVertically(unsigned char* image, int width, int height, int channels)
{
    for (int j = 0; j < height / 2; ++j)
    {
        int index1 = j * width * channels;
        int index2 = (height - 1 - j) * width * channels;

        for (int i = width * channels; i > 0; --i)
        {
            unsigned char tmp = image[index1];
            image[index1] = image[index2];
            image[index2] = tmp;
            ++index1;
            ++index2;
        }
    }
}

/*
* Function that handles the resizing of the window whether by the OS or the user
*
* Takes the current GLFW window as a parameter
* Takes the resized width and heigth as parameters
*/
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    // This is where the image is displayed when rendered
    glViewport(0, 0, width, height);
}

/*
* Function that processes the input from the user
* This function checks if the escape key is press and if so closes the window
* Checks if the WASDQE buttons are pressed
* W - Forward, A - Left, S - Backward, D - Right, Q - Up, E - Down
*
* Takes the current GLFW window as a parameter
*/
void processInput(GLFWwindow* window)
{
    static const float cameraSpeed = 2.5f;

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        gCamera.ProcessKeyboard(FORWARD, gDeltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        gCamera.ProcessKeyboard(BACKWARD, gDeltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        gCamera.ProcessKeyboard(LEFT, gDeltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        gCamera.ProcessKeyboard(RIGHT, gDeltaTime);
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
        gCamera.ProcessKeyboard(UP, gDeltaTime);
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
        gCamera.ProcessKeyboard(DOWN, gDeltaTime);
    if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
        gCamera.processPerspective(PERSPECTIVE);
    if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS)
        gCamera.processPerspective(ORTHO);
}

/*
* Function that handles rendering the frame
* Sets the background, creates the shader programs, activates the VBOs,
* Draws the triangles, deactivates the VAO, and Swaps the buffers
* 
* Takes the parameters of the different shapes that will be drawn on the screen
*/
void render(Shader shaderProgram, Shader lightShader, Pen pen, Plane plane, Clip clip, Cylinder cylinder, GBA gba, Plane screen, Button dButton, Binder binder, Binder paper, Ring ring, Light light) {
    //Enable z-depth
    glEnable(GL_DEPTH_TEST);

    // Clear the background and z buffer
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Set the shader to be used
    programID = shaderProgram.Activate();

    // Retrieves and passes transform matrices to the Shader program
    GLint modelLoc = glGetUniformLocation(programID, "model");
    GLint viewLoc = glGetUniformLocation(programID, "view");
    GLint projLoc = glGetUniformLocation(programID, "projection");

    // camera view transformation
    glm::mat4 view = gCamera.GetViewMatrix();

    // Creates a perspective projection (field of view, aspect ratio, near plane, and far plane are the four parameters)
    glm::mat4 projection = gCamera.getPerspective();

    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

    //Draw the Plane
    {
        //Calls the transformation function that will scale, rotate, and transform the object in the scene
        plane.transformation(modelLoc, glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 0.0f, 1.0f), 0.0f);

        //Sets the shader Information in the plane class.
        //This handles coloring the object with the object's color and the light sources, currently set up for two light sources.
        plane.setShaderInfo(programID, gObjectColor, gLightColor, gLightPosition);

        // Activate the VBOs contained within the mesh's VAO
        glBindVertexArray(planeMesh.vao);

        //Bind texture on corresponding texture units
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, planeTexture);

        //Draw Plane
        glDrawArrays(GL_TRIANGLES, 0, planeMesh.nIndices);

        // Deactivate the Vertex Array Object
        glBindVertexArray(0);
    }

    //Draw the Pen
    {
        pen.transformation(modelLoc);

        pen.setShaderInfo(programID, gObjectColor, gLightColor, gLightPosition);

        glBindVertexArray(penMesh.vao);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, silverTexture);

        glDrawArrays(GL_TRIANGLES, 0, penMesh.nIndices);

        glBindVertexArray(0);
    }

    //Draw the Pen Clip on the Pen
    {
        clip.transformation(modelLoc);

        clip.setShaderInfo(programID, gObjectColor, gLightColor, gLightPosition);

        glBindVertexArray(penClip.vao);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, clipTexture);

        glDrawArrays(GL_TRIANGLES, 0, penClip.nIndices);

        glBindVertexArray(0);
    }

    //Draw the Cup
    {
        cylinder.transformation(modelLoc, glm::vec3(0.45f, 0.8f, 0.45f), glm::vec3(3.8f, 0.0f, -3.15f), 0.0f);

        cylinder.setShaderInfo(programID, gObjectColor, gLightColor, gLightPosition);

        glBindVertexArray(cylinderMesh.vao);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, whitePlastic);

        glDrawArrays(GL_TRIANGLES, 0, cylinderMesh.nIndices);

        glBindVertexArray(0);
    }

    //Draw the GameBoy
    {
        gba.transformation(modelLoc);

        gba.setShaderInfo(programID, gObjectColor, gLightColor, gLightPosition);

        glBindVertexArray(gbaMesh.vao);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, gbaTexture);

        glDrawArrays(GL_TRIANGLES, 0, gbaMesh.nIndices);

        glBindVertexArray(0);
    }

    //Draw the Screen on the GameBoy
    {
        screen.transformation(modelLoc, glm::vec3(0.04f, -2.225f, 0.04f), glm::vec3(-1.5f, 0.31f, 1.5f), 200.0f);

        screen.setShaderInfo(programID, gObjectColor, gLightColor, gLightPosition);

        glBindVertexArray(screenMesh.vao);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, blackPlastic);

        glDrawArrays(GL_TRIANGLES, 0, screenMesh.nIndices);

        glBindVertexArray(0);
    }

    //Draw the Directional Pad on the GameBoy
    {
        dButton.transformation(modelLoc);

        dButton.setShaderInfo(programID, gObjectColor, gLightColor, gLightPosition);

        glBindVertexArray(dButtonMesh.vao);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, blackPlastic);

        glDrawArrays(GL_TRIANGLES, 0, dButtonMesh.nIndices);

        glBindVertexArray(0);
    }

    //Draw the A button
    {
        cylinder.transformation(modelLoc, glm::vec3(0.05f, 0.05f, 0.05f), glm::vec3(-1.25f, 0.31f, 1.45f), 180.0f);

        cylinder.setShaderInfo(programID, gObjectColor, gLightColor, gLightPosition);

        glBindVertexArray(cylinderMesh.vao);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, blackPlastic);

        glDrawArrays(GL_TRIANGLES, 0, cylinderMesh.nIndices);

        glBindVertexArray(0);
    }

    //Draw the B button
    {
        cylinder.transformation(modelLoc, glm::vec3(0.05f, 0.05f, 0.05f), glm::vec3(-1.23f, 0.31f, 1.3f), 180.0f);

        cylinder.setShaderInfo(programID, gObjectColor, gLightColor, gLightPosition);

        glBindVertexArray(cylinderMesh.vao);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, blackPlastic);

        glDrawArrays(GL_TRIANGLES, 0, cylinderMesh.nIndices);

        glBindVertexArray(0);
    }

    //Draw the Binder
    {
        binder.transformation(modelLoc, glm::vec3(6.0f, 1.0f, 6.0f), glm::vec3(1.0f, 0.0f, 1.0f));

        binder.setShaderInfo(programID, gObjectColor, gLightColor, gLightPosition);

        glBindVertexArray(binderMesh.vao);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, blackPlastic);

        glDrawArrays(GL_TRIANGLES, 0, binderMesh.nIndices);

        glBindVertexArray(0);
    }

    //Draw the right hand stack of Paper
    {
        paper.transformation(modelLoc, glm::vec3(2.5f, 2.0f, 4.0f), glm::vec3(2.55f, 0.0f, 1.0f));

        paper.setShaderInfo(programID, gObjectColor, gLightColor, gLightPosition);

        glBindVertexArray(paperMesh.vao);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, whitePlastic);

        glDrawArrays(GL_TRIANGLES, 0, paperMesh.nIndices);

        glBindVertexArray(0);
    }

    //Draw the left hand stack of Paper
    {
        paper.transformation(modelLoc, glm::vec3(2.5f, 2.0f, 4.0f), glm::vec3(-0.55f, 0.0f, 1.0f));

        paper.setShaderInfo(programID, gObjectColor, gLightColor, gLightPosition);

        glBindVertexArray(paperMesh.vao);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, whitePlastic);

        glDrawArrays(GL_TRIANGLES, 0, paperMesh.nIndices);

        glBindVertexArray(0);
    }

    //Draw the Top ring on the Binder
    {
        ring.transformation(modelLoc, glm::vec3(0.4f, 0.4f, 0.4f), glm::vec3(1.0f, 0.25f, -0.6f));

        ring.setShaderInfo(programID, gObjectColor, gLightColor, gLightPosition);

        glBindVertexArray(ringMesh.vao);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, silverTexture);

        glDrawArrays(GL_TRIANGLES, 0, ringMesh.nIndices);

        glBindVertexArray(0);
    }

    //Draw the Middle ring on the Binder
    {
        ring.transformation(modelLoc, glm::vec3(0.4f, 0.4f, 0.4f), glm::vec3(1.0f, 0.25f, 1.0f));

        ring.setShaderInfo(programID, gObjectColor, gLightColor, gLightPosition);

        glBindVertexArray(ringMesh.vao);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, silverTexture);

        glDrawArrays(GL_TRIANGLES, 0, ringMesh.nIndices);

        glBindVertexArray(0);
    }

    //Draw the Bottom ring on the Binder
    {
        ring.transformation(modelLoc, glm::vec3(0.4f, 0.4f, 0.4f), glm::vec3(1.0f, 0.25f, 2.6f));

        ring.setShaderInfo(programID, gObjectColor, gLightColor, gLightPosition);

        glBindVertexArray(ringMesh.vao);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, silverTexture);

        glDrawArrays(GL_TRIANGLES, 0, ringMesh.nIndices);

        glBindVertexArray(0);
    }

    {
        // LAMP: draw lamp
        //----------------
        lightID = lightShader.Activate();

        // Reference matrix uniforms from the Lamp Shader program
        modelLoc = glGetUniformLocation(lightID, "model");
        viewLoc = glGetUniformLocation(lightID, "view");
        projLoc = glGetUniformLocation(lightID, "projection");

        light.transformation(modelLoc, gLightPosition, gLightScale);
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

        // Activate the VBOs contained within the mesh's VAO
        glBindVertexArray(lightMesh.vao);

        glDrawArrays(GL_TRIANGLES, 0, lightMesh.nIndices);

        // Deactivate the Vertex Array Object
        glBindVertexArray(0);
    }

    // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
    glfwSwapBuffers(window);    // Flips the the back buffer with the front buffer every frame.
}

/*
* This function handles the callback for the location of the mouse
* Whenever the mouse moves within the scene this function will update a location variable for the mouse
* location will then be passed to the camera object
* 
* Parameters are the window of the scene and the mouse's current location before movement
*/
// glfw: whenever the mouse moves, this callback is called
// Checks the location of the mouse on the screen and passes the information to the Camera object
void UMousePositionCallback(GLFWwindow* window, double xpos, double ypos)
{
    if (gFirstMouse)
    {
        gLastX = xpos;
        gLastY = ypos;
        gFirstMouse = false;
    }

    float xoffset = xpos - gLastX;
    float yoffset = gLastY - ypos; // reversed since y-coordinates go from bottom to top

    gLastX = xpos;
    gLastY = ypos;

    //Call to the camera object that will update the mouse movement
    gCamera.ProcessMouseMovement(xoffset, yoffset);
}


/*
* Function that handles the scroll wheels movement on a mouse
* If the scroll wheel is used the speed of the camera will be adjusted
* passes the new speed to the camera object
* 
* Paremeters are the window of the scene and the mouse's current location
*/
// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// Passes the information to the Camera object
void UMouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
    gCamera.ProcessMouseScroll(yoffset);
}

/*
* Function that handles the creation of the texture object. 
* The object is retrieved from the resource files and loaded into OpenGL
*/
bool UCreateTexture(const char* filename, GLuint& textureId) {
    int width, height, channels;
    unsigned char* image = stbi_load(filename, &width, &height, &channels, 0);
    if (image) {
        flipImageVertically(image, width, height, channels);

        glGenTextures(1, &textureId);
        glBindTexture(GL_TEXTURE_2D, textureId);

        //Set the textuer wrapping parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        //set texture filtering parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        if (channels == 3)
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
        else if (channels == 4)
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
        else {
            cout << "Not implemented to handle image with " << channels << " channels" << endl;
            return false;
        }

        glGenerateMipmap(GL_TEXTURE_2D);

        stbi_image_free(image);
        glBindTexture(GL_TEXTURE_2D, 0); //Unbind the texture

        return true;
    }

    //Error loading the image
    return false;
}

void UDestroyTexture(GLuint textureId) {
    glGenTextures(1, &textureId);
}