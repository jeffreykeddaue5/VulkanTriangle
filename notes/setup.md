# Setup 

# Vulkan Instance 
-- A vulkan instance is the pathway between the program and the vulkan api
-- First we need to specifiy some details to the vulkan gpu driver 

-- Vulkan Program -> Vulkan SDK Headers/ Loader -> Vulkan.so -> Vulkan GPU driver 

-- SDK (Software development tool kit)
-- contains: headers files (vulkan/vulkan.h)/ libraries (Vulkan loader)/ 
Validation Layers / Debugging tools / Shader tools / Documentation Examples


-- Vulkan loader (libvulkan.so)
a piece of sofware that lives in between your vulkan application and vulkan driver 
-- it is responsible for communicating details about your application to the vulkan driver


-- Vulkan driver -- interprets vulkan commands so that the gpu understands
(Vulkan Capable Graphics driver)

-- For AMD, Drivers are Mesa RADV or AMDVLK 


# platform agnostic : not tied to a specific operating system/hardware/environment; code looks the same on all computers

therefore, vulkan is platform agnostic

-- however, creating a window generally is platform specific because the code to create a window depends on the operating system

-- glfw helps us out with that by dealing with this under the hood and the platform specific details

-- extension is an optinal feature that extends Vulkan's core api/ functionality
    -- think of it as a plugin that can be platform specific (linking the glfw window library with VK_KHR_surface)
    -- necessary so we don't include libraries that are uneeded with the core api that might be platform specific (thus being non platform agnostic)


