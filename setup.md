# Vulkan Triangle — File Structure Overview

This document describes a **minimal but correct Vulkan file setup** specifically for rendering a **single triangle**. The focus is on **clarity**, **lifetime correctness**, and **learning Vulkan fundamentals** without premature engine abstraction.

This is *not* an engine layout — it is a **teaching-first structure** that still follows real Vulkan best practices.

---

## High-Level Directory Layout

```
project-root/
├── CMakeLists.txt
├── README.md
├── shaders/
│   ├── triangle.vert
│   ├── triangle.frag
│   └── compile.sh
├── include/
│   ├── instance.hpp
│   ├── device.hpp
│   ├── swapchain.hpp
│   └── renderer.hpp
├── src/
│   ├── instance.cpp
│   ├── device.cpp
│   ├── swapchain.cpp
│   ├── renderer.cpp
│   └── main.cpp
```

---

## Design Goals (Triangle Scope)

For a Vulkan triangle, the project should:

* Map **1:1 with Vulkan concepts**
* Make object **creation order obvious**
* Make object **destruction order safe**
* Avoid hiding Vulkan behind abstractions

Everything here exists because Vulkan *requires* it — nothing more.

---

## File Responsibilities

### `main.cpp`

**Purpose:** Application entry point

Responsibilities:

* Create window (GLFW / SDL)
* Create Vulkan surface
* Initialize Vulkan objects (top-down)
* Run render loop
* Handle cleanup (implicitly via destructors)

Contains:

* High-level flow only
* No Vulkan boilerplate logic

---

### `instance.hpp / .cpp`

**Purpose:** Vulkan instance + validation setup

Responsibilities:

* Create `VkInstance`
* Enable required extensions
* Enable validation layers (debug builds)
* Create debug messenger

Owns:

* `VkInstance`
* `VkDebugUtilsMessengerEXT`

Notes:

* Does **not** know about devices or swapchains
* Only concerned with Vulkan global state

---

### `device.hpp / .cpp`

**Purpose:** Physical & logical device selection

Responsibilities:

* Pick a suitable `VkPhysicalDevice`
* Create `VkDevice`
* Retrieve graphics & present queues

Owns:

* `VkPhysicalDevice`
* `VkDevice`
* `VkQueue` handles

Inputs:

* Vulkan instance
* Window surface

---

### `swapchain.hpp / .cpp`

**Purpose:** Presentation and framebuffer management

Responsibilities:

* Create `VkSwapchainKHR`
* Create image views
* Create framebuffers
* Handle window resize (recreation)

Owns:

* Swapchain
* Swapchain images
* Image views
* Framebuffers

Notes:

* Tightly coupled to window size
* Recreated when surface changes

---

### `renderer.hpp / .cpp`

**Purpose:** Triangle rendering logic

Responsibilities:

* Create render pass
* Create graphics pipeline
* Allocate command buffers
* Record draw commands
* Submit frames

Owns:

* Pipeline layout
* Graphics pipeline
* Command buffers
* Sync objects (semaphores, fences)

Does **not**:

* Own the device
* Own the swapchain

---

## `shaders/`

Contains shader source files for the triangle.

Typical flow:

```
triangle.vert / triangle.frag
        ↓
     SPIR-V (.spv)
```

Shaders are compiled **offline**, never at runtime.

---

## Build System

### `CMakeLists.txt`

Responsibilities:

* Locate Vulkan SDK
* Configure compiler
* Link windowing library
* (Optional) compile shaders

For a triangle:

* Single executable
* Flat target structure

---

## Object Lifetime Order (Very Important)

Creation order:

```
Instance
  → Surface
    → Device
      → Swapchain
        → Pipeline / Command Buffers
```

Destruction happens in **reverse order**.

This file structure mirrors that order to prevent:

* Use-after-free bugs
* Validation layer errors

---

## Why This Isn’t Overkill (Even for a Triangle)

Vulkan requires:

* Explicit ownership
* Explicit synchronization
* Explicit destruction

This layout:

* Makes Vulkan behavior visible
* Avoids "god files"
* Scales cleanly to the next tutorial step

Once you add **depth**, **uniforms**, or **textures**, this structure stops feeling verbose and starts feeling necessary.

---

## Natural Next Steps After the Triangle

* Add vertex buffers
* Add uniform buffers
* Add depth buffer
* Extract a `Resource` helper

No refactor required — just new files.

---

This layout is intentionally boring.

That’s a compliment in Vulkan.

