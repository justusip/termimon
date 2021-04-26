#pragma once

#include <chrono>
#include <string>
#include <iostream>
#include <fstream>
#include <codecvt>

#include "../Libraries/NlohmannJson/json.hpp"

#include "../Visuals/Colour.h"
#include "../Interface/Inputs.h"
#include "../Interface/Terminal.h"
#include "Renderer.h"
#include "Arena.h"
#include "Pokemon.h"
#include "../Misc/Random.h"
#include "../Data/Maps.h"
#include "../Misc/SaveManager.h"
#include "../Misc/Utils.h"
#include "Inventory.h"

using namespace std;

class Game {
public:
    enum State {
        FREE,
        COMBAT
    } state = State::FREE;

    int curMapId = 0;
    int mapWidth;
    int mapHeight;
    char32_t *mapGlyphs = nullptr;
    Colour *mapFg = nullptr;
    Colour *mapBg = nullptr;

    float defaultProbability = 0.005;
    float appearProbability = defaultProbability;
    int playerX = 5;
    int playerY = 8;

    vector<pair<int, int>> savePoints = {
            {6,  33},
            {25, 10},
            {31, 48},
    };

    void start();

    bool checkLeap(int newX, int newY);

private:
    Renderer rdr;
    Arena ana;
    Inventory inv;

    void loadMap(int id);

    void teleportToHeal();

    void save();

    void load();
};