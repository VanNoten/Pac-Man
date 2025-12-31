#include "Score.h"

#include <Util/Constants.h>
#include <algorithm>
#include <fstream>
#include <iostream>

namespace logic {

using namespace logic::util;

Score::Score() { loadHighscores(); }

void Score::onNotify(EventType event) {
    if (event == EventType::CoinCollected) {
        const double timeWindow =
            _timeSinceLastIncrement < GameConstants::MAX_MULTIPLIER_TIME && _timeSinceLastIncrement > 0.0
                ? _timeSinceLastIncrement
                : GameConstants::MAX_MULTIPLIER_TIME;

        // right now max multiplier is x2
        const double bonusMultiplier =
            1.0 + (GameConstants::MAX_MULTIPLIER_TIME - timeWindow) / GameConstants::MAX_MULTIPLIER_TIME;
        _currentScore += static_cast<int>(GameConstants::COIN_VALUE * bonusMultiplier);
        _timeSinceLastIncrement = 0.0;
    }

    if (event == EventType::FruitCollected) {
        _currentScore += GameConstants::FRUIT_VALUE;
        _timeSinceLastIncrement = 0.0;
    }

    if (event == EventType::GhostEaten) {
        _currentScore += GameConstants::GHOST_VALUE;
        _timeSinceLastIncrement = 0.0;
    }

    if (event == EventType::GameOver) {
        saveScore();
    }

    if (event == EventType::LevelCleared) {
        _currentScore += GameConstants::LEVEL_CLEAR_VALUE;
        _timeSinceLastIncrement = 0.0;
    }
}

void Score::updateTick(float deltaTime) {
    // Accumulate deltaTime until enough time has passed to decrease the score
    _accumulatedDecrease += GameConstants::SCORE_DECREASE_RATE * deltaTime;

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
    // Get all current high scores and sort in descending order
    std::vector<int> scores = _highscores;
    scores.push_back(_currentScore);
    std::sort(scores.rbegin(), scores.rend());

    // Take the top 5 high scores
    if (scores.size() > 5) {
        scores.resize(5);
    }

    // Save new high scores to file
    std::ofstream file(GameConstants::HIGHSCORES_FILE);
    if (file.is_open()) {
        for (const int score : scores) {
            file << score << "\n";
        }
        file.close();
    }
}

void Score::loadHighscores() {
    // Get all current high scores and sort in descending order
    std::vector<int> scores;
    std::ifstream file(GameConstants::HIGHSCORES_FILE);

    if (file.is_open()) {
        int score;
        while (file >> score) {
            scores.push_back(score);
        }
        file.close();
    }

    std::sort(scores.rbegin(), scores.rend());

    // Take the top 5 high scores
    if (scores.size() > 5) {
        scores.resize(5);
    }

    _highscores = scores;
}

} // namespace logic