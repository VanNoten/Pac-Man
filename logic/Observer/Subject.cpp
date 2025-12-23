#include "Subject.h"

namespace logic {

void Subject::addObserver(const std::shared_ptr<Observer>& observer) { _observers.push_back(observer); }

void Subject::notify(const EventType event) const {
    for (const auto& observer : _observers) {
        observer->update(event);
    }
}

} // namespace logic