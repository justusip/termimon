#pragma once

#include <string>
#include <fstream>

#include "../Libraries/NlohmannJson/json.hpp"

using namespace std;

class SaveManager {
private:

public:
    static nlohmann::json config;

    static void load();

    static void save();

};

