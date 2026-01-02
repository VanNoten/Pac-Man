#ifndef OBSERVER_H
#define OBSERVER_H

namespace logic {

/**
 * @brief The different type of events.
 */
enum class EventType {
    Move,
    CoinCollected,
    FruitCollected,
    GhostEaten,
    GameOver,
    LevelCleared,
    DirectionChanged,
    FearedModeChanged
};

/**
 * @brief Abstract base class that allows other classes to receive events from subjects.
 *
 * Implements Observer/Subject design pattern.
 */
class Observer {
public:
    virtual ~Observer() = default;

    /**
     * @brief Called when a subject notifies its observers of an event.
     * @param event The type of event that was received.
     */
    virtual void onNotify(EventType event) = 0;
};

} // namespace logic

#endif // OBSERVER_H
