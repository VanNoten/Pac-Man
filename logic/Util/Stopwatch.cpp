#include "Stopwatch.h"

namespace logic {

Stopwatch& Stopwatch::getInstance() {
    static Stopwatch instance;
    return instance;
}

double Stopwatch::getDeltaTime() {
    const std::chrono::steady_clock::time_point currentTime = std::chrono::steady_clock::now();
    const double deltaTime = std::chrono::duration<double>(currentTime - _lastTime).count();
    _lastTime = currentTime;
    return std::min(deltaTime, 0.1);
}

Stopwatch::Stopwatch() { _lastTime = std::chrono::steady_clock::now(); }

} // namespace logic