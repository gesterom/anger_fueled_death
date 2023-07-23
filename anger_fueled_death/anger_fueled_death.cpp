#define SDL_MAIN_HANDLED // We'll manage SDL's main ourselves
#include <SDL2/SDL.h>
#include <vulkan/vulkan.h>
#include <iostream>
#include <stdexcept>
#include <vector>

const int WIDTH = 800;
const int HEIGHT = 600;

void initSDL() {
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		throw std::runtime_error("Failed to initialize SDL.");
	}
}

void createWindow(SDL_Window*& window, SDL_Renderer*& renderer) {
	window = SDL_CreateWindow(
		"SDL2 Vulkan Window",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		WIDTH,
		HEIGHT,
		SDL_WINDOW_VULKAN | SDL_WINDOW_SHOWN
	);

	if (!window) {
		throw std::runtime_error("Failed to create SDL window.");
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (!renderer) {
		throw std::runtime_error("Failed to create SDL renderer.");
	}
}

void initVulkan() {
	VkInstance instance;

	VkApplicationInfo appInfo = {};
	appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	appInfo.pApplicationName = "My Vulkan Application";
	appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
	appInfo.pEngineName = "No Engine";
	appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
	appInfo.apiVersion = VK_API_VERSION_1_0;

	VkInstanceCreateInfo createInfo = {};
	createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	createInfo.pApplicationInfo = &appInfo;

	// Enable validation layers if desired (optional)
	const char* validationLayer = "VK_LAYER_KHRONOS_validation";
	createInfo.enabledLayerCount = 1;
	createInfo.ppEnabledLayerNames = &validationLayer;

	VkResult result = vkCreateInstance(&createInfo, nullptr, &instance);
	if (result != VK_SUCCESS) {
		throw std::runtime_error("Failed to create Vulkan instance.");
	}
	// TODO: Continue with Vulkan setup
}

void cleanup(SDL_Window* window, SDL_Renderer* renderer) {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

int main() {
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;

	try {
		initSDL();
		createWindow(window, renderer);
		initVulkan();

		bool quit = false;
		while (!quit) {
			SDL_Event event;
			while (SDL_PollEvent(&event)) {
				if (event.type == SDL_QUIT) {
					quit = true;
				}
			}

			// TODO: Rendering and Vulkan code here

			// Present the rendered frame with SDL
			SDL_RenderPresent(renderer);
		}
	}
	catch (const std::exception& e) {
		std::cerr << "Exception: " << e.what() << std::endl;
		return EXIT_FAILURE;
	}
}