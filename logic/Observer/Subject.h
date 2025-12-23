#ifndef SUBJECT_H
#define SUBJECT_H

#include "./Observer/Observer.h"

#include <memory>
#include <vector>

namespace logic {

class Subject {
public:
    void addObserver(const std::shared_ptr<Observer>& observer);

protected:
    void notify(EventType event) const;

private:
    std::vector<std::shared_ptr<Observer>> _observers;
};

} // namespace logic

#endif // SUBJECT_H
