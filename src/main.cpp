// {{{ Includes
#include "headers/pch.hpp"
#include "headers/globals.hpp"
#include "headers/main.hpp"
#include "headers/worm.hpp"
#include "headers/shader.hpp"
// }}}
// {{{ Function Declarations
bool init();
void update(double);
void render(double);
// }}}
// {{{ void main()
int main(){

	if (!init()){
		return -1;
	}

	int width = 2880;
	int height = 1620;

	glm::mat4 Projection = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 100.0f);

	glm::mat4 View = glm::lookAt(glm::vec3(4,3,3), glm::vec3(0,0,0), glm::vec3(0,1,0));

	glm::mat4 Model = glm::mat4(1.0f);

	glm::mat4 mvp = Projection * View * Model;

	static const GLfloat g_vertex_buffer_data[] = {
		-1.0f, -1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		0.0f, 1.0, 0.0f,
	};

	GLuint vertexbuffer;
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
	
	GLuint programID = LoadShaders("src/shaders/SimpleVertexShader.vertexshader", "src/shaders/SimpleFragmentShader.fragmentshader");

	do {
		glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glUseProgram(programID);

		GLuint MatrixID = glGetUniformLocation(programID, "MVP");

		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &mvp[0][0]);

		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		glVertexAttribPointer(
			0,
			3,
			GL_FLOAT,
			GL_FALSE,
			0,
			(void*)0
		);

		glDrawArrays(GL_TRIANGLES, 0, 3);
		glDisableVertexAttribArray(0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	} while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0);
	/*
	auto oldTime = chrono::high_resolution_clock::now();
	auto newTime = chrono::high_resolution_clock::now();
	chrono::duration<double> dt;
	double diff;

	while (running){
		newTime = chrono::high_resolution_clock::now();
		dt = newTime - oldTime;
		oldTime = newTime;
		diff = dt.count();
		update(diff);
		render(diff);
	}
	*/
	return 0;
}
// }}}
// {{{ void init()
bool init(){

	// Get seed
	//cout << "Seed: ";
	//cin >> seed;

	// Seed the random number generator
	//srand(seed);

	// Seed the perlin noise generator and set its parameters
	pnoise.SetSeed(seed);
	pnoise.SetFrequency(FREQUENCY);
	pnoise.SetLacunarity(LACUNARITY);
	pnoise.SetPersistence(PERSISTENCE);
	pnoise.SetOctaveCount(OCTAVES);

	// Set running to true to start game loop
	running = true;

	// OpenGl and glfw setup
	glewExperimental = true;
	if (!glfwInit()){
		cout << "Failed to initialize GLFW" << endl;
		return false;
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(2880, 1620, "Main", NULL, NULL);

	if (window == NULL){
		cout << "Failed to open GLFW window" << endl;
		glfwTerminate();
		return false;
	}

	glfwMakeContextCurrent(window);
	if (glewInit() != GLEW_OK){
		cout << "Failed to initialize GLEW" << endl;
		return false;
	}

	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	// return true if nothing went wrong in init()
	return true;
}
// }}}
// {{{ void update()
void update(double dt){
	cout << "Updating with dt=" << dt << endl;
}
// }}}
// {{{ void render()
void render(double dt){
	cout << "Rendering with dt=" << dt << endl;
}
// }}}
