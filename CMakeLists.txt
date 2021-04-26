cmake_minimum_required(VERSION 3.16.3)
project(Pokemon)

set(CMAKE_CXX_STANDARD 20)
add_executable(rpg
        main.cpp
        Interface/Inputs.cpp
        Interface/Terminal.cpp
        Interaction/Prompt.cpp
        Interaction/Dialogue.cpp
        Mechanics/Arena.cpp
        Mechanics/Game.cpp
        Mechanics/Pokemon.cpp
        Mechanics/Renderer.cpp
        Misc/Random.cpp
        Misc/Utils.cpp
        Visuals/Colour.cpp
        Misc/SaveManager.cpp
        Mechanics/Inventory.cpp
        )