#ifndef STOPWATCH_H
#define STOPWATCH_H
#include <chrono>

namespace logic::util {

/**
 * @brief Singleton providing a method to get deltaTime
 *
 * Used to ensure game logic runs at the same speed regardless of speed of the device and used to ensure animations last
 * a fixed amount of time.
 *
 * Implements Scott Meyers' Singleton design pattern.
 */
class Stopwatch {
public:
    /**
     * @brief Returns the singleton instance.
     */
    static Stopwatch& getInstance();

    Stopwatch(const Stopwatch&) = delete;
    Stopwatch(Stopwatch&&) = delete;
    Stopwatch& operator=(Stopwatch&&) = delete;
    Stopwatch& operator=(const Stopwatch&) = delete;

    /**
     * @brief Returns time since last getDeltaTime() call.
     */
    double getDeltaTime();

private:
    Stopwatch();
    ~Stopwatch() = default;

    std::chrono::steady_clock::time_point _lastTime;
};

} // namespace logic::util

#endif // STOPWATCH_H
