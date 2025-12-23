#ifndef SCORE_H
#define SCORE_H
#include <Observer/Observer.h>

namespace logic {

class Score : public Observer {
public:
    Score() = default;
    void update(EventType event) override;
    void updateTick(float deltaTime);
    [[nodiscard]] int getCurrentScore() const;

private:
    int _currentScore = 0;
    double _timeSinceLastIncrement = 0.0;
    double _accumulatedDecrease = 0.0;

    static constexpr double SCORE_DECREASE_RATE = 1.0; // 1 per second
    static constexpr int COIN_VALUE = 10;
    static constexpr double MAX_MULTIPLIER_TIME = 3.0; // after 3 seconds you just get COIN_VALUE
};

} // namespace logic

#endif // SCORE_H
