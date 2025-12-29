cmake_minimum_required(VERSION 3.28)
project(PacMan)

set(CMAKE_CXX_STANDARD 20)

#LOGIC
file(GLOB_RECURSE LOGIC_SOURCES
        CONFIGURE_DEPENDS
        ${CMAKE_CURRENT_SOURCE_DIR}/logic/*.cpp
)

add_library(pacman_logic STATIC
        ${LOGIC_SOURCES}
)

target_include_directories(pacman_logic
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/logic
)

#APPLICATION
find_package(SFML 2.6.1 COMPONENTS system window graphics REQUIRED)

file(GLOB_RECURSE APP_SOURCES
        CONFIGURE_DEPENDS
        ${CMAKE_CURRENT_SOURCE_DIR}/application/*.cpp
)

add_executable(pacman_app
        ${APP_SOURCES}
)

target_include_directories(pacman_app
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/application
        ${CMAKE_CURRENT_SOURCE_DIR}/logic
)

target_link_libraries(pacman_app
        PRIVATE
        pacman_logic
        sfml-system
        sfml-window
        sfml-graphics
)

add_custom_target(copy_assets
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/application/Resources/Assets ${PROJECT_BINARY_DIR}/Assets
)
add_dependencies(pacman_app copy_assets)