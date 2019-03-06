#ifdef WINDOW_MANAGER_GLFW3

#include "../Window.h"
#include "../OpenGL/Debug.h"
#include "../../Util/Debug.h"
#include "Engine/Game.h"
#include "glfw3.h"

namespace Kepler {

const std::string Window::windowAPI = "GLFW3";
const std::string Window::renderAPI = "OpenGL";

void glfwError(int id, const char *description) {
  std::cout << "GLFW Error: " << description << std::endl;
}

Window::Window(int w, int h, std::string t) {
  GLFWwindow *window = (GLFWwindow *)this->window;

  glfwSetErrorCallback(&glfwError);

  // Init GLFW
  if (!glfwInit()) {
    std::cout << "Failed to init GLFW" << std::endl;
    return;
  } else {
    std::cout << "GLFW init." << std::endl;
  }

  // GLFW Hints
  glfwWindowHint(GLFW_SAMPLES, 4);

  // Create window
  window = glfwCreateWindow(w, h, t.c_str(), NULL, NULL);
  if (window == NULL) {
    glfwTerminate();
    std::cout << "Failed to create GLFW window" << std::endl;
    return;
  } else {
    std::cout << "Created Window" << std::endl;
  }

  // Set context
  glfwMakeContextCurrent(window);
  int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

  glfwSetWindowUserPointer(window, this);

  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

  this->window = (void *)window;

  //Setting Debug Messages
  #if KEPLERDEBUG
  GenerateDebugCallbacks();
  #endif

  SetupApi();
  SetupInput();
}

void Window::RenderEnd() {
  std::cout << "RENDER END" << std::endl;
  glfwSwapInterval(1);
  glfwSwapBuffers((GLFWwindow *)window);
}
void Window::PollEvents() { glfwPollEvents(); }
bool Window::ShouldClose() {
  return glfwWindowShouldClose((GLFWwindow *)window);
}
void Window::Terminate() { glfwTerminate(); }
double Window::GetTime() { return glfwGetTime(); }

} // namespace Kepler

#endif
