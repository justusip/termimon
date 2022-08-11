#include "SaveManager.h"

//for saving game progress
nlohmann::json SaveManager::config = {
        {
                "lastpoint", {
                                     {"x", 2},
                                     {"y", 7},
                                     {"map_id", 0}
                             }
        },
        {
                "pokemon",   {
                                     {
                                      {"name", "pikachu"},
                                           {"xp", 97},
                                             {"cur_health", 15},
                                             {"max_health", 15}
                                     }
                             }
        }
};

void SaveManager::load() {
    //ifstream f("../Sprites/" + string("owo") + ".dat", std::ios::binary);
    //                f.read((char *) &c, 4);
    ifstream f("./save.json");
    if (f.fail())
        return;
    config = nlohmann::json::parse(f);
}

void SaveManager::save() {
    ofstream f("./save.json");
    f << config.dump(4);
}
