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

const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1080;

const int SCREEN_BITSPERPIXEL = 32;


void VulkanInit(SDL_Window* window, VkInstance& instance){
    // init settings n stuff; https://www.gamedev.net/forums/topic/699117-vulkan-with-sdl2-getting-started/?do=findComment&comment=5391959
    uint32_t extensionCount;
    SDL_Vulkan_GetInstanceExtensions(window, &extensionCount, nullptr);
    std::vector<const char *> extensionNames(extensionCount);
    SDL_Vulkan_GetInstanceExtensions(window, &extensionCount, extensionNames.data());

    VkApplicationInfo appInfo {};
    // TODO: fill this out

    std::vector<const char *> layerNames {};
    // uncomment below if you want to use validation layers
    // layerNames.push_back("VK_LAYER_LUNARG_standard_validation");

    // clean up?
    VkApplicationInfo app = {
    .sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
    .pNext = NULL,
    .pApplicationName = "SGE",
    .applicationVersion = 0,
    .pEngineName = "SGE",
    .engineVersion = 0,
    .apiVersion = VK_API_VERSION_1_0,
    };


    VkInstanceCreateInfo info {};
    info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    info.pApplicationInfo = &appInfo;
    info.enabledLayerCount = layerNames.size();
    info.ppEnabledLayerNames = layerNames.data();
    info.enabledExtensionCount = extensionNames.size();
    info.ppEnabledExtensionNames = extensionNames.data();

    VkResult res;
    res = vkCreateInstance(&info, nullptr, &instance);
    if (res != VK_SUCCESS) {
      // do some error checking
    }

    // select physical device:
  //  VkPhysicalDevice *physical_devices = malloc(sizeof(VkPhysicalDevice) * gpu_count);
  //  err = vkEnumeratePhysicalDevices(demo->inst, &gpu_count, physical_devices);
  //  demo->gpu = physical_devices[0];

    VkSurfaceKHR surface;

    SDL_Vulkan_CreateSurface(window, instance, &surface);
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


    VulkanInit(_window, _instance);
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
    SGE::Debugger::Instance().WriteMessage("yo");
    DrawScene();
    return true;
}


void GraphicsSystem_3d::DrawScene(){
    std::unique_lock<std::mutex> lock(_resourceMutex);

    VkSurfaceKHR surface;

    SDL_Vulkan_CreateSurface(_window, _instance, &surface);
}
