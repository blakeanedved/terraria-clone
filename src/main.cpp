#include "headers/main.hpp"

int width = 2880;
int height = 1620;
double FPS = 60.0;

auto init() -> void;
auto update(double dt) -> void;
auto render() -> void;

int main() {

#warning TODO: NORMALIZE COORDINATE SYSTEM, SOME START 0 AT BOTTOM AND OTHERS AT TOP, MAKE A DESCISION

    init();

    std::unique_ptr<Shader> playerShader = std::make_unique<Shader>(
        "src/shaders/player/vert.glsl", "src/shaders/player/frag.glsl");
    playerShader->Bind();
    playerShader->AddUniform("MVP");
    playerShader->AddUniform("u_Texture");
    playerShader->SetUniform("MVP", camera->MVP);
    playerShader->SetUniform("u_Texture", 0);

    double frameTime = 1.0 / FPS;
    double lastTime, currentTime, dt, nextFrame = 0;
    lastTime = glfwGetTime();
    double temp = 0.0;
    do {
        currentTime = glfwGetTime();
        dt = currentTime - lastTime;
        nextFrame += dt;
        temp += dt;
        lastTime = currentTime;

        // if (temp >= 0.25) {
        //     tm->IncrementColumn();
        //     temp = 0.0;
        // }

        if (nextFrame >= frameTime) {
            update(nextFrame);
            render();
            playerShader->Bind();
            player->Render();
            // std::cout << "FPS: " << (1.0f / nextFrame) << std::endl;
            nextFrame = 0.0;
            window->PollEvents(); // This needs to be here
                                  // otherwise window just lags
        }

    } while (!window->ShouldClose());

    return 0;
}

auto init() -> void {

    seed = time(NULL);

    // Seed the random number generator
    srand(seed);

    // Seed the perlin noise generator and set its parameters
    noisegen = std::make_unique<NoiseGenerator>(SCALE);
    noisegen->SetSeed(seed);
    noisegen->SetFrequency(FREQUENCY);
    noisegen->SetLacunarity(LACUNARITY);
    noisegen->SetPersistence(PERSISTENCE);
    noisegen->SetOctaveCount(OCTAVES);

    window = std::make_unique<Window>(width, height, (char *)"Main");

    player = std::make_unique<Player>(glm::vec2(0, 100));

    camera = std::make_unique<Camera>(glm::vec3(0.0f, 0.0f, 0.0f),
                                      glm::vec4(0.0f, width, 0.0f, height));

    tm = std::make_unique<TileMap>(width, height);
}

auto update(double dt) -> void {
    player->Update(dt);
    // tm->DecrementRow();
}

auto render() -> void {
    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    tm->Render();
}