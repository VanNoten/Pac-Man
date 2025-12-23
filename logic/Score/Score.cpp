#include "Score.h"
#include <iostream>

namespace logic {

void Score::update(EventType event) {
    if (event == EventType::CoinCollected) {
        const double timeWindow = _timeSinceLastIncrement < MAX_MULTIPLIER_TIME && _timeSinceLastIncrement > 0.0
                                      ? _timeSinceLastIncrement
                                      : MAX_MULTIPLIER_TIME;

        // right now max multiplier is x2
        const double bonusMultiplier = 1.0 + (MAX_MULTIPLIER_TIME - timeWindow) / MAX_MULTIPLIER_TIME;
        _currentScore += static_cast<int>(COIN_VALUE * bonusMultiplier);
        _timeSinceLastIncrement = 0.0;
    }
}

void Score::updateTick(float deltaTime) {
    _accumulatedDecrease += SCORE_DECREASE_RATE * deltaTime;

    if (_accumulatedDecrease >= 1.0) {
        const int decreaseAmount = static_cast<int>(_accumulatedDecrease);
        _currentScore -= decreaseAmount;
        _accumulatedDecrease -= decreaseAmount;

        if (_currentScore < 0) {
            _currentScore = 0;
        }
    }

    _timeSinceLastIncrement += deltaTime;
}

int Score::getCurrentScore() const { return _currentScore; }

} // namespace logic