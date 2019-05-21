#include "GraphicsSystem_3d.h"
#include "Debugger.h"
#include <SDL.h>
#include <list>
#include "EntityComponentManager.h"
#include <math.h>
#include <future>
#include "ThreadPool.h"
#include "InputState.h"
#include <mutex>
#include "GameState.h"
#include "PhysicsBodyComponent.h"
#include "EVector.h"
#include "Aabb.h"
#include <SDL_vulkan.h>
#include <vulkan/vulkan.h>


#ifdef NDEBUG
    const bool enableValidationLayers = false;
#else
    const bool enableValidationLayers = true;
#endif

#define VK vulkan;

const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1080;

const int SCREEN_BITSPERPIXEL = 32;




void GraphicsSystem_3d::VulkanInit(){
    if (enableValidationLayers && !checkValidationLayerSupport()){
        throw "VK: validation layers requested, but not available.";
    }



    // Application info
    VkApplicationInfo appInfo = {
    .sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
    .pNext = NULL,
    .pApplicationName = "SGE",
    .applicationVersion = VK_MAKE_VERSION(1,0,0),
    .pEngineName = "SGE",
    .engineVersion = VK_MAKE_VERSION(1,0,0),
    .apiVersion = VK_API_VERSION_1_0,
    };

    // Vulkan create info
    VkInstanceCreateInfo createInfo  {};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &appInfo;

    // Get extensions
    uint32_t extensionCount;
    SDL_Vulkan_GetInstanceExtensions(_window, &extensionCount, nullptr);
    std::vector<const char *> extensionNames(extensionCount);
    SDL_Vulkan_GetInstanceExtensions(_window, &extensionCount, extensionNames.data());

    createInfo .enabledExtensionCount = extensionNames.size();
    createInfo .ppEnabledExtensionNames = extensionNames.data();

    // Get layers
    std::vector<const char *> layerNames {};
    createInfo .enabledLayerCount = layerNames.size();

    if (layerNames.empty() == false){
        createInfo .ppEnabledLayerNames = layerNames.data();
    }

    // Create instance
    if (vkCreateInstance(&createInfo , nullptr, &_instance) != VK_SUCCESS) {
      // do some error checking
      throw "VK: Failed to create Vulkan instance.";
    }

    VkSurfaceKHR surface;

    SDL_Vulkan_CreateSurface(_window, _instance, &surface);
}



GraphicsSystem_3d::GraphicsSystem_3d()
{
    std::unique_lock<std::mutex> lock(_resourceMutex);

    // Initialize SDL
    if (SDL_WasInit(SDL_INIT_VIDEO) == 0){
        SDL_Init(SDL_INIT_VIDEO);
    }

    _window = nullptr;
    _window = SDL_CreateWindow( "Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_VULKAN );


    VulkanInit();
}

GraphicsSystem_3d::~GraphicsSystem_3d()
{
    std::unique_lock<std::mutex> lock(_resourceMutex);

    // Cleanup Vulkan
    vkDestroyInstance(_instance, nullptr);

    // Cleanup SDL
    if (_window != nullptr){
        SDL_DestroyWindow(_window);
        _window = nullptr;
    }
}



bool GraphicsSystem_3d::Process(ECS::EntityComponentManager& ecs){
    DrawScene();
    return true;
}


void GraphicsSystem_3d::DrawScene(){
    std::unique_lock<std::mutex> lock(_resourceMutex);

    VkSurfaceKHR surface;

    SDL_Vulkan_CreateSurface(_window, _instance, &surface);
}

bool GraphicsSystem_3d::checkValidationLayerSupport(){
    uint32_t layerCount;
    vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

    std::vector<VkLayerProperties> availableLayers(layerCount);
    vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

    for (const char* layerName : availableLayers.data()) {
        bool layerFound = false;

        for (const auto& layerProperties : availableLayers) {
            if (strcmp(layerName, layerProperties.layerName) == 0) {
                layerFound = true;
                break;
            }
        }

        if (!layerFound) {
            return false;
        }
    }

    return true;

}
