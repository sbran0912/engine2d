#pragma once
#include "rl2d_core.h"

struct Figure2d {
    std::string typ;
    Vec2d location;
    Vec2d velocity;
    float angVelocity;
    Vec2d accel;
    float angAccel;
    float mass;
    float inertia;
    bool marked;
    float radius;
    Vec2d orientation;
    std::array<Vec2d, 5> vertices;

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
