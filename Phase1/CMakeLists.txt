cmake_minimum_required(VERSION 3.13)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-Wall -o3 -g")

project(Engine)
set(ENGINE_FILES Engine/engine.cpp Engine/engine.h Engine/tinyxml2.cpp src/vertex.cpp src/vertex.h src/shape.cpp src/shape.h)
find_package(GLUT REQUIRED)
find_package(OpenGL REQUIRED)

project(Generator)
set(GENERATOR_FILES Generator/generator.cpp Generator/generator.h Generator/models.cpp Generator/models.h)

add_executable(generator ${GENERATOR_FILES})

add_executable(engine ${ENGINE_FILES})
target_link_libraries(engine ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})
