#include <iostream>
#include <math.h>
// GLEW
#define GLEW_STATIC
#include <GL/glew.h>
// GLFW
#include <GLFW/glfw3.h>
// Shader Class
#include "SHADER.h"

// Function Prototype
void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode);

// Window Dimensions
const GLuint WIDTH = 800, HEIGHT = 600;

int main(){
    // Init GLFW
    glfwInit();
    // Required options for GLFW
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);    // For MAC
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    // GLFW window object
    GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "Learn OpenGL", nullptr, nullptr);
    if (window == nullptr){
        std::cout<< "Failed to create GLFW window" <<std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    // Set the required callback function
    glfwSetKeyCallback(window, key_callback);
    // True so GLEW knows to use a modern approach to retrieving function pointers and extensions
    glewExperimental = GL_TRUE;
    // Initialize GLEW
    if (GLEW_OK != glewInit()){
        std::cout<<"Failed to initialize GLEW"<<std::endl;
        return -1;
    }
    // Define Viewport Dimensions
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);
    
    Shader ourShader("path/to/shaders/default.vs", "path/to/shaders/default.frag");
    
    // Triangle Vertices
    GLfloat vertices[] = {
        // Positions         // Colors
        0.5f, -0.5f, 0.0f,   1.0f, 0.0f, 0.0f,  // Bottom Right
        -0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,  // Bottom Left
        0.0f,  0.5f, 0.0f,   0.0f, 0.0f, 1.0f   // Top
    };
   
    // Vertex Buffer
    GLuint VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
 
    // Bind Vertex Array Object first, then bind and set vertex buffers
    glBindVertexArray(VAO);
    
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    // Color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 *sizeof(GLfloat)));
    glEnableVertexAttribArray(1);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    glBindVertexArray(0);
    
    GLint nrAtrributes;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAtrributes);
    std::cout << "Maximum nr of vertex attrivutes supported: " << nrAtrributes<< std::endl;
    
    // Game Loop
    while(!glfwWindowShouldClose(window)){
        // Check and call events
        glfwPollEvents();
        
        // Rendering commands
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
       
        // Draw triangle
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);
        
        // Swap the bufers
        glfwSwapBuffers(window);
    }
    
    // De-allocate all resources
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    // Terminate GLFW
    glfwTerminate();
    return 0;
}

// Called when a key is pressed
void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode){
    std::cout << key << std::endl;
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS){
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
}
