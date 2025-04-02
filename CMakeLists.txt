cmake_minimum_required(VERSION 3.28)
project(CMakeSFMLProject LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.0
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

file (GLOB SRC_FILES 
    src/*.cpp
    src/GUI/*.cpp
    src/State/*.cpp
    src/State/AVL/*.cpp
    src/State/Graph/*.cpp
    src/State/Heap/*.cpp
    src/StateMachine/*.cpp
)

add_executable(viz ${SRC_FILES})

target_compile_features(viz PRIVATE cxx_std_17)
target_link_libraries(viz PRIVATE sfml-graphics)
