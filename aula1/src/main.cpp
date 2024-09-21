#include <iostream>
#include "glad.h"
#include <GLFW/glfw3.h>

using std::cout;
using std::endl;


const char *vertexShaderSource="#version 330 core\n"
"layout (location = 0 ) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z,1.0f);\n"
"}\n\0";
const char *fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor=vec4(1.0f,0.5f,0.2f,1.0f);\n"
"}\n\0";


int main()
{
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);

    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);


  


    GLFWwindow* window = glfwCreateWindow(800,600,"Learn Opengl",NULL,NULL);

    if(window == NULL)
    {
        cout << "Failed to create window" << endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    /*
    if(!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
    {
        cout << "Failed to load Glad" << endl;
        return -1;
    }*/

    gladLoadGL();

    glViewport(0,0,800,600);

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader,1,&vertexShaderSource,NULL);
    glCompileShader(vertexShader);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader,1,&fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    GLint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    GLfloat vertices[] =
	{
		-0.5f, -0.5f, 0.0f, // Lower left corner
		0.5f, -0.5f , 0.0f, // Lower right corner
		0.0f, 0.5f , 0.0f // Upper corner
	};


    GLuint VAO, VBO;
    glGenVertexArrays(1,&VAO);
    glBindVertexArray(VAO);
    
    glGenBuffers(1,&VBO);

    //VAO the current vertex buffer to bind

    //Bind VBO specifying its a array buffer
    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    //Verticies in the array buffer
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices, GL_STATIC_DRAW);

    //COnffigure the vertex attributes and opengl will know how to read VBO
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE, 3*sizeof(float), (void*)0);
    //Enable the vertex atriibute
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER,0);
    glBindVertexArray(0);



    glClearColor(0.07f,0.13f,0.17f,1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glfwSwapBuffers(window);
    



    while(!glfwWindowShouldClose(window))
    {
        glClearColor(0.07f,0.13f,0.17f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES,0,3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteBuffers(1,&VBO);
    glDeleteVertexArrays(1,&VAO);
    glDeleteProgram(shaderProgram);

    glfwDestroyWindow(window);
    glfwTerminate();



    return 0;
}