cmake_minimum_required(VERSION 3.10)
project(math_project)

# Set C++ standard to C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Add executable
add_executable(math math.cpp
)

# Optional: Enable compiler warnings
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang|AppleClang")
    target_compile_options(math PRIVATE -Wall -Wextra -Wpedantic)
endif()

# Optional: Set optimization level for Release builds
set(CMAKE_CXX_FLAGS_RELEASE "-O3")