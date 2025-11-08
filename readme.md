# **OggaLib**<br>

> ## **How To Use**<br>
> To add the library to your git repository run this in project root:
> ```
> git submodule add https://github.com/0gga/OggaLib.git extern/ogga
> git submodule update --init --recursive --remote --merge
> ```  
> To later pull the latest commit & initialize any submodules that have yet to be cloned you can run the last line.


> ## **CMake**<br>
> To use this library in your CMake project simply add the following to your CMakeLists.txt.
> ```.cmake
> include_directories(${CMAKE_SOURCE_DIR}/extern/ogga/include).
> ```