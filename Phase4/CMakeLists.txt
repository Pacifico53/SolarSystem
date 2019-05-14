cmake_minimum_required(VERSION 3.13)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Wall -o3 -g -lGLEW")

project(Engine)
set(ENGINE_FILES Engine/engine.cpp Engine/tinyxml2.cpp
        src/Vertex.cpp src/Vertex.h src/Shape.cpp src/Shape.h src/Action.cpp src/Action.h Engine/Parser.cpp Engine/Parser.h src/Group.cpp src/Group.h src/CatmullRom.cpp src/CatmullRom.h src/Light.cpp src/Light.h src/Material.cpp src/Material.h)
find_package(GLUT REQUIRED)
find_package(OpenGL REQUIRED)
find_package(DevIL REQUIRED)
link_libraries(${IL_LIBRARIES} )
include_directories(§{IL_INCLUDE_DIR})

project(Generator)
set(GENERATOR_FILES Generator/generator.cpp Generator/models.cpp Generator/models.h src/Vertex.cpp src/Vertex.h src/Shape.cpp src/Shape.h Generator/bezier.cpp Generator/bezier.h src/Light.cpp src/Light.h src/Material.cpp src/Material.h)

add_executable(generator ${GENERATOR_FILES})
target_link_libraries(generator ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})

add_executable(engine ${ENGINE_FILES})
target_link_libraries(engine ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})
