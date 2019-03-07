#include "../headers/pch.hpp"
#include "../headers/window.hpp"

Window::Window(int width, int height, char* title){

	this->width = width;
	this->height = height;

	// OpenGl and glfw setup
	glewExperimental = true;
	if (!glfwInit()){
		std::cout << "Failed to initialize GLFW" << std::endl;
		exit(-1);
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	this->window = glfwCreateWindow(width, height, title, NULL, NULL);

	if (this->window == NULL){
		std::cout << "Failed to open GLFW window" << std::endl;
		glfwTerminate();
		exit(-1);
	}

	glfwMakeContextCurrent(this->window);

	glfwSetKeyCallback(this->window, [](auto* window, int key, int scancode, int action, int mods) {
        if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
            glfwSetWindowShouldClose(window, GLFW_TRUE);
        }
    });

	if (glewInit() != GLEW_OK){
		std::cout << "Failed to initialize GLEW" << std::endl;
		exit(-1);
	}

	// glEnable(GL_BLEND);
	// glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

Window::~Window(){
	glfwTerminate();
}

auto Window::IsKeyDown(int key) -> bool {
	return glfwGetKey(this->window, key);
}

auto Window::ShouldClose() -> bool {
	return glfwWindowShouldClose(this->window) == GLFW_TRUE;
}

auto Window::PollEvents() -> void {
	glfwSwapBuffers(this->window);
	glfwPollEvents();
}