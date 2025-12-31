#include "Random.h"

namespace logic::util {

Random& Random::getInstance() {
    static Random instance;
    return instance;
}

double Random::randomDouble() {
    std::uniform_real_distribution<double> distribution(0.0, 1.0);
    return distribution(_generator);
}

bool Random::chance(const double probability) { return randomDouble() < probability; }

int Random::randomIndex(const int n) {
    std::uniform_int_distribution<int> distribution(0, n - 1);
    return distribution(_generator);
}

Random::Random() : _generator(_rd()) {}

} // namespace logic::util