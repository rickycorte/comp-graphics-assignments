// Following the Vulkan Tutorial as shown in the enclose Assignment13.pdf, complete
// this Vulkan initialization sample. You can copy and past code from Example E08,
// or from other assginments such as Assignment0.cpp

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <vector>
#include <optional>
#include <set>

const uint32_t WIDTH = 640;
const uint32_t HEIGHT = 480;

class Assignment14 {
public:
    void run() {
        initWindow();
        initVulkan();
        initApp();
        mainLoop();
        cleanup();
    }

private:
    // place all the application variables here. As an example, here the one for the GLFW Window
    // and the Vulkan instances are already defined.

    GLFWwindow* window;

    VkInstance instance;

    VkSurfaceKHR surface;

    VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
    std::optional<uint32_t> aQueueWithGraphicsCapability;
    std::optional<uint32_t> aQueueWithPresentationCapability;

    VkDevice logicDevice;
    float queuePriority = 1.0f;
    VkQueue graphicsQueue;
    VkQueue presentQueue;

    VkCommandPool commandPool;

    VkCommandBuffer commandBuffer;

    VkSwapchainKHR swapChain;
    uint32_t chainImageCount;
    VkSurfaceFormatKHR surfaceFormat;
    VkPresentModeKHR presentMode;
    VkExtent2D extent;

    std::vector<VkImage> swapChainImages;

    std::vector<VkImageView> swapChainImageViews;

    // INIT WINDOW -----------------------------------------------------------------------------
    void initWindow() {
        glfwInit();


        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

        window = glfwCreateWindow(WIDTH, HEIGHT, "Assignment 14", nullptr, nullptr);
    }

    // INIT INSTANCE -----------------------------------------------------------------------------
    VkApplicationInfo getAppInfo()
    {
        VkApplicationInfo appInfo{};
        appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        appInfo.pApplicationName = "Assignment 12";
        appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.pEngineName = "No Engine";
        appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.apiVersion = VK_API_VERSION_1_0;
        return appInfo;
    }

    VkResult createInstance()
    {
        VkInstanceCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        createInfo.pApplicationInfo = &getAppInfo();

        uint32_t glfwExtensionCount = 0;
        const char** glfwExtensions;

        glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

        createInfo.enabledExtensionCount = glfwExtensionCount;
        createInfo.ppEnabledExtensionNames = glfwExtensions;
        createInfo.enabledLayerCount = 0;

        return vkCreateInstance(&createInfo, nullptr, &instance);
    }

    // PICK PHISICAL -----------------------------------------------------------------------------
    bool isDeviceSuitable(VkPhysicalDevice device)
    {

        uint32_t queueFamilyCount = 0;
        vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

        std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
        vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());

        for (unsigned int i = 0; i < queueFamilyCount; i++) {
            if ((queueFamilies[i].queueFlags & VK_QUEUE_GRAPHICS_BIT) != 0) {
                std::cout << " Graphics";
                aQueueWithGraphicsCapability = i;
            }
            VkBool32 presentSupport = false;
            vkGetPhysicalDeviceSurfaceSupportKHR(device, i, surface, &presentSupport);
            if (presentSupport) {
                aQueueWithPresentationCapability = i;
            }
        }

