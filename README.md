# Computer Graphics Assignments

## Getting started

Both guides require cmake installed and a working C++17 compiler.
### Linux (ubuntu)

Install vulkan:
```
sudo apt install vulkan-tools libvulkan-dev vulkan-validationlayers-dev spirv-tools
```

Install GLFW
```
sudo apt install libglfw3-dev
```

Install GLM
```
sudo apt install libglm-dev
```

Other dependencies may be provided in headers folder inside assignment folder.

### Windows 

Install vulkan following the site guide. The edit the cmake's in AXX folders to match your path (the version may change)

Download both GLFW (pre built libraries are present so you don't have to build yoursef) and GLM from their sites.

Create `c:/libs` folder and inside it create two folders: `glfw` and `glm`. 

Copy all the content of GLFW library inside `glfw`. Make sure to copy the right compiler version deping on your visual studio version.

Copy all the file of GLM library in `glm` folder.
## Compiling

To compile every assignament run:
```
cmake .
cmake --build .
```

## Running assignments

To run assignaments you must reside in side `AXX` folder or it won't find required folders and crash.