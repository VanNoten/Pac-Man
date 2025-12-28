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
};

} // namespace logic

#endif // SCORE_H
