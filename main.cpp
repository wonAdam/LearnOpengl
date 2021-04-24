#include <iostream>
#include <fstream>
#include <sstream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#define MAX_SHADER_LENGTH 4096

const char* read_shader(const char* path)
{
    std::ifstream file(path);
    std::stringstream shader;
    std::string temp;
    if (file.is_open())
    {
        while (std::getline(file, temp))
            shader << temp << '\n';
    }
    else
        std::cout << "shader open error" << std::endl;

    char* result = new char[shader.str().length() + 1];
    strcpy_s(result, shader.str().length() + 1, shader.str().c_str());
    return result;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action,
    int mode)
{
    // When a user presses the escape key, we set the WindowShouldClose property to true,
    // closing the application
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}

GLuint ShaderObject(const char* path, GLint shaderType)
{
    const char* source = read_shader(path);
    std::cout << source << std::endl;

    GLint shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, &source, NULL);
    glCompileShader(shader);

    {
        GLint success;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            char infoLog[512];
            glGetShaderInfoLog(shader, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
        }
    }

    return shader;
}

GLuint ShaderProgram(GLuint vertShader, GLuint fragShader)
{
    GLuint shaderProgram;
    shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram, vertShader);
    glAttachShader(shaderProgram, fragShader);
    glLinkProgram(shaderProgram);

    {
        GLint success;
        glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
        if (!success) {
            char infoLog[512];
            glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
        }
    }

    glDeleteShader(vertShader);
    glDeleteShader(fragShader);

    return shaderProgram;
}



int main()
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);


    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    glViewport(0, 0, 800, 600);

    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, key_callback);
    
    glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    if (err != GLEW_OK) {
        // Problem: glewInit failed, something is seriously wrong.
        std::cout << "glewInit failed: " << glewGetErrorString(err) << std::endl;
        exit(1);
    }

    GLfloat vertices[] = {
        -0.5f,  -0.5f,  0.0f,
        0.5f,   -0.5f,  0.0f,
        0.0f,   0.5f,   0.0f
    };

    GLuint VBO;
    glGenBuffers(1, &VBO);
    GLuint VAO;
    glGenVertexArrays(1, &VAO);

    // select vertex array
    glBindVertexArray(VAO);

    // select buffer
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    // send data to the buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // set attribute pointer in vertex data
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 3, (void*)0);
    glEnableVertexAttribArray(0);


    GLuint  vertShader = ShaderObject("vertexshader.vert", GL_VERTEX_SHADER);
    GLuint  fragShader = ShaderObject("fragmentshader.frag", GL_FRAGMENT_SHADER);
    GLuint shaderProgram = ShaderProgram(vertShader, fragShader);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}