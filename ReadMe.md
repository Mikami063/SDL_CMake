# Welcome to Cmake Version of SDL_GameEngine

## find a good website explain the ECS(entity_component_system) in detail

https://austinmorlan.com/posts/entity_component_system/#What%20Is%20An%20Ecs?

## general

I'm just tired of poor c++ support on Xcode.

Install SDL2 and SDL2_image to /Library/Frameworks to build

use VSCode plugin CMake Tools

type in command panel >CMake: Configure

and >CMake: Debug

build for MacOS, not sure of other system, good luck get it to work

This repo is for me to follow along the tutorial of a C++ GameEngine series, to ultimately understand basic structure of a GameEngine, not a framework for other people to work on, thus no support, tutorial link in below if you want to also try it

https://www.youtube.com/watch?v=QQzAHcojEKg&list=PLhfAbcv9cehhkG7ZQK0nfIGJC_C-wSLrx&index=1

This readme is a reminder note for myself, I know I will definitely forget how to build my project, 100%

## Build

two build folder: /build for VSCode and /Xbuild for Xcode

```
mkdir build
cd build
cmake ..
```
```
mkdir Xbuild
cd Xbuild
cmake -G Xcode ..
```

Cheers
