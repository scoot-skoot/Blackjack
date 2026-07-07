cmake_minimum_required(VERSION 3.16)
project(Blackjack VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(BLACKJACK_BUILD_SFML "Build with SFML graphical UI" ON)

set(BLACKJACK_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Blackjack)

add_executable(Blackjack
    ${BLACKJACK_DIR}/main.cpp
    ${BLACKJACK_DIR}/core/hand.cpp
    ${BLACKJACK_DIR}/core/game_engine.cpp
    ${BLACKJACK_DIR}/views/ConsoleView.cpp
)

target_include_directories(Blackjack PRIVATE ${BLACKJACK_DIR})

if(BLACKJACK_BUILD_SFML)
    find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)
    target_sources(Blackjack PRIVATE ${BLACKJACK_DIR}/views/SfmlView.cpp)
    target_link_libraries(Blackjack PRIVATE sfml-graphics sfml-window sfml-system)
    target_compile_definitions(Blackjack PRIVATE BLACKJACK_HAS_SFML=1)
endif()

if(MSVC)
    target_compile_options(Blackjack PRIVATE /W4)
else()
    target_compile_options(Blackjack PRIVATE -Wall -Wextra -Wpedantic)
endif()
