#include <raylib.h>
#include <vector>
#include <cmath>
#include "Objects.h"

const float G = 0.1f;    // scaled gravity constant
const float C = 1000.0f; // speed of light (simulation max speed)



int main()
{
    // Main variables
    const int screenWidth = 1200;
    const int screenHeight = 900;

    // Objects
    // SUN
    Object sun(
        {screenWidth / 2.0f, screenHeight / 2.0f},
        {0.0f, 0.0f},
        1989000.0f,
        YELLOW,
        30.0f);

    // MERCURY
    Object mercury(
        {screenWidth / 2.0f + 60.0f, screenHeight / 2.0f},
        {0.0f, 57.6f},
        0.3285f,
        GRAY,
        4.0f);

    // VENUS
    Object venus(
        {screenWidth / 2.0f + 100.0f, screenHeight / 2.0f},
        {0.0f, 44.6f},
        4.867f,
        ORANGE,
        6.0f);

    // EARTH
    Object earth(
        {screenWidth / 2.0f + 150.0f, screenHeight / 2.0f},
        {0.0f, 36.4f},
        5.972f,
        BLUE,
        6.0f);

    // MARS
    Object mars(
        {screenWidth / 2.0f + 220.0f, screenHeight / 2.0f},
        {0.0f, 30.1f},
        0.639f,
        RED,
        5.0f);

    // JUPITER
    Object jupiter(
        {screenWidth / 2.0f + 400.0f, screenHeight / 2.0f},
        {0.0f, 22.3f},
        1898.0f,
        ORANGE,
        15.0f);

    // SATURN
    Object saturn(
        {screenWidth / 2.0f + 550.0f, screenHeight / 2.0f},
        {0.0f, 19.0f},
        568.3f,
        BEIGE,
        13.0f);

    // URANUS
    Object uranus(
        {screenWidth / 2.0f + 700.0f, screenHeight / 2.0f},
        {0.0f, 16.8f},
        86.81f,
        SKYBLUE,
        11.0f);

    // NEPTUNE
    Object neptune(
        {screenWidth / 2.0f + 850.0f, screenHeight / 2.0f},
        {0.0f, 15.3f},
        102.4f,
        DARKBLUE,
        11.0f);

    std::vector<Object> ob;

    ob.push_back(sun);
    ob.push_back(mercury);
    ob.push_back(venus);
    ob.push_back(earth);
    ob.push_back(mars);
    ob.push_back(jupiter);
    ob.push_back(saturn);
    ob.push_back(uranus);
    ob.push_back(neptune);

    // Initialize window
    InitWindow(screenWidth, screenHeight, "Atomic Sim");
    SetTargetFPS(60);

    // Camera
    Camera2D camera = {0};
    camera.target = {screenWidth / 2, screenHeight / 2};
    camera.offset = {screenWidth / 2, screenHeight / 2};
    camera.zoom = 1;

    // gameloop
    while (!WindowShouldClose())
    {
        float dt = GetFrameTime(); // delta time

        //  1. Update velocities and positions
        for (Object &obj : ob)
        {
            obj.Update(dt / 2);
        }

        // Reset accelerations
        for (Object &obj : ob)
        {
            obj.acceleration = {0.0f, 0.0f};
        }

        // apply forces between all pairs of objects
        for (int i = 0; i < ob.size(); i++)
        {
            for (int j = 0; j < ob.size(); j++)
            {
                if (i == j)
                    continue;

                Object &p = ob[i];
                Object &q = ob[j];

                // Displacement vector from p → q
                Vector2 r =
                    {
                        q.position.x - p.position.x,
                        q.position.y - p.position.y};

                // Distance squared and distance
                float distSq = r.x * r.x + r.y * r.y;

                // Prevent singularity
                if (distSq < 1.0f)
                    distSq = 1.0f;

                float distance = sqrtf(distSq);

                // Unit direction vector
                Vector2 direction =
                    {
                        r.x / distance,
                        r.y / distance};

                // Velocity magnitude of object p
                float vSq =
                    p.velocity.x * p.velocity.x +
                    p.velocity.y * p.velocity.y;

                float speed = sqrtf(vSq);

                // Clamp speed below speed of light
                if (speed >= C)
                {
                    float scale = (C * 0.999f) / speed;
                    p.velocity.x *= scale;
                    p.velocity.y *= scale;
                    speed = C * 0.999f;
                    vSq = speed * speed;
                }

                // Lorentz factor γ
                float gamma =
                    1.0f / sqrtf(1.0f - (vSq / (C * C)));

                // Newtonian gravitational force magnitude
                float F =
                    (G * p.mass * q.mass) / distSq;

                // Relativistic inertia correction
                // acceleration decreases as velocity increases
                float accelMagnitude =
                    F / (p.mass * gamma * gamma * gamma);

                // Apply acceleration vector
                p.acceleration.x += accelMagnitude * direction.x;
                p.acceleration.y += accelMagnitude * direction.y;

                // Proper time update (time dilation)
                p.properTime += dt / gamma;
            }
        }

        // check collsions
        for (int i = 0; i < ob.size(); i++)
        {
            for (int j = 0; j < ob.size(); j++)
            {
                if (i == j)
                    continue;

                if (CheckCollisionCircles(ob[i].position, ob[i].radius, ob[j].position, ob[j].radius))
                {
                    Object &obj1 = ob[i];
                    Object &obj2 = ob[j];

                    // store original masses
                    float m1 = obj1.mass;
                    float m2 = obj2.mass;

                    // calculate areas using density
                    float A1 = m1 / obj1.density;
                    float A2 = m2 / obj2.density;

                    // new mass
                    float newMass = m1 + m2;

                    // new density (physically correct weighted density)
                    float newDensity = newMass / (A1 + A2);

                    // new radius from area
                    float newRadius = sqrt((A1 + A2) / PI);

                    // CONSERVE MOMENTUM (VERY IMPORTANT)
                    Vector2 newVelocity;

                    newVelocity.x =
                        ((m1 * obj1.velocity.x) + (m2 * obj2.velocity.x)) / newMass;

                    newVelocity.y =
                        ((m1 * obj1.velocity.y) + (m2 * obj2.velocity.y)) / newMass;

                    // OPTIONAL: center of mass position
                    Vector2 newPosition;

                    newPosition.x =
                        ((m1 * obj1.position.x) + (m2 * obj2.position.x)) / newMass;

                    newPosition.y =
                        ((m1 * obj1.position.y) + (m2 * obj2.position.y)) / newMass;

                    // apply results
                    obj1.mass = newMass;
                    obj1.density = newDensity;
                    obj1.radius = newRadius;
                    obj1.velocity = newVelocity;
                    obj1.position = newPosition;

                    // remove second object
                    ob.erase(ob.begin() + j);
                    j--;
                }
            }
        }

        //  2. Update velocities and positions (again for better accuracy)
        for (Object &obj : ob)
        {
            obj.Update(dt / 2);
        }

        // Display
        BeginDrawing();
        ClearBackground(BLACK);
        BeginMode2D(camera);

        float camSpeed = 500 * GetFrameTime();

        if (IsKeyDown(KEY_W))
            camera.target.y -= camSpeed;
        if (IsKeyDown(KEY_S))
            camera.target.y += camSpeed;
        if (IsKeyDown(KEY_A))
            camera.target.x -= camSpeed;
        if (IsKeyDown(KEY_D))
            camera.target.x += camSpeed;

        // determine visible world region
        int cellSize = 5;
        float maxField = 1.0f;
        float epsilon = 10.0f;

        Vector2 topLeft = GetScreenToWorld2D({0, 0}, camera);
        Vector2 bottomRight = GetScreenToWorld2D(
            {(float)screenWidth, (float)screenHeight}, camera);

        // Gravity heatmap
        for (float x = topLeft.x; x < bottomRight.x; x += cellSize)
        {
            for (float y = topLeft.y; y < bottomRight.y; y += cellSize)
            {
                Vector2 point = {x + cellSize / 2, y + cellSize / 2};

                Vector2 field = {0, 0};

                // compute field from all objects
                for (Object &obj : ob)
                {
                    Vector2 r =
                        {
                            obj.position.x - point.x,
                            obj.position.y - point.y};

                    float distSq = r.x * r.x + r.y * r.y + epsilon;
                    float dist = sqrtf(distSq);

                    float g = (G * obj.mass) / distSq;

                    field.x += g * (r.x / dist);
                    field.y += g * (r.y / dist);
                }

                float magnitude = sqrtf(field.x * field.x + field.y * field.y);

                // normalize heat intensity
                float t = magnitude / maxField;
                if (t > 1)
                    t = 1;

                Color heat =
                    {
                        (unsigned char)(255 * t),
                        (unsigned char)(100 * t),
                        (unsigned char)(255 * t),
                        120};

                // draw heat cell
                DrawRectangleV({x, y}, {(float)cellSize, (float)cellSize}, heat);
            }
        }

        // Display all objects with Trails

        for (int i = 0; i < ob.size(); i++)
        {
            ob[i].Display();
            ob[i].getTrails();
        }

        EndMode2D();
        EndDrawing();
    }

    CloseWindow();
}