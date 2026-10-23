#include <iostream>
#include <cmath>
#include "WorldState.hpp"
#include "PhysicsEngine.hpp"
#include "Renderer.hpp"

int main()
{
    WorldState world(16);
    PhysicsEngine engine;
    engine.CentralMass = 5.972e24;

    double r0 = 7e6;
    double v0 = std::sqrt(PhysicsEngine::G * engine.CentralMass / r0);
    Renderer renderer(800, 600, "Space Simulation");

    world.Add(r0, 0.0, 0.0, v0, 1000.0);

    double dt = 1.0;
    while (renderer.IsOpen())
    {
        renderer.PollEvents();
        engine.Step(world, dt);
        renderer.Draw(world);
    }
}