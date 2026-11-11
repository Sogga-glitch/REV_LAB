#define GLFW_INCLUDE_VULKAN
#include <glfw/glfw3.h>

#include <iostream>

int main(void) {
	if (!glfwInit()) {
		return 1;
	}

	GLFWwindow *window = glfwCreateWindow(1280, 720, "Revlab", NULL, NULL);
	if (!window) {
		return 1;
	}

	uint32_t extensionCount = 0;
	vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);

	std::cout << extensionCount << " extensions supported\n";

	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	return 0;
}