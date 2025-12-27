#include "Score.h"

#include <algorithm>
#include <fstream>
#include <iostream>

namespace logic {

Score::Score() { loadHighscores(); }

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

    if (event == EventType::FruitCollected) {
        _currentScore += FRUIT_VALUE;
    }

    if (event == EventType::GhostEaten) {
        _currentScore += GHOST_VALUE;
    }

    if (event == EventType::GameOver) {
        saveScore();
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

std::vector<int> Score::getHighscores() const { return _highscores; }

void Score::saveScore() const {
    std::vector<int> scores = _highscores;
    scores.push_back(_currentScore);
    std::sort(scores.rbegin(), scores.rend());

    if (scores.size() > 5) {
        scores.resize(5);
    }

    std::ofstream file(HIGHSCORES_FILE);
    if (file.is_open()) {
        for (const int score : scores) {
            file << score << "\n";
        }
        file.close();
    }
}

void Score::loadHighscores() {
    std::vector<int> scores;
    std::ifstream file(HIGHSCORES_FILE);

    if (file.is_open()) {
        int score;
        while (file >> score) {
            scores.push_back(score);
        }
        file.close();
    }

    std::sort(scores.rbegin(), scores.rend());

    if (scores.size() > 5) {
        scores.resize(5);
    }

    _highscores = scores;
}

} // namespace logic