#ifndef _TC_WINDOW_HPP_
#define _TC_WINDOW_HPP_
#include "pch.hpp"

class Window {
  private:
    GLFWwindow *window;
    int width, height;

  public:
    Window(int width, int height, char *title);
    ~Window();
    auto IsKeyDown(int key) -> bool;
    auto ShouldClose() -> bool;
    auto PollEvents() -> void;
};

#endif