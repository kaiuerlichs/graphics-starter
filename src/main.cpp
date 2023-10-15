/*
 * Include the header to the GLFW wrapper class which
 * also includes the OpenGL extension initialisation
 */
#include "wrapper_glfw.h"
#include <iostream>

GLuint positionBufferObject;
GLuint program;
GLuint vao;

using namespace std;

/*
 * This function is called before entering the main rendering loop.
 * Use it for all you initialisation stuff
 */
void init(GLWrapper *glw)
{
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	float vertexPositions[] = {
		0.75f, 0.75f, 0.0f, 1.0f,
		0.75f, -0.75f, 0.0f, 1.0f,
		-0.75f, -0.75f, 0.0f, 1.0f,
	};

	glGenBuffers(1, &positionBufferObject);
	glBindBuffer(GL_ARRAY_BUFFER, positionBufferObject);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexPositions), vertexPositions, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	try
	{
		program = glw->LoadShader("shaders/basic.vert", "shaders/basic.frag");
	}
	catch (exception &e)
	{
		cout << "Caught exception: " << e.what() << endl;
		cin.ignore();
		exit(0);
	}

	glw->DisplayVersion();
}

/*
 * Called to update the display.
 * You should call glfwSwapBuffers() after all of your rendering to display what you rendered.
 */
void display()
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(program);

	glBindBuffer(GL_ARRAY_BUFFER, positionBufferObject);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);

	glDrawArrays(GL_TRIANGLES, 0, 3);

	glDisableVertexAttribArray(0);
	glUseProgram(0);
}

/*
 * Called whenever the window is resized. The new window size is given, in pixels.
 */
static void reshape(GLFWwindow* window, int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
}

/*
 * change view angle, exit upon ESC
 */
static void keyCallback(GLFWwindow* window, int k, int s, int action, int mods)
{
	if (action != GLFW_PRESS) return;
	if (k == GLFW_KEY_ESCAPE)
    {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
}

/*
 * An error callback function to output GLFW errors
 */
static void errorCallback(int error, const char* description)
{
	fputs(description, stderr);
}

/*
 * Entry point of program
 */
int main(int argc, char* argv[])
{
	const char * title = "Graphics Starter";
	auto *glw = new GLWrapper(1080, 720, title);

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		cout << "Failed to initialize GLAD. Exiting." << endl;
		return -1;
	}

	glw->setRenderer(display);
	glw->setKeyCallback(keyCallback);
	glw->setReshapeCallback(reshape);
    glw->setErrorCallback(errorCallback);

	init(glw);

	glw->eventLoop();

	delete(glw);
	return 0;
}