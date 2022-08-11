#include "Game.h"

//for loading and navigating around the map
using namespace std;

void Game::start() {
    Random::seed();
    Inputs::flush();

    load();

    const auto start = chrono::steady_clock::now();
    while (true) {
        Inputs::onUpdate();

        const auto now = chrono::steady_clock::now();
        const auto elapsed = chrono::duration_cast<chrono::milliseconds>(now - start).count();

        rdr.clearBuf();

        switch (state) {
            case State::FREE: {
                int axisX = 0, axisY = 0;
                if (rdr.ready()) {
                    if (Inputs::isKeydown('w'))
                        axisY -= 1;
                    if (Inputs::isKeydown('a'))
                        axisX -= 1;
                    if (Inputs::isKeydown('s'))
                        axisY += 1;
                    if (Inputs::isKeydown('d'))
                        axisX += 1;
                }
                if (axisX != 0 || axisY != 0) {
                    int newX = playerX + axisX;
                    int newY = playerY + axisY;
                    if (checkLeap(newX, newY))
                        break;
                    if (mapGlyphs[newY * mapWidth + newX] == 0
                        && newX >= 0 && newX < mapWidth
                        && newY >= 0 && newY < mapHeight) {
                        playerX = newX;
                        playerY = newY;
                        appearProbability *= 1.1;
                        appearProbability = clamp(appearProbability, 0.0f, 0.4f);
                        if (Random::rand() < appearProbability) {
                            ana.begin(inv.getPrimary(),
                                      Arena::getRandom(curMapId),
                                      [&](const int status) {
                                          state = State::FREE;
                                          appearProbability = defaultProbability;
                                          if (status == 0)
                                              teleportToHeal();
                                          else
                                              inv.getPrimary().xp += 10;
                                      });
                            state = State::COMBAT;
                        }
                    }
                }

                if (rdr.ready() && Inputs::isKeydown(' ')) {
                    array<pair<int, int>, 4> offsets = {
                            {
                                    {0, 1},
                                    {1, 0},
                                    {-1, 0},
                                    {0, -1}
                            }
                    };
                    for (const auto &o : offsets) {
                        int x = playerX + o.first;
                        int y = playerY + o.second;
                        if (savePoints[curMapId].first == x && savePoints[curMapId].second == y) {
                            rdr.ask(U"Would you like to restore the health of your Pokemon and save the game?",
                                    {U"Yes", U"No"},
                                    [&](const int &response) {
                                        if (response != 0)
                                            return;
                                        for (auto &p : inv.pokemons)
                                            p.restore();
                                        save();
                                        rdr.tell(U"Game saved. Your Pokemon have restored their health.", true,
                                                 []() {});
                                    });
                        }
                        if (curMapId == 2 && x == 43 && y == 73) {
                            rdr.ask(U"Are you ready to fight the boss?",
                                    {U"Yes", U"No"},
                                    [&](const int &response) {
                                        if (response != 0)
                                            return;
                                        ana.begin(inv.getPrimary(),
                                                  {
                                                          U"Lord Charmander",
                                                          1,
                                                          Pokemon::Gender::MALE,
                                                          9999,
                                                          200,
                                                          200,
                                                          {
                                                                  {
                                                                          U"Ember",
                                                                          U"Smokescreen",
                                                                          U"Dragon Breath",
                                                                          U"Flare Blitz"
                                                                  }
                                                          }
                                                  },
                                                  [&](const int status) {
                                                      state = State::FREE;
                                                      if (status == 0)
                                                          teleportToHeal();
                                                  });
                                        state = State::COMBAT;
                                    });
                        }
                    }
                }
                break;
            }
            case State::COMBAT: {
                ana.onUpdate(rdr, elapsed);
                break;
            }
        }

        int width, height;
        Terminal::getCanvasSize(width, height);

        switch (state) {
            case Game::State::FREE: {
                rdr.drawScene(mapWidth, mapHeight, mapGlyphs, mapFg, mapBg, playerX, playerY);
                break;
            }
            case Game::State::COMBAT: {
                ana.onRender(rdr, elapsed);
                break;
            }
        }

        rdr.onUpdate(elapsed);
//        rdr.debug(to_string(playerX) + " " + to_string(playerY));
        rdr.onRender(elapsed);
    }

}

