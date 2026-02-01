cmake_minimum_required(VERSION 3.10)
project(PhysicsEngine2D)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

file(GLOB_RECURSE SOURCES "src/*.cpp")

add_executable(${PROJECT_NAME} ${SOURCES} "include/physics/World.h" "src/World.cpp" "include/physics/shapes/Shape.h" "include/physics/shapes/CircleShape.h" "src/BoxShape.cpp" "include/physics/collision/CollisionManifold.h" "include/physics/collision/CollisionDetection.h" "src/CollisionDetection.cpp" "include/physics/collision/CollisionResolution.h" "src/CollisionResolution.cpp")