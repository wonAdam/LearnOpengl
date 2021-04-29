#include <iostream>
#include <fstream>
#include <sstream>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "stb_image.h"


#include "Game.h"
#include "Cube.h"
#include "Shader.h"
#include "Camera.h"

int glfw_Intialization(GLFWwindow** window);
void ImGui_Initialization(GLFWwindow* window);
int gl_Initialization();
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

float deltaTime = 0.0f;
float lastFrame = 0.0f;

float lastX = 400.0f;
float lastY = 300.0f;

int main()
{
    GLFWwindow* window = nullptr;
    int error;
    if ((error = glfw_Intialization(&window)) != 0)
        return error;

    if ((error = gl_Initialization()) != 0)
        return error;

    ImGui_Initialization(window);

    Game::Instance()->Initialize();
    
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        //------ Frame Time ------//
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        //------ Render ------//
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        

        //------ Update ------//
        Game::Instance()->Update(deltaTime, static_cast<float>(glfwGetTime()));

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwTerminate();
    return 0;
}

void ImGui_Initialization(GLFWwindow* window)
{
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    // Setup Platform/Renderer bindings
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    const char* glsl_version = "#version 330";
    ImGui_ImplOpenGL3_Init(glsl_version);
    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
}

int glfw_Intialization(GLFWwindow** window)
{
    /* Initialize the library */
    if (!glfwInit())
        return -1;
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

    /* Create a windowed mode window and its OpenGL context */
    *window = glfwCreateWindow(800, 600, "Hello OpenGL", NULL, NULL);

    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(*window);
    glfwSetFramebufferSizeCallback(*window, framebuffer_size_callback);
    glfwSetInputMode(*window, GLFW_STICKY_KEYS, GLFW_TRUE);
    //glfwSetInputMode(*window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetInputMode(*window, GLFW_CURSOR, GLFW_CURSOR);
    glfwSetKeyCallback(*window, key_callback);
    glfwSetCursorPosCallback(*window, mouse_callback);
    glfwSetScrollCallback(*window, scroll_callback);

    return 0;
}

int gl_Initialization()
{
    glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    if (err != GLEW_OK) {
        // Problem: glewInit failed, something is seriously wrong.
        std::cout << "glewInit failed: " << glewGetErrorString(err) << std::endl;
        return 1;
    }
    glViewport(0, 0, 800, 600);
    glEnable(GL_DEPTH_TEST);

    return 0;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    // When a user presses the escape key, we set the WindowShouldClose property to true,
    const float cameraSpeed = 5.5f * deltaTime; // adjust accordingly
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        Game::gCamera->ProcessKeyboard(Camera::Camera_Movement::FORWARD, deltaTime);
    
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        Game::gCamera->ProcessKeyboard(Camera::Camera_Movement::BACKWARD, deltaTime);

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        Game::gCamera->ProcessKeyboard(Camera::Camera_Movement::LEFT, deltaTime);

    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        Game::gCamera->ProcessKeyboard(Camera::Camera_Movement::RIGHT, deltaTime);

    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) // closing the application
        glfwSetWindowShouldClose(window, GL_TRUE);
}

bool firstMouse = true;
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates range from bottom to top
    lastX = xpos;
    lastY = ypos;

    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) != GLFW_PRESS)
        return;

    Game::gCamera->ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    Game::gCamera->ProcessMouseScroll(yoffset);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}


