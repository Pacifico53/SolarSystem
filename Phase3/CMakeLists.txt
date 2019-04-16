cmake_minimum_required(VERSION 3.13)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Wall -o3 -g")

project(Engine)
set(ENGINE_FILES Engine/engine.cpp Engine/tinyxml2.cpp
        src/Vertex.cpp src/Vertex.h src/Shape.cpp src/Shape.h src/Action.cpp src/Action.h Engine/Parser.cpp Engine/Parser.h src/Group.cpp src/Group.h src/CatmullRom.cpp src/CatmullRom.h)
find_package(GLUT REQUIRED)
find_package(OpenGL REQUIRED)

project(Generator)
set(GENERATOR_FILES Generator/generator.cpp Generator/models.cpp Generator/models.h src/Vertex.cpp src/Vertex.h src/Shape.cpp src/Shape.h Generator/bezier.cpp Generator/bezier.h)

add_executable(generator ${GENERATOR_FILES})

add_executable(engine ${ENGINE_FILES})
target_link_libraries(engine ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})
