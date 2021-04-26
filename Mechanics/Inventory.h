#pragma once

#include <vector>

#include "Pokemon.h"

using namespace std;

class Inventory {
public:
    vector<Pokemon> pokemons = {
            {
                    U"Pikachu",
                    9,
                    Pokemon::Gender::MALE,
                    92,
                    15,
                    15,
                    {
                            {
                                    U"Thunderbolt",
                                    U"Thunder Shock",
                                    U"Scratch",
                                    U"Thunder Wave"
                            }
                    }
            }
    };

    Pokemon &getPrimary() {
        return pokemons[0];
    }

};

