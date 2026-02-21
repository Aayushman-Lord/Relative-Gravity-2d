#pragma once
#include <iostream>
#include <vector>
#include <raylib.h>


class Object 
{
    public:
        Vector2 position;
        Vector2 velocity;
        Vector2 acceleration;
        float mass;
        float radius;
        float properTime;
        float density;
        Color color;
        std::vector<Vector2> trails;
        
        Object(Vector2 pos, Vector2 velo, float mass, Color color, float radius);
        void Display();
        void Update(float dt);
        void getTrails();
};