        return aQueueWithGraphicsCapability.has_value() && aQueueWithPresentationCapability.has_value();
    }

    void pickPhysicalDevice()
    {
        uint32_t deviceCount = 0;
        vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);
        if (deviceCount == 0) {
            throw std::runtime_error("failed to find GPUs with Vulkan support!");
        }

        std::vector<VkPhysicalDevice> devices(deviceCount);
        vkEnumeratePhysicalDevices(instance, &deviceCount, devices.data());

        for (const auto& device : devices)
        {
            if (isDeviceSuitable(device)) {
                physicalDevice = device;
                break;
            }
        }

        std::cout << physicalDevice << "\n";

    }

    // INIT LOGICAL -----------------------------------------------------------------------------
    void createLogicalDevice()
    {
        VkPhysicalDeviceFeatures deviceFeatures{};
        VkDeviceCreateInfo createInfo{};

        std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
        std::set<uint32_t> uniqueQueueFamilies =
        {   aQueueWithGraphicsCapability.value(),
            aQueueWithPresentationCapability.value() 
        };
        const std::vector<const char*> deviceExtensions = {
            VK_KHR_SWAPCHAIN_EXTENSION_NAME
        };

        for (uint32_t queueFamily : uniqueQueueFamilies) {
            VkDeviceQueueCreateInfo queueCreateInfo{};
            queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
            queueCreateInfo.queueFamilyIndex = queueFamily;
            queueCreateInfo.queueCount = 1;
            queueCreateInfo.pQueuePriorities = &queuePriority;
            queueCreateInfos.push_back(queueCreateInfo);
        }

        createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
        createInfo.pQueueCreateInfos = queueCreateInfos.data();
        createInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());
        createInfo.pEnabledFeatures = &deviceFeatures;
        createInfo.enabledExtensionCount = static_cast<uint32_t>(deviceExtensions.size());;
        createInfo.ppEnabledExtensionNames = deviceExtensions.data();
        createInfo.enabledLayerCount = 0;

        auto result = vkCreateDevice(physicalDevice, &createInfo, nullptr, &logicDevice);

        if (result != VK_SUCCESS) {
            throw std::runtime_error("failed to create logical device!");
        }

        vkGetDeviceQueue(logicDevice, aQueueWithGraphicsCapability.value(), 0, &graphicsQueue);
        vkGetDeviceQueue(logicDevice, aQueueWithPresentationCapability.value(), 0, &presentQueue);

        std::cout << logicDevice << "\n";
    }


    // INIT CMD POOL -----------------------------------------------------------------------------
    void initCommandPool()
    {
        VkCommandPoolCreateInfo poolInfo{};
        poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
        poolInfo.queueFamilyIndex = aQueueWithGraphicsCapability.value();
        poolInfo.flags = 0; // Optional
        auto result = vkCreateCommandPool(logicDevice, &poolInfo, nullptr, &commandPool);
        if (result != VK_SUCCESS) {
            throw std::runtime_error("failed to create command pool!");
        }
    }

    // INIT BUFFER -----------------------------------------------------------------------------
    void initCmdBuffer()
    {
        VkCommandBufferAllocateInfo allocInfo{};
        allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
        allocInfo.commandPool = commandPool;
        allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
        allocInfo.commandBufferCount = 1;
        auto result = vkAllocateCommandBuffers(logicDevice, &allocInfo, &commandBuffer);
        if (result != VK_SUCCESS) {
            throw std::runtime_error("failed to allocate command buffer!");
        }
    }

    // INIT SWAP CHAIN -----------------------------------------------------------------------------

    VkSurfaceFormatKHR chooseSwapSurfaceFormat(
        const std::vector<VkSurfaceFormatKHR>& availableFormats)
    {
        for (const auto& availableFormat : availableFormats) {
            if (availableFormat.format == VK_FORMAT_B8G8R8A8_SRGB &&
                availableFormat.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR) {
                return availableFormat;
            }
        }

        return availableFormats[0];
    }

    VkPresentModeKHR chooseSwapPresentMode(
        const std::vector<VkPresentModeKHR>& availablePresentModes) {
        for (const auto& availablePresentMode : availablePresentModes) {
            if (availablePresentMode == VK_PRESENT_MODE_MAILBOX_KHR) {
                return availablePresentMode;
            }
        }
        return VK_PRESENT_MODE_FIFO_KHR;
    }

    VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities,
        GLFWwindow* window) {
        if (capabilities.currentExtent.width != UINT32_MAX) {
            return capabilities.currentExtent;
        }
        else {
            int width, height;
            glfwGetFramebufferSize(window, &width, &height);

            VkExtent2D actualExtent = {
                static_cast<uint32_t>(width),
                static_cast<uint32_t>(height)
            };
            actualExtent.width = std::max(capabilities.minImageExtent.width,
                std::min(capabilities.maxImageExtent.width, actualExtent.width));
            actualExtent.height = std::max(capabilities.minImageExtent.height,
                std::min(capabilities.maxImageExtent.height, actualExtent.height));
            return actualExtent;
        }
    }

    void initSwapChain()
    {
        // capabilities
        VkSurfaceCapabilitiesKHR SCcapabilities;
        vkGetPhysicalDeviceSurfaceCapabilitiesKHR(physicalDevice, surface, &SCcapabilities);
        std::cout << "\t Min. Image Count: " << SCcapabilities.minImageCount << "\n";
        std::cout << "\t Max. Image Count: " << SCcapabilities.maxImageCount << "\n";
        std::cout << "\t Min. Image Exent: " << SCcapabilities.minImageExtent.width << "x" <<
            SCcapabilities.minImageExtent.height << "\n";
        std::cout << "\t Cur. Image Exent: " << SCcapabilities.currentExtent.width << "x" <<
            SCcapabilities.currentExtent.height << "\n";
        std::cout << "\t Max. Image Exent: " << SCcapabilities.maxImageExtent.width << "x" <<
            SCcapabilities.maxImageExtent.height << "\n";
        std::cout << "\n";

        // formats
        uint32_t formatCount;
        vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice, surface, &formatCount,
            nullptr);

        std::vector<VkSurfaceFormatKHR> SCformats;
        if (formatCount != 0) {
            SCformats.resize(formatCount);
            vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice, surface, &formatCount, SCformats.data());
            std::cout << "\t Supported Formats: " << formatCount << "\n";
            for (int i = 0; i < formatCount; i++) {
                std::cout << "\t\tFormat: " << SCformats[i].format << ", Color Space:" << SCformats[i].colorSpace << "\n";
            }
        }
        std::cout << "\n";

        // modes
        uint32_t presentModeCount;
        vkGetPhysicalDeviceSurfacePresentModesKHR(physicalDevice, surface,
            &presentModeCount, nullptr);

        std::vector<VkPresentModeKHR> SCpresentModes;
        if (presentModeCount != 0) {
            SCpresentModes.resize(presentModeCount);
            vkGetPhysicalDeviceSurfacePresentModesKHR(physicalDevice, surface,
                &presentModeCount, SCpresentModes.data());
            std::cout << "\t Supported Modes: " << presentModeCount << "\n";
            for (int i = 0; i < presentModeCount; i++) {
                switch (SCpresentModes[i]) {
                case VK_PRESENT_MODE_IMMEDIATE_KHR:
                    std::cout << "\t\tVK_PRESENT_MODE_IMMEDIATE_KHR\n";
                    break;
                case VK_PRESENT_MODE_MAILBOX_KHR:
                    std::cout << "\t\tVK_PRESENT_MODE_MAILBOX_KHR\n";
                    break;
                case VK_PRESENT_MODE_FIFO_KHR:
                    std::cout << "\t\tVK_PRESENT_MODE_FIFO_KHR\n";
                    break;
                case VK_PRESENT_MODE_FIFO_RELAXED_KHR:
                    std::cout << "\t\tVK_PRESENT_MODE_FIFO_RELAXED_KHR\n";
                    break;
                default:
                    std::cout << "\t\tMode: " << SCpresentModes[i] << "\n";
                    break;
                }
            }
        }
        std::cout << "\n";

        // select end create swapchain
        surfaceFormat = chooseSwapSurfaceFormat(SCformats);
        presentMode = chooseSwapPresentMode(SCpresentModes);
        extent = chooseSwapExtent(SCcapabilities, window);

        chainImageCount = SCcapabilities.minImageCount + 1;

        if (SCcapabilities.maxImageCount > 0 &&
            chainImageCount > SCcapabilities.maxImageCount) {
            chainImageCount = SCcapabilities.maxImageCount;
        }

        VkSwapchainCreateInfoKHR SCcreateInfo{};
        SCcreateInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
        SCcreateInfo.surface = surface;
        SCcreateInfo.minImageCount = chainImageCount;
        SCcreateInfo.imageFormat = surfaceFormat.format;
        SCcreateInfo.imageColorSpace = surfaceFormat.colorSpace;
        SCcreateInfo.imageExtent = extent;
        SCcreateInfo.imageArrayLayers = 1;
        SCcreateInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

        uint32_t queueFamilyIndices[] = { aQueueWithGraphicsCapability.value(),
                                         aQueueWithPresentationCapability.value() };
        if (aQueueWithPresentationCapability != aQueueWithPresentationCapability) {
            SCcreateInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
            SCcreateInfo.queueFamilyIndexCount = 2;
            SCcreateInfo.pQueueFamilyIndices = queueFamilyIndices;
        }
        else {
            SCcreateInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
            SCcreateInfo.queueFamilyIndexCount = 0;
            SCcreateInfo.pQueueFamilyIndices = nullptr;
        }

        SCcreateInfo.preTransform = SCcapabilities.currentTransform;
        SCcreateInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
        SCcreateInfo.presentMode = presentMode;
        SCcreateInfo.clipped = VK_TRUE;
        SCcreateInfo.oldSwapchain = VK_NULL_HANDLE;

        VkResult result = vkCreateSwapchainKHR(logicDevice, &SCcreateInfo, nullptr, &swapChain);

        if (result != VK_SUCCESS) {
            throw std::runtime_error("failed to create swap chain!");
        }
    }

    void getChainImages()
    {
        vkGetSwapchainImagesKHR(logicDevice, swapChain, &chainImageCount, nullptr);
        swapChainImages.resize(chainImageCount);
        vkGetSwapchainImagesKHR(logicDevice, swapChain, &chainImageCount, swapChainImages.data());
    }

    // INIT IMAGE VIEW -----------------------------------------------------------------------------

    void initImageView() {

        swapChainImageViews.resize(swapChainImages.size());

        for (size_t i = 0; i < swapChainImages.size(); i++) {
            VkImageViewCreateInfo viewInfo{};
            viewInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
            viewInfo.image = swapChainImages[i];
            viewInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
            viewInfo.format = surfaceFormat.format;
            viewInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
            viewInfo.subresourceRange.baseMipLevel = 0;
            viewInfo.subresourceRange.levelCount = 1;
            viewInfo.subresourceRange.baseArrayLayer = 0;
            viewInfo.subresourceRange.layerCount = 1;

            VkImageView imageView;

            VkResult result = vkCreateImageView(logicDevice, &viewInfo, nullptr,
                &imageView);
            if (result != VK_SUCCESS) {
                throw std::runtime_error("failed to create image view!");
            }

            swapChainImageViews[i] = imageView;
        }
    }

    // INIT VULKAN -----------------------------------------------------------------------------
    void initVulkan() {
        if (createInstance() != VK_SUCCESS)
            throw std::runtime_error("failed to create instance!");

        // Prsentation Surface Creation
        if (glfwCreateWindowSurface(instance, window, nullptr, &surface) != VK_SUCCESS)
            throw std::runtime_error("failed to create window surface!");

        // Physical Device selection
        pickPhysicalDevice();

        // Logical Device creation
        createLogicalDevice();

        // Command Pool creation
        initCommandPool();

        // Command Buffer creation
        initCmdBuffer();

        // Swap chain creation
        initSwapChain();
        getChainImages();
        
        // Image view creation
        initImageView();

    }


    // APP -----------------------------------------------------------------------------

    void initApp() {
        // This will not be needed in this assignment!
    }

    void mainLoop() {
        // Wait for the window to close [you can take it from Assingment 12]
        while (!glfwWindowShouldClose(window)) {
            glfwPollEvents();
        }
    }

    void cleanup() {

        for (size_t i = 0; i < swapChainImageViews.size(); i++) {
            vkDestroyImageView(logicDevice, swapChainImageViews[i], nullptr);
        }

        vkDestroySwapchainKHR(logicDevice, swapChain, nullptr);

        vkEndCommandBuffer(commandBuffer);

        vkDestroyCommandPool(logicDevice, commandPool, nullptr);

        vkDestroyDevice(logicDevice, nullptr);

        vkDestroySurfaceKHR(instance, surface, nullptr);

        vkDestroyInstance(instance, nullptr);

        glfwDestroyWindow(window);

        glfwTerminate();
    }
};

int main() {
    Assignment14 app;

    try {
        app.run();
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}