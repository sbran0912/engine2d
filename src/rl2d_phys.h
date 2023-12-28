#include <string>
#include <array>
#include "rl2d_core.h"

#ifndef PHYS_H
#define PHYS_H

struct Box {
    const std::string typ = "BOX";
    std::array<Vec2d, 5> vertices;
    Vec2d location;
    Vec2d velocity;
    float angVelocity;
    Vec2d accel;
    float angAccel;
    float mass;
    float inertia;
    bool marked;

    Box();
    Box(float x, float y, float w, float h);

    void rotate(float angle);
    void draw(float thick, Color c);
    void checkKicking();
};

#endif
