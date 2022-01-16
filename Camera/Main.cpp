// Camera.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Shader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Camera.h"

void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
void MouseCallback(GLFWwindow* window, double xpos, double ypos);

static const GLfloat g_vertex_buffer_data[] = {
    -1.0f,-1.0f,-1.0f, // triangle 1 : begin
    -1.0f,-1.0f, 1.0f,
    -1.0f, 1.0f, 1.0f, // triangle 1 : end
    1.0f, 1.0f,-1.0f, // triangle 2 : begin
    -1.0f,-1.0f,-1.0f,
    -1.0f, 1.0f,-1.0f, // triangle 2 : end
    1.0f,-1.0f, 1.0f,
    -1.0f,-1.0f,-1.0f,
    1.0f,-1.0f,-1.0f,
    1.0f, 1.0f,-1.0f,
    1.0f,-1.0f,-1.0f,
    -1.0f,-1.0f,-1.0f,
    -1.0f,-1.0f,-1.0f,
    -1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f,-1.0f,
    1.0f,-1.0f, 1.0f,
    -1.0f,-1.0f, 1.0f,
    -1.0f,-1.0f,-1.0f,
    -1.0f, 1.0f, 1.0f,
    -1.0f,-1.0f, 1.0f,
    1.0f,-1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f,-1.0f,-1.0f,
    1.0f, 1.0f,-1.0f,
    1.0f,-1.0f,-1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f,-1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f,-1.0f,
    -1.0f, 1.0f,-1.0f,
    1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f,-1.0f,
    -1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f, 1.0f,
    1.0f,-1.0f, 1.0f
};

static const GLfloat g_triangle_vertex_buffer[] = {
    -1.0f, -1.0f, 0.0f,
    1.0f, -1.0f, 0.0f,
    0.0f, 1.0f, 0.0f
};

Camera camera(45.0f, 800.0f, 400.0f);
bool cameraUsed = false;
float lastXPos, lastYPos = 0;

int main()
{
    GLFWwindow* window;

    if (!glfwInit()) {
        std::cerr << "Error initializing GLFW\n";
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    window = glfwCreateWindow(800, 400, "Hello World", NULL, NULL);
    if (!window) {
        glfwTerminate();
        std::cerr << "Error creating GLFW window.\n";
        return -1;
    }

    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to GLADload\n";
        return -1;
    }
    // configure OpenGL settings
    glEnable(GL_DEPTH_TEST);
    // configure GLFW settings
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window, MouseCallback);
    glfwSetKeyCallback(window, KeyCallback);
    
    
    

    unsigned int VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
    //glBufferData(GL_ARRAY_BUFFER, sizeof(g_triangle_vertex_buffer), g_triangle_vertex_buffer, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(0);
    auto err = glGetError();

    Shader shader;
    shader.AddShader("vertex.glsl", GL_VERTEX_SHADER);
    shader.AddShader("fragment.glsl", GL_FRAGMENT_SHADER);
    shader.BuildProgram("shader");
    shader.UseProgram("shader");
    err = glGetError();

    camera.NewDirection(0.0, 0.0, -1.0);
    camera.NewPos(0.0, 0.0, 5.0);
    camera.NewUp(0.0, 1.0, 0.0);

    while (!glfwWindowShouldClose(window)) {
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::rotate(model, glm::radians(5 * (float)glfwGetTime()), glm::vec3(1.0f, 1.0f, 0.0f));
        glm::mat4 view = camera.ViewMatrix();
        glm::mat4 projection = camera.PerspectiveMatrix();
        shader.ModifyUniform("model", 4, 4, glm::value_ptr(model), false);
        shader.ModifyUniform("view", 4, 4, glm::value_ptr(view), false);
        shader.ModifyUniform("projection", 4, 4, glm::value_ptr(projection), false);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glfwSwapBuffers(window);
        err = glGetError();
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_W && (action == GLFW_PRESS || action == GLFW_REPEAT))
        camera.MoveCamera(CameraMovement::FORWARD);
    if (key == GLFW_KEY_S && (action == GLFW_PRESS || action == GLFW_REPEAT))
        camera.MoveCamera(CameraMovement::BACKWARD);
    if (key == GLFW_KEY_A && (action == GLFW_PRESS || action == GLFW_REPEAT))
        camera.MoveCamera(CameraMovement::LEFT);
    if (key == GLFW_KEY_D && (action == GLFW_PRESS || action == GLFW_REPEAT))
        camera.MoveCamera(CameraMovement::RIGHT);
}

void MouseCallback(GLFWwindow* window, double xpos, double ypos) {
    std::cout << "x: " << xpos << " y: " << ypos << "\n";
    // If camera has not yet been used, prevent camera from jumping around with the mouse is first moved
    if (!cameraUsed) {
        lastXPos = xpos;
        lastYPos = ypos;
        cameraUsed = true;
    }
    camera.MoveDir(xpos - lastXPos, -ypos + lastYPos);
    lastXPos = xpos;
    lastYPos = ypos;
}
