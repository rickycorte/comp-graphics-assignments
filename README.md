# Computer Graphics Assignments

## Depdencies
This guide works for Ubuntu and gcc 9.3.0.

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

## Compiling

To compile every assignament run:
```
cmake .
cmake --build .
```