void Game::loadMap(int id) {
    curMapId = id;
    int cursor = 0;
    for (int i = 0; i < id; i++)
        cursor += (*(int32_t *) &MAPS[cursor]) * (*(int32_t *) &MAPS[cursor + 4]) * 12 + 8;
    memcpy(&mapWidth, &MAPS[cursor], 4);
    memcpy(&mapHeight, &MAPS[cursor + 4], 4);

    delete mapGlyphs;
    mapGlyphs = new char32_t[mapWidth * mapHeight];

    delete mapFg;
    mapFg = new Colour[mapWidth * mapHeight];

    delete mapBg;
    mapBg = new Colour[mapWidth * mapHeight];

    for (int j = 0; j < mapHeight; j++) {
        for (int i = 0; i < mapWidth; i++) {
            int offset = j * mapWidth + i;
            //TODO flipped diagonally
            memcpy(&mapGlyphs[offset], &MAPS[cursor + 8 + (i * mapHeight + j) * 12 + 0], 4);
            memcpy(&mapFg[offset], &MAPS[cursor + 8 + (i * mapHeight + j) * 12 + 4], 4);
            memcpy(&mapBg[offset], &MAPS[cursor + 8 + (i * mapHeight + j) * 12 + 8], 4);
//            mapFg[offset] = *(uint32_t *) &MAPS[cursor + 8 + (inv * mapHeight + j) * 12 + 4];
//            mapBg[offset] = *(uint32_t *) &MAPS[cursor + 8 + (inv * mapHeight + j) * 12 + 8];
        }
    }
}

bool Game::checkLeap(int newX, int newY) {
    switch (curMapId) {
        case 0:
            if (newY == mapHeight) {
                loadMap(1);
                playerX = 8;
                playerY = 0;
                return true;
            }
            break;
        case 1:
            if (newY == -1) {
                loadMap(0);
                playerX = 18;
                playerY = mapHeight - 1;
            } else if (newY == mapHeight) {
                loadMap(2);
                playerX = 43;
                playerY = 0;
                return true;
            }
            break;
        case 2:
            if (newY == -1) {
                loadMap(1);
                playerX = 32;
                playerY = mapHeight - 1;
                return true;
            }
            break;
    }
    return false;
}

void Game::teleportToHeal() {
    rdr.tell(U"Your Pokemon have all restored their health. Be more careful next time!",
             true, [&]() {});
    playerX = savePoints[curMapId].first;
    playerY = savePoints[curMapId].second;
    for (auto &p : inv.pokemons)
        p.restore();
    save();
}

void Game::load() {
    SaveManager::load();
    playerX = SaveManager::config["lastpoint"]["x"];
    playerY = SaveManager::config["lastpoint"]["y"];
    loadMap(SaveManager::config["lastpoint"]["map_id"]);

    Pokemon &primary = inv.getPrimary();
    primary.name = Utils::toU32(SaveManager::config["pokemon"][0]["name"]);
    primary.xp = SaveManager::config["pokemon"][0]["xp"];
    primary.curHealth = SaveManager::config["pokemon"][0]["cur_health"];
    primary.maxHealth = SaveManager::config["pokemon"][0]["max_health"];
}

void Game::save() {
    SaveManager::config["lastpoint"]["x"] = playerX;
    SaveManager::config["lastpoint"]["y"] = playerY;
    SaveManager::config["lastpoint"]["map_id"] = curMapId;

    Pokemon &primary = inv.getPrimary();
    SaveManager::config["pokemon"][0]["name"] = Utils::toU8(primary.name);
    SaveManager::config["pokemon"][0]["xp"] = primary.xp;
    SaveManager::config["pokemon"][0]["cur_health"] = primary.curHealth;
    SaveManager::config["pokemon"][0]["max_health"] = primary.maxHealth;
    SaveManager::save();
}