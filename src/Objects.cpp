#include <iostream>
#include <vector>
#include <raylib.h>
#include "objects.h"
#include <cmath>



Object::Object(Vector2 pos, Vector2 velo, float mass, Color color, float radius)
{
    this->position = pos;
    this->velocity = velo;
    this->mass = mass;
    this->radius = radius;
    this->color = color;
    this->acceleration = {0.0f, 0.0f};
    this->density = mass / (PI * radius * radius); 
}

void Object::Display()
{
    DrawCircleV(position, radius, color);
}

void Object::getTrails()
{
    trails.push_back(position);

    if (trails.size() > 700)
        trails.erase(trails.begin());

    for (int i = 0; i < trails.size(); i++)
    {
        DrawPixel(trails[i].x, trails[i].y, color);
    }
}

void Object::Update(float dt)
{   
    // Update velocity from acceleration
    velocity.x += acceleration.x * dt;
    velocity.y += acceleration.y * dt;

    // Update position from velocity
    position.x += velocity.x * dt;
    position.y += velocity.y * dt;
}

