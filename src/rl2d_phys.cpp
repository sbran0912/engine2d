#include "rl2d_phys.h"

Vec2d Figure2d::checkKicking() {

    Vec2d mousePos{ (float)GetMouseX(), (float)GetMouseY() };

    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {

        if (location.distance(mousePos) < 10) {
            marked = true;
        }

        if (marked) {
            core::DrawArrow(location, mousePos, RED);
        }
    }

    if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT) && marked) {
        marked = false;
        return core::subVec(mousePos, location);
    }

    return Vec2d{0, 0};
}

Ball::Ball(): 
    Figure2d()
    {}

Ball::Ball(float x, float y, float r)
    {
        typ = "Ball";
        marked = false;
        location = Vec2d{ x, y };
        radius = r;
        mass = radius * 2;
        inertia = radius * radius * radius / 2;
        velocity = Vec2d{ 0, 0 };
        angVelocity = 0;
        accel = Vec2d{ 0, 0 };
        angAccel = 0;
        orientation = Vec2d{ radius + x, 0 + y };
    }

void Ball::rotate(float angle) {
    // noch leer
}

void Ball::draw(float thick, Color c) {
    DrawCircleV(location.pos,radius, c);
    DrawLineEx(location.pos, orientation.pos, 3, c);
}

void Ball::update(){
    // noch leer
}

void Ball::applyForce(Vec2d force, float angForce){
    //noch leer
}

void Ball::resetPos(){
    //noch leer
}

void Ball::test() {
    //printf("Hier ist der Ball\n");
}

Box::Box():
    Figure2d()
    {}

Box::Box(float x, float y, float w, float h)
    {
        typ = "Box";
        marked = false;
        location = Vec2d{ x + w / 2, y + h / 2 };
        mass = (w + h) * 2;
        inertia = w * h * w;
        velocity = Vec2d{ 0, 0 };
        angVelocity = 0;
        accel = Vec2d{ 0, 0 };
        angAccel = 0;
        vertices[0] = Vec2d{ x, y };
        vertices[1] = Vec2d{ x + w, y };
        vertices[2] = Vec2d(x + w, y + h);
        vertices[3] = Vec2d{x, y + h};
        vertices[4] = Vec2d{ x, y };
    }

void Box::rotate(float angle) {
    for (int i = 0; i < 5; i++) {
        vertices[i].rotate(location, angle);
    }
}

void Box::draw(float thick, Color c) {
    for (int i = 0; i < 4; i++) {
        DrawLineEx(vertices[i].pos, vertices[i+1].pos, thick, c);
    }
    DrawCircleV(location.pos, 5, c);
}

void Box::update() {
    //noch leer
}

void Box::applyForce(Vec2d force, float angForce){
    //noch leer
}

void Box::resetPos() {
    //noch leer
}

void Box::test() {
    //printf("Hier ist die Box\n");
}