#include "Stopwatch.h"

namespace logic {

Stopwatch* Stopwatch::_instance = nullptr;

Stopwatch* Stopwatch::getInstance() {
    if (!_instance)
        _instance = new Stopwatch();
    return _instance;
}

double Stopwatch::getDeltaTime() {
    const std::chrono::steady_clock::time_point currentTime = std::chrono::steady_clock::now();
    const double deltaTime = std::chrono::duration<double>(currentTime - _lastTime).count();
    _lastTime = currentTime;
    return deltaTime;
}

Stopwatch::Stopwatch() { _lastTime = std::chrono::steady_clock::now(); }

} // namespace logic