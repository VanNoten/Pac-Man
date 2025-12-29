#ifndef SCORE_H
#define SCORE_H
#include <Observer/Observer.h>
#include <string>
#include <vector>

namespace logic {

/**
 * @brief Tracks current score, handles score events and saves/loads high scores to file on disk.
 *
 * - Score decreases at SCORE_DECREASE_RATE per second
 * - Coins increments score by COIN_VALUE with multiplier based on time since last increment (faster collection = more
 * score)
 * - Fruits increments score by FRUIT_VALUE
 * - Eating ghosts increments score by GHOST_VALUE
 * - Clearing a level increments score by LEVEL_CLEAR_VALUE
 *
 * Top 5 high scores are loaded from file on construction and saved on game over.
 *
 * Implements Observer.
 */
class Score : public Observer {
public:
    /**
     * @brief Constructor calls loadHighscores() to load top 5 high scores from disk.
     */
    Score();

    /**
     * @brief Receives events and updates score based on the event type.
     * @param event Type of event received.
     */
    void onNotify(EventType event) override;

    /**
     * @brief Decreases score if it has taken too long since last score increment.
     * @param deltaTime Time since last frame.
     */
    void updateTick(float deltaTime);

    /**
     * @brief Returns the current score.
     */
    [[nodiscard]] int getCurrentScore() const;

    /**
     * @brief Returns the top 5 high scores
     */
    [[nodiscard]] std::vector<int> getHighscores() const;

private:
    /**
     * @brief Saves the current score to the high scores file on disk.
     */
    void saveScore() const;

    /**
     * @brief Loads the top 5 high scores from disk.
     */
    void loadHighscores();

    int _currentScore = 0;
    double _timeSinceLastIncrement = 0.0;
    double _accumulatedDecrease = 0.0;

    std::vector<int> _highscores = {};
};

} // namespace logic

#endif // SCORE_H
