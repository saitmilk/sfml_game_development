cmake_minimum_required(VERSION 3.28)
project(AirCombat LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.2
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

add_executable(main)
target_sources(main
PRIVATE
    src/main.cpp
    src/game.cpp

PUBLIC
    FILE_SET myHeaders
    TYPE HEADERS
    BASE_DIRS
        include
    FILES
        include/game.hpp
        include/resource_holder.hpp
)
target_compile_features(main PRIVATE cxx_std_17)
target_link_libraries(main PRIVATE SFML::Graphics)

# Define the source image path
set(GAME_SOURCE "${CMAKE_CURRENT_SOURCE_DIR}/media")

# Define the destination path in the binary directory
set(GAME_DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/bin/media")

# Add a custom command to copy the image after building a specific target
add_custom_command(
    TARGET main # Replace MyExecutable with your actual target name
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory_if_different
            "${GAME_SOURCE}"
            "${GAME_DESTINATION}"
    COMMENT "Copying resource to the binary directory"
)
