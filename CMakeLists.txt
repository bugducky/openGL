cmake_minimum_required(VERSION 3.15)
project(Exp)

set(CMAKE_CXX_STANDARD 17)

add_executable(Exp src/main.cpp src/glad.c include/learnopengl/shader_s.h src/model.cpp src/world.cpp)

INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/include)
link_directories(${PROJECT_SOURCE_DIR}/lib)

configure_file(configuration/root_directory.h.in configuration/root_directory.h)
include_directories(${CMAKE_BINARY_DIR}/configuration)

#add_library(STB_IMAGE "src/stb_image.cpp")
##set(LIBS ${LIBS} STB_IMAGE)

target_link_libraries(Exp -lopengl32 ${PROJECT_SOURCE_DIR}/lib/glfw3.dll ${PROJECT_SOURCE_DIR}/lib/libassimp.dll)