#include "rl2d_phys.h"

Figure2d::Figure2d():
    location{ 0.0f, 0.0f },
    velocity{ 0.0f, 0.0f },
    angVelocity{ 0.0f },
    accel{ 0.0f, 0.0f },
    angAccel{ 0.0f },
    mass{ 0.0f },
    inertia{ 0.0f },
    marked{ false }
    {}

Figure2d::Figure2d(float x, float y):
    location{ x, y },
    velocity{ 0.0f, 0.0f },
    angVelocity{ 0.0f },
    accel{ 0.0f, 0.0f },
    angAccel{ 0.0f },
    mass{ 0.0f },
    inertia{ 0.0f },
    marked{ false }
    {}

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
    Figure2d(),
    radius{0},
    orientation{0.0f, 0.0f}
    {}

Ball::Ball(float x, float y, float r):
    Figure2d(x, y),
    radius{r},
    orientation{ radius + x, 0 + y }
    {
        mass = radius * 2;
        inertia = radius * radius * radius / 2;
    }

void Ball::rotate(float angle) {
    // noch leer
}

void Ball::draw(float thick, Color c) {
    DrawCircleV(location.pos,radius, c);
    DrawLineEx(location.pos, orientation.pos, 3, WHITE);
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
    printf("Hier ist der Ball\n");
}

Box::Box():
    Figure2d(),
    vertices{ Vec2d{ 0.0f, 0.0f }, Vec2d{ 0.0f, 0.0f }, Vec2d(0.0f, 0.0f), Vec2d{0.0f, 0.0f}, Vec2d{ 0.0f, 0.0f } }
    {}

Box::Box(float x, float y, float w, float h):
    Figure2d(x, y),
    vertices{ Vec2d{ x, y }, Vec2d{ x + w, y }, Vec2d(x + w, y + h), Vec2d{x, y + h}, Vec2d{ x, y } }
    {
        location = { x + w / 2, y + h / 2 };
        mass = { (w + h) * 2 };
        inertia = { w * h * w };
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
    printf("Hier ist die Box\n");
}