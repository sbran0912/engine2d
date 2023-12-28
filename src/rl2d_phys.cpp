#include "rl2d_phys.h"

Box::Box()
    :
    vertices{ Vec2d{ 0.0f, 0.0f }, Vec2d{ 0.0f, 0.0f }, Vec2d(0.0f, 0.0f), Vec2d{0.0f, 0.0f}, Vec2d{ 0.0f, 0.0f } },
    location{ 0.0f, 0.0f},
    velocity{ 0.0f, 0.0f },
    angVelocity{ 0.0f },
    accel{ 0.0f, 0.0f },
    angAccel{ 0.0f },
    mass{ 0.0f },
    inertia{ 0.0f },
    marked{false}
{}

Box::Box(float x, float y, float w, float h)
    : 
        vertices{ Vec2d{ x, y }, Vec2d{ x + w, y }, Vec2d(x + w, y + h), Vec2d{x, y + h}, Vec2d{ x, y } },
        location{ x + w / 2, y + h / 2 }, 
        velocity{ 0.0f, 0.0f }, 
        angVelocity{ 0.0f }, 
        accel{ 0.0f, 0.0f }, 
        angAccel{0.0f},
        mass{ (w + h) * 2 }, 
        inertia{ w * h * w },
        marked{false}
    {} 

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

void Box::checkKicking() {

    Vec2d mousePos{(float)GetMouseX(), (float)GetMouseY()};

    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
        
        if (location.distance(mousePos) < 10) {
            marked = true;
        }

        if (marked) {
            DrawArrow(location, mousePos, RED);
            //printf("Box Location x und y: %f %f, MousPos x und y: %f %f\n\n", location.pos.x, location.pos.y, mousePos.pos.x, mousePos.pos.y);
        }
    }

    if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT) && marked) {
        printf("Maus losgelassen, Stärke : %f\n\n", subVec(location, mousePos).mag());
        marked = false;
    }
}