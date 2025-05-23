# Voxel Engine

A really basic voxel engine i wanted to make to get better at cpp and understand 3d graphics. not much else to say.

## Features

- rendering
- freeroam camera
- TODO chunks and worldgen

## Dependencies
- [vcpkg](https://github.com/microsoft/vcpkg)
- C++ compiler with C++17 support or higher
- [CMake](https://cmake.org/)

## Instructions
```bash
git clone https://github.com/suboptimalcx/voxel-engine.git

$env:VCPKG_ROOT="C:\path\to\vcpkg"
$env:PATH="$env:VCPKG_ROOT;$env:PATH"

# you could also type in: "vcpkg integrate install" and use the -DCMAKE_TOOLCHAIN_FILE while using CMake :)
```
then just build it using cmake

## cursed demo gif
![Voxel Engine Demo](assets/gif/ababab.gif)
---

## Extra
I've learned the basics of opengl from https://learnopengl.com/ and i'd recommend it to anyone that wants to learn about 3dgraphics :))

also this project is using [stb_image.h](https://github.com/nothings/stb/blob/master/stb_image.h) to load the images 

bird img from [unsplash](https://unsplash.com/photos/gray-pelican-on-green-grass-during-daytime-mIwTJNB4x80?utm_content=creditShareLink&utm_medium=referral&utm_source=unsplash)
