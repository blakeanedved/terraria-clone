#include "headers/main.hpp"

bool init();

int main(){

	if (!init()){
		return -1;
	}

	tiles.push_back(Tile(-0.75f, -0.75f, 0, glm::vec4(1.0f, 0.0f, 0.0f, 1.0f)));
	tiles.push_back(Tile(-0.5f, -0.5f, 0, glm::vec4(0.0f, 1.0f, 0.0f, 1.0f)));
	tiles.push_back(Tile(-0.25f, -0.25f, 0, glm::vec4(0.0f, 0.0f, 1.0f, 1.0f)));

	int width = 2880;
	int height = 1620;

	glm::mat4 Projection = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 100.0f);

	glm::mat4 View = glm::lookAt(glm::vec3(4,3,3), glm::vec3(0,0,0), glm::vec3(0,1,0));

	glm::mat4 Model = glm::mat4(1.0f);

	glm::mat4 mvp = Projection * View * Model;

	GLuint programID = LoadShaders("src/shaders/vert.glsl", "src/shaders/frag.glsl");
	glUseProgram(programID);
	// GLuint MatrixID = glGetUniformLocation(programID, "MVP");

	GLuint u_Color = glGetUniformLocation(programID, "u_Color");
	
	do {
		glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &mvp[0][0]);

		for (auto &tile : tiles){
			tile.SetColor(u_Color);
			tile.Render();
		}

		window->PollEvents();
	} while (!window->ShouldClose());

	return 0;
}

bool init(){

	// Seed the random number generator
	//srand(seed);

	// Seed the perlin noise generator and set its parameters
	pnoise.SetSeed(time(NULL));
	pnoise.SetFrequency(FREQUENCY);
	pnoise.SetLacunarity(LACUNARITY);
	pnoise.SetPersistence(PERSISTENCE);
	pnoise.SetOctaveCount(OCTAVES);

	window = std::unique_ptr<Window>(new Window(2880, 1620, (char*)"Main"));

	// return true if nothing went wrong in init()
	return true;
}