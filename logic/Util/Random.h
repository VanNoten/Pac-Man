#ifndef RANDOM_H
#define RANDOM_H
#include <random>

namespace logic {

// singleton with raw pointer allowed?
class Random {
public:
    ~Random() = default;
    static Random* getInstance();
    [[nodiscard]] double randomDouble();
    [[nodiscard]] bool chance(double probability);
    [[nodiscard]] int randomIndex(int n);

private:
    Random();
    static Random* _instance;
    std::random_device _rd;
    std::mt19937 _generator;
};

} // namespace logic

#endif // RANDOM_H
