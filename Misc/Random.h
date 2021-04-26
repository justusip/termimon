#pragma once

#include <chrono>
#include <random>
#include <optional>

class Random {
public:
    static void seed();

    static float rand();

    static float rand(float from, float to);

private:
    static std::optional<std::mt19937> gen;
};