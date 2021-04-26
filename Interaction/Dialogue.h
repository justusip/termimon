#pragma once

#include <codecvt>
#include <string>
#include <optional>
#include <functional>

using namespace std;

class Dialogue {
public:
    optional<u32string> msg;
    int cursor = 0;
    int prevUpdate = 0;
    function<void()> callback;

    bool animationCompleted();
};