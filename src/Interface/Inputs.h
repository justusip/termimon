#pragma once

#include <cstdio>
#include <termios.h>
#include <vector>

using namespace std;

class Inputs {
private:
    static struct termios initial, current;
    static vector<char> keydowns;

public:
    static void init();

    static void reset();

    static void flush();

    static bool onUpdate();

    static bool isKeydown(char key);

    static bool isAnyKeydown();
};