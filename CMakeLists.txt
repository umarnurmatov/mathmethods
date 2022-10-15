cmake_minimum_required(VERSION 3.12)

set(CMAKE_TOOLCHAIN_FILE /home/umarnurmatov/vcpkg/scripts/buildsystems/vcpkg.cmake
  CACHE STRING "Vcpkg toolchain file")

project(mathmeth VERSION 0.1.0)

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

set(RESOURCE_PATH "${PROJECT_SOURCE_DIR}/resourses/")

# Find SFML shared libraries
find_package(SFML COMPONENTS system window graphics CONFIG REQUIRED)
find_package(ImGui-SFML CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)
find_package(GSL REQUIRED)

add_executable(mathmeth 
  src/mathmeth.cpp
  src/polynomial_regression.cpp
  src/interface.cpp
  src/plotter.cpp)

target_compile_definitions(mathmeth PRIVATE PROJECT_SOURCE_DIR="${PROJECT_SOURCE_DIR}")
target_compile_definitions(mathmeth PRIVATE RESOURSE_PATH="${PROJECT_SOURCE_DIR}/resourses/}")


# Set include directory search paths
target_include_directories(mathmeth
    PRIVATE
    "${PROJECT_BINARY_DIR}"
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
  )
  

target_link_libraries(mathmeth 
    PRIVATE ImGui-SFML::ImGui-SFML
    PRIVATE imgui::imgui
    PRIVATE sfml-system sfml-graphics sfml-window
    PRIVATE GSL::gsl GSL::gslcblas)