#include "Inputs.h"

#include <unistd.h>
#include <iostream>

//managing user inputs
using namespace std;

struct termios Inputs::initial = {}, Inputs::current = {};
vector<char> Inputs::keydowns = {};

void Inputs::init() {
    tcgetattr(0, &initial);
    current = initial;
    current.c_lflag &= ~ICANON;
    current.c_lflag &= ~ECHO;
    tcsetattr(0, TCSANOW, &current);
}

void Inputs::reset() {
    tcsetattr(0, TCSANOW, &initial);
}

void Inputs::flush() {
    while (Inputs::onUpdate());
}

bool Inputs::onUpdate() {
    keydowns.clear();

    fd_set set;
    FD_ZERO(&set);
    FD_SET(STDIN_FILENO, &set);
    struct timeval interval = {0L, 0L};
    if (!select(1, &set, nullptr, nullptr, &interval))
        return false;

    unsigned char c;
    if (read(STDIN_FILENO, &c, sizeof(c)) < 0)
        return false;

    if (c != '\033') {
        if (c >= 'A' && c <= 'Z')
            c += 'a' - 'A';
        keydowns.push_back(c);
        return true;
    }

    if (read(STDIN_FILENO, &c, sizeof(c)) < 0)
        return false;
    if (read(STDIN_FILENO, &c, sizeof(c)) < 0)
        return false;
    keydowns.push_back(c - 'A' + 1);
    return true;
}

bool Inputs::isKeydown(char key) {
    for (const char &k: keydowns)
        if (key == k)
            return true;
    return false;
}

bool Inputs::isAnyKeydown() {
    return !keydowns.empty();
}
