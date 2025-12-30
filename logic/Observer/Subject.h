#ifndef SUBJECT_H
#define SUBJECT_H

#include "./Observer/Observer.h"

#include <memory>
#include <vector>

namespace logic {

/**
 * @brief Class that allows other classes to send out events to the attached observers.
 *
 * Implements Observer/Subject design pattern.
 */
class Subject {
public:
    virtual ~Subject() = default;

    /**
     * @brief Adds an observer to the subject.
     * @param observer Observer to add.
     */
    void addObserver(const std::shared_ptr<Observer>& observer);

protected:
    /**
     * @brief Sends an event to all attached observers.
     * @param event Event to send out.
     */
    void notify(EventType event) const;

private:
    std::vector<std::shared_ptr<Observer>> _observers;
};

} // namespace logic

#endif // SUBJECT_H
