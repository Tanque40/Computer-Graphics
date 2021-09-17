#include <GLFW/glfw3.h>
#include <stdio.h>

void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    else if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
        printf("tecla r\n");
}
int main() {
    glfwInit();
    GLFWwindow* window = glfwCreateWindow(800, 600, "Ejemplo glfw", NULL, NULL);
    while (!glfwWindowShouldClose(window)) {
        processInput(window);
        // Dibujar algo
        glfwWaitEvents();
    }
    glfwTerminate();
    return 0;
}