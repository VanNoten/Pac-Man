/**
 * @file Structs.h
 * @brief Contains Direction enum and Bounds struct
 */

#ifndef STRUCTS_H
#define STRUCTS_H

namespace logic::util {

enum class Direction { UP, DOWN, LEFT, RIGHT };

struct Bounds {
    float left = 0;
    float right = 0;
    float top = 0;
    float bottom = 0;
};

} // namespace logic::util

#endif // STRUCTS_H
