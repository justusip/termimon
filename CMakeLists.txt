cmake_minimum_required(VERSION 3.16.3)
project(Pokemon)

set(CMAKE_CXX_STANDARD 20)
add_executable(termimon
        src/main.cpp
        src/Interface/Inputs.cpp
        src/Interface/Terminal.cpp
        src/Interaction/Prompt.cpp
        src/Interaction/Dialogue.cpp
        src/Mechanics/Arena.cpp
        src/Mechanics/Game.cpp
        src/Mechanics/Pokemon.cpp
        src/Mechanics/Renderer.cpp
        src/Misc/Random.cpp
        src/Misc/Utils.cpp
        src/Visuals/Colour.cpp
        src/Misc/SaveManager.cpp
        src/Mechanics/Inventory.cpp
        )