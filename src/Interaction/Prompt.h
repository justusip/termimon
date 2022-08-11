#pragma once

#include <vector>
#include <codecvt>
#include <string>
#include <optional>
#include <functional>

using namespace std;

class Prompt {
public:
    u32string question;
    vector<u32string> answers;
    function<void(const int)> callbackDecided;
    int choice;
};
