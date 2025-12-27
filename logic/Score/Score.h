#ifndef SCORE_H
#define SCORE_H
#include <Observer/Observer.h>
#include <string>
#include <vector>

namespace logic {

static constexpr std::string HIGHSCORES_FILE = "highscores.txt";

class Score : public Observer {
public:
    Score();
    void update(EventType event) override;
    void updateTick(float deltaTime);
    [[nodiscard]] int getCurrentScore() const;
    [[nodiscard]] std::vector<int> getHighscores() const;

private:
    void saveScore() const;
    void loadHighscores();

    int _currentScore = 0;
    double _timeSinceLastIncrement = 0.0;
    double _accumulatedDecrease = 0.0;

    std::vector<int> _highscores = {};

    static constexpr double SCORE_DECREASE_RATE = 1.0; // 1 per second
    static constexpr int COIN_VALUE = 10;
    static constexpr double MAX_MULTIPLIER_TIME = 3.0; // after 3 seconds you just get COIN_VALUE

    static constexpr int FRUIT_VALUE = 100;

    static constexpr int GHOST_VALUE = 200;
};

} // namespace logic

#endif // SCORE_H
