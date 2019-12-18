cmake_minimum_required(VERSION 3.15)
project(Exp)

set(CMAKE_CXX_STANDARD 17)

add_executable(Exp src/main.cpp src/glad.c)

INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/include)
link_directories(${PROJECT_SOURCE_DIR}/lib)

target_link_libraries(Exp -lopengl32 ${PROJECT_SOURCE_DIR}/lib/glfw3.dll )