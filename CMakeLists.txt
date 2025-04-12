cmake_minimum_required(VERSION 3.28)
project(data-structures-visualizer LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.0
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

file(GLOB SRC_FILES 
    src/*.cpp
    src/GUI/*.cpp
    src/State/*.cpp
    src/State/AVL/*.cpp
    src/State/Graph/*.cpp
    src/State/Heap/*.cpp
    src/State/SinglyLinkedList/*.cpp
    src/State/Tree234/*.cpp
    src/State/Trie/*.cpp
    src/StateMachine/*.cpp
)

add_executable(main ${SRC_FILES})

target_compile_features(main PRIVATE cxx_std_17)
target_link_libraries(main PRIVATE sfml-graphics)

target_include_directories(main PRIVATE
    header
    header/GUI
    header/State
    header/State/AVL
    header/State/Graph
    header/State/Heap
    header/State/SinglyLinkedList/
    header/State/Tree234/
    header/State/Trie/
    header/StateMachine
)

add_custom_command(TARGET main POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_SOURCE_DIR}/assets
            $<TARGET_FILE_DIR:main>/assets
)