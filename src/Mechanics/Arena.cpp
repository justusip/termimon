#include "Arena.h"

//character information
const vector<Pokemon> Arena::ENEMIES_PLATEAU = {
        {
                U"Nidoran",
                7,
                Pokemon::Gender::FEMALE,
                87,
                16,
                16,
                {
                        {
                                U"Tackle",
                                U"Rage",
                                U"Bide",
                                U"Shock Wave"
                        }
                }
        },
        {
                U"Caterpie",
                0,
                Pokemon::Gender::MALE,
                47,
                16,
                16,
                {
                        {
                                U"Tackle",
                                U"String shot",
                                U"Bug Bite",
                                U"Snore"
                        }
                }
        },
        {
                U"Oddish",
                8,
                Pokemon::Gender::MALE,
                68,
                16,
                16,
                {
                        {
                                U"Absorb",
                                U"Growth",
                                U"Sweet Scent"
                        }
                }
        },
        {
                U"Weedle",
                12,
                Pokemon::Gender::MALE,
                96,
                16,
                16,
                {
                        {
                                U"Poison Sting",
                        }
                }
        }
};
const vector<Pokemon> Arena::ENEMIES_FOREST = {
        {
                U"Sandshrew",
                10,
                Pokemon::Gender::FEMALE,
                163,
                16,
                16,
                {
                        {
                                U"Gyro Ball	Steel",
                                U"Swords Dance",
                                U"Sandstorm	Rock",
                                U"Earthquake"
                        }
                }
        },
        {
                U"Mankey",
                6,
                Pokemon::Gender::MALE,
                193,
                16,
                16,
                {
                        {
                                U"U-turn",
                                U"Screech",
                                U"Thrash",
                                U"Outrage"
                        }
                }
        },
        {
                U"Oddish",
                8,
                Pokemon::Gender::MALE,
                184,
                16,
                16,
                {
                        {
                                U"Absorb",
                                U"Growth",
                                U"Sweet Scent"
                        }
                }
        },
        {
                U"Magikarp",
                5,
                Pokemon::Gender::MALE,
                174,
                16,
                16,
                {
                        {
                                U"Splash",
                                U"Tackle",
                                U"Flail"
                        }
                }
        }
};
const vector<Pokemon> Arena::ENEMIES_CLIFFS = {
        {
                U"Dragonair",
                2,
                Pokemon::Gender::FEMALE,
                294,
                16,
                16,
                {
                        {
                                U"Rain Dance",
                                U"Dragon Dance",
                                U"Outrage Dragon",
                                U"Hyper Beam"
                        }
                }
        },
        {
                U"Eevee",
                4,
                Pokemon::Gender::MALE,
                299,
                16,
                16,
                {
                        {
                                U"Take Down",
                                U"Charm	Fairy",
                                U"Double-Edge",
                                U"Last Resort"
                        }
                }
        },
        {
                U"Squirtle",
                11,
                Pokemon::Gender::MALE,
                249,
                16,
                16,
                {
                        {
                                U"Shell Smash",
                                U"Iron Defense",
                                U"Hydro Pump",
                                U"Skull Bash",
                        }
                }
        },
        {
                U"Dratini",
                3,
                Pokemon::Gender::MALE,
                295,
                16,
                16,
                {
                        {
                                U"Hyper Beam",
                                U"Thunder Wave",
                                U"Slam",
                                U"Dragon Dance",
                        }
                }
        }
};

void Arena::onStart() {
}

void Arena::onUpdate(Renderer &r, const int &elapsed) {
    if (turn == 1) {
        r.ask(U"What will Pikachu do?", {
                U"Fight",
                U"Bag",
                U"Pokémon",
                U"Escape"
        }, [&](const int choice) {
            switch (choice) {
                case 0:
                    r.ask(U"What move will you use?",
                          self.attacks,
                          [&](const int choice) {
                              enemy.damage(floor(5 + Random::rand(5, 10)));
                              r.tell(self.name + U" used " + self.attacks[choice] + U"! It is extremely effective!",
                                     true,
                                     [&]() {
                                         if (!checkFatality(r))
                                             turn = 2;
                                     });
                          });
                    break;
                case 1:
                    r.tell(U"Your bag is empty.",
                           true,
                           [&]() {
                               turn = 1;
                           });
                    break;
                case 2:
                    r.tell(U"You have no other Pokemon",
                           true,
                           [&]() {
                               turn = 1;
                           });
                    break;
                case 3:
                    r.ask(U"Are you sure to escape?",
                          {U"Yes", U"No"},
                          [&](const int choice) {
                              if (choice == 0)
                                  callbackCompleted(2);
                              else
                                  turn = 1;
                          });
                    break;

            }
        });
        turn = 0;
    } else if (turn == 2) {
        int attack = floor(Random::rand() * enemy.attacks.size());
        self.damage(floor(5 + Random::rand(5, 10)));
        std::vector<u32string> adjective = {
                U"kinda",
                U"quite",
                U"extremely"
        };
        r.tell(enemy.name + U" used " + enemy.attacks[attack] + U"! It is " +
               adjective[Random::rand() * adjective.size()] + U" effective!",
               true,
               [&]() {
                   if (!checkFatality(r))
                       turn = 1;
               });
        turn = 0;
    }
}

void Arena::onRender(Renderer &r, const int &elapsed) {
    int width, height;
    Terminal::getCanvasSize(width, height);

    for (int j = 0; j < height; j++) {
        int v = 0xFF - (100.f * j / height);
        for (int i = 0; i < width; i++)
            r.canvasBg[j * width + i] = Colour(v, v, v);
    }

    r.drawSprite(-16, 4, self.id, true);
    r.drawSprite(width / 2 + 4, 0, enemy.id, false);

    r.drawStatus(width - 40, height - 8, self.name, self.getHealthNormalized(), self.getLevel(), self.getExp(),
                 self.gender);
    r.drawStatus(0, 0, enemy.name, enemy.getHealthNormalized(), enemy.getLevel(), enemy.getExp(), enemy.gender);
}

void Arena::begin(Pokemon self, Pokemon enemy, const function<void(const int)> &onCompleted) {
    this->self = move(self);
    this->enemy = move(enemy);
    callbackCompleted = onCompleted;
    turn = 1;
}

bool Arena::checkFatality(Renderer &r) {
    if (self.curHealth > 0 && enemy.curHealth > 0)
        return false;
    bool won = self.curHealth > 0;
    Pokemon &fainted = won ? enemy : self;

    r.tell(fainted.name + U" fainted!", true, [&, won]() {
        if (won) {
            int xp = floor(Random::rand() * 30) + 20;
            self.xp += xp;
            r.tell(to_string(xp) + " xp is awarded!", true, [&]() {
                callbackCompleted(1);
            });
        } else {
            callbackCompleted(0);
        }
    });
    return true;
}

const Pokemon Arena::getRandom(int mapId) {
    switch (mapId) {
        case 0:
            return ENEMIES_PLATEAU[Random::rand() * ENEMIES_PLATEAU.size()];
        case 1:
            return ENEMIES_FOREST[Random::rand() * ENEMIES_FOREST.size()];
        case 2:
            return ENEMIES_CLIFFS[Random::rand() * ENEMIES_CLIFFS.size()];
    }
}
