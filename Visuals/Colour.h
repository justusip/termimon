#pragma once

#include <cstdint>

struct Colour {
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;

    Colour() : r(0), g(0), b(0), a(0) {}

    Colour(uint8_t r, uint8_t g, uint8_t b) : r(r), g(g), b(b), a(255) {}

    Colour(uint8_t r, uint8_t g, uint8_t b, uint8_t a) : r(r), g(g), b(b), a(a) {}

    Colour &operator=(const Colour &other) {
        r = other.r;
        g = other.g;
        b = other.b;
        a = other.a;
        return *this;
    }

    bool operator==(const Colour &other) const {
        return r == other.r && g == other.g && b == other.b && a == other.a;
    }

    bool operator!=(const Colour &other) const {
        return !(*this == other);
    }
};