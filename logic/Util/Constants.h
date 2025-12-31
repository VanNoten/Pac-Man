/**
 * @file Constants.h
 * @brief Contains constants for game configuration.
 */

#ifndef CONSTANTS_H
#define CONSTANTS_H

namespace logic::util::GameConstants {

static constexpr std::string HIGHSCORES_FILE = "highscores.txt";

static constexpr int STARTING_LIVES = 3;

static constexpr float BASE_PACMAN_SPEED = 0.4f;
static constexpr float BASE_GHOST_SPEED = 0.25f;
static constexpr float BASE_FEARED_GHOST_SPEED = 0.20f;
static constexpr float BASE_FEARED_DURATION = 6.0f;

static constexpr float SPEED_INCREASE_PER_LEVEL = 0.03f;
static constexpr float FEARED_DURATION_DECREASE_PER_LEVEL = 0.5f;
static constexpr float MAX_GHOST_SPEED = 0.40f;
static constexpr float MAX_FEARED_GHOST_SPEED = 0.35f;
static constexpr float MIN_FEARED_DURATION = 2.0f;

static constexpr float GHOST_1_DELAY = 0.0f;
static constexpr float GHOST_2_DELAY = 0.0f;
static constexpr float GHOST_3_DELAY = 5.0f;
static constexpr float GHOST_4_DELAY = 10.0f;

static constexpr double SCORE_DECREASE_RATE = 1.0; // 1 per second
static constexpr int COIN_VALUE = 10;
static constexpr double MAX_MULTIPLIER_TIME = 3.0; // after 3 seconds you just get COIN_VALUE
static constexpr int FRUIT_VALUE = 100;
static constexpr int GHOST_VALUE = 200;
static constexpr int LEVEL_CLEAR_VALUE = 500;

} // namespace logic::util::GameConstants

#endif // CONSTANTS_H
