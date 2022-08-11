#pragma once

#include <cmath>
#include <string>
#include <vector>

using namespace std;

class Pokemon {
public:
    float getExp() const;

    int getLevel() const;

    void damage(int health);

    float getHealthNormalized();

    void restore();

    u32string name;
    int id;
    enum Gender {
        MALE,
        FEMALE
    } gender = Gender::MALE;

    int xp;
    int maxHealth;
    int curHealth;

    vector<u32string> attacks;
};