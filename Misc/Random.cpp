#include "Random.h"

std::optional<std::mt19937>Random::gen = {};


//generate random numbers
void Random::seed() {
    std::random_device rd;
    std::mt19937::result_type seed = rd() ^(
            (std::mt19937::result_type)
                    std::chrono::duration_cast<std::chrono::seconds>(
                            std::chrono::system_clock::now().time_since_epoch()
                    ).count() +
            (std::mt19937::result_type)
                    std::chrono::duration_cast<std::chrono::microseconds>(
                            std::chrono::high_resolution_clock::now().time_since_epoch()
                    ).count());
    gen = std::mt19937(seed);
}

float Random::rand() {
    std::uniform_real_distribution<> dis(0, 1);
    return dis(*gen);
}

float Random::rand(float from, float to) {
    std::uniform_real_distribution<> dis(from, to);
    return dis(*gen);
}
