#include "Random.h"

namespace logic {

Random* Random::_instance = nullptr;

Random* Random::getInstance() {
    if (!_instance) {
        _instance = new Random();
    }
    return _instance;
}

double Random::randomDouble() {
    std::uniform_real_distribution<double> distribution(0.0, 1.0);
    return distribution(_generator);
}

Random::Random() : _generator(_rd()) {}

} // namespace logic