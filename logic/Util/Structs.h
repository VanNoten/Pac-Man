/**
 * @file Structs.h
 * @brief Contains Direction enum and Bounds struct
 */

#ifndef STRUCTS_H
#define STRUCTS_H

namespace logic::util {

enum class Direction { UP, DOWN, LEFT, RIGHT };

struct Bounds {
    float left;
    float right;
    float top;
    float bottom;
};

} // namespace logic::util

#endif // STRUCTS_H
