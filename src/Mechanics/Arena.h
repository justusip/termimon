#pragma once

#include <cstring>
#include <string>
#include <utility>

#include "Pokemon.h"
#include "Renderer.h"
#include "../Misc/Random.h"

using namespace std;

class Arena {
public:
    void onStart();

    void onUpdate(Renderer &r, const int &elapsed);

    void onRender(Renderer &r, const int &elapsed);

    bool checkFatality(Renderer &r);

    void begin(Pokemon self, Pokemon enemy, const function<void(const int status)> &onCompleted);

    static const vector<Pokemon> ENEMIES_PLATEAU;
    static const vector<Pokemon> ENEMIES_FOREST;
    static const vector<Pokemon> ENEMIES_CLIFFS;

    static const Pokemon getRandom(int mapId);

private:
    int turn = 1;

    Pokemon self;
    Pokemon enemy;

    function<void(const int status)> callbackCompleted;
};