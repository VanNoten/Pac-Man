#ifndef STOPWATCH_H
#define STOPWATCH_H
#include <chrono>

namespace logic {

// singleton with raw pointer allowed?
class Stopwatch {
public:
    ~Stopwatch() = default;
    static Stopwatch* getInstance();
    double getDeltaTime();

private:
    Stopwatch();
    static Stopwatch* _instance;
    std::chrono::steady_clock::time_point _lastTime;
};

} // namespace logic

#endif // STOPWATCH_H
