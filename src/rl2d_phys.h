#pragma once
#include "rl2d_core.h"

struct Figure2d {
    char typ;
    Vec2d location{0.0f, 0.0f};
    Vec2d velocity{0.0f, 0.0f};
    float angVelocity{0};
    Vec2d accel{0.0f, 0.0f};
    float angAccel{0};
    float mass{0};
    float inertia{0};
    bool marked{false};
    float radius{0};
    Vec2d orientation{0.0f, 0.0f};
    std::array<Vec2d, 5> vertices{};

    virtual void draw(float thick, Color c) = 0;
    virtual void rotate(float angle) = 0;
    virtual void update() = 0;
    virtual void applyForce(Vec2d force, float angForce) = 0;
    virtual void resetPos(Vec2d v) = 0;
    virtual void test() = 0;
    Vec2d checkKicking();
};

struct Ball : public Figure2d {
    Ball(float x, float y, float r);

    void rotate(float angle);
    void draw(float thick, Color c);
    void update();
    void applyForce(Vec2d force, float angForce);
    void resetPos(Vec2d v);
    void test();
};

struct Box: public Figure2d {
    Box(float x, float y, float w, float h);

    void rotate(float angle);
    void draw(float thick, Color c);
    void update();
    void applyForce(Vec2d force, float angForce);
    void resetPos(Vec2d v);
    void test();
};
