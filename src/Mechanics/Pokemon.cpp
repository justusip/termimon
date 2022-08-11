#include "Pokemon.h"

//for calculating pokemon XP, level, damage and health
float Pokemon::getExp() const {
    return fmod((float) xp, 10.f) / 10.f;
}

int Pokemon::getLevel() const {
    return xp / 10;
}

void Pokemon::damage(int health) {
    curHealth -= health;
    if (curHealth < 0)
        curHealth = 0;
}

float Pokemon::getHealthNormalized() {
    return (float) curHealth / (float) maxHealth;
}

void Pokemon::restore() {
    curHealth = maxHealth;
}
