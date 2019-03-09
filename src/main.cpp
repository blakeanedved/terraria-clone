#include "headers/main.hpp"

int width = 2880;
int height = 1620;
double FPS = 60.0;

auto init() -> void;
auto update(double dt) -> void;
auto render(double dt) -> void;

int main() {

    init();

#warning TODO: Make a camera class
    // glm::mat4 Projection = glm::perspective(glm::radians(45.0f), (float)width
    // / (float)height, 0.1f, 100.0f);
    glm::mat4 Projection =
        glm::ortho(0.0f, (float)width, 0.0f, (float)height, -1.0f, 1.0f);

    glm::mat4 View = glm::mat4(1.0f); // glm::lookAt(glm::vec3(0,0,3),
                                      // glm::vec3(0,0,0), glm::vec3(0,1,0));

    glm::mat4 Model = glm::mat4(1.0f);

    glm::mat4 mvp = Projection * View * Model;

#warning TODO: abstract shaders somehow
    GLuint programID =
        LoadShaders("src/shaders/vert.glsl", "src/shaders/frag.glsl");
    glUseProgram(programID);

    GLuint MatrixID = glGetUniformLocation(programID, "MVP");
    GLuint u_Texture = glGetUniformLocation(programID, "u_Texture");
    glUniform1i(u_Texture, 0);
    glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &mvp[0][0]);

    double frameTime = 1.0 / FPS;
    double lastTime, currentTime, dt, nextFrame = 0;
    lastTime = glfwGetTime();
    do {
        currentTime = glfwGetTime();
        dt = currentTime - lastTime;
        nextFrame += dt;
        lastTime = currentTime;

        if (nextFrame >= frameTime) {
            update(nextFrame);
            render(nextFrame);
            // std::cout << "Time for frame" << nextFrame << std::endl;
            nextFrame = 0.0;
            window->PollEvents(); // This needs to be here otherwise window just
                                  // lags
        }

    } while (!window->ShouldClose());

    return 0;
}

auto init() -> void {

    seed = time(NULL);

    // Seed the random number generator
    srand(seed);

    // Seed the perlin noise generator and set its parameters
    noisegen = std::unique_ptr<NoiseGenerator>(new NoiseGenerator(SCALE));
    noisegen->SetSeed(seed);
    noisegen->SetFrequency(FREQUENCY);
    noisegen->SetLacunarity(LACUNARITY);
    noisegen->SetPersistence(PERSISTENCE);
    noisegen->SetOctaveCount(OCTAVES);

    window = std::unique_ptr<Window>(new Window(width, height, (char *)"Main"));

    tm = std::unique_ptr<TileMap>(new TileMap(width, height));

    player = std::unique_ptr<Player>(new Player(glm::vec2(100.0, 100.0)));
}

auto update(double dt) -> void { player->Update(dt); }

auto render(double dt) -> void {
    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    tm->Render();
    player->Render();
}