#ifndef RANDOM_H
#define RANDOM_H
#include <random>

namespace logic::util {

/**
 * @brief Singleton providing random number generation using Mersenne Twister.
 *
 * Used in AI pathfinding:
 *  - Locked ghost: 50% chance to change direction at intersection
 *  - If multiple directions are possible choose a random one
 *
 * Implements Scott Meyers' Singleton design pattern.
 */
class Random {
public:
    /**
     * @brief Returns the singleton instance.
     */
    static Random& getInstance();

    Random(const Random&) = delete;
    Random(Random&&) = delete;
    Random& operator=(Random&&) = delete;
    Random& operator=(const Random&) = delete;

    /**
     * @brief Generates a random double between 0.0 and 1.0.
     */
    [[nodiscard]] double randomDouble();

    /**
     * @brief Returns true with probability p and false with probability 1-p.
     * @param probability Value between 0.0 and 1.0.
     */
    [[nodiscard]] bool chance(double probability);

    /**
     * @brief Returns a random index of vector
     * @param n Size of vector
     */
    [[nodiscard]] int randomIndex(int n);

private:
    Random();
    ~Random() = default;

    std::random_device _rd;
    std::mt19937 _generator;
};

} // namespace logic::util

#endif // RANDOM_H
