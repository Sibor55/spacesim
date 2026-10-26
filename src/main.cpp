#include <cmath>
#include "WorldState.hpp"
#include "PhysicsEngine.hpp"
#include "Renderer.hpp"

int main()
{
    const int SCREEN_HEIGHT = 600;
    const int SCREEN_WIDTH = 800;

    const int WORLD_CAPACITY = 16;             // Максимальное количество объектов в мире
    // const double R0 = 16e6;
    const double R0 = 7e6;                     // радиус орбиты, м
    const double CENTRAL_BODY_MASS = 5.972e24; // Масса большого тела, кг
    const double DT = 0.1;                     // шаг симуляции, с
    const int STEPS_PER_FRAME = 20;            // 0.1 * 20 = 2 сим-секунды за кадр
    const double M_SAT = 1000.0;               // масса спутника, кг (для гравитации не важна)

    PhysicsEngine engine;
    engine.CentralMass = CENTRAL_BODY_MASS;
    // Скорость для круговой орбиты, направлена вдоль +Y.
    const double V0 = std::sqrt(PhysicsEngine::G * engine.CentralMass / R0);
    // const double V0 = 14e4;
    WorldState world(WORLD_CAPACITY);

    Renderer renderer(SCREEN_WIDTH, SCREEN_HEIGHT, "Space Simulation");

    world.Add(R0, 0.0, 0.0, V0, M_SAT);
    renderer.FitOrbit(R0, 1.2);
    while (renderer.IsOpen())
    {
        renderer.PollEvents();
        for (int i = 0; i < STEPS_PER_FRAME; i++)
        {
            engine.Step(world, DT);
        }

        renderer.Draw(world);
    }
}