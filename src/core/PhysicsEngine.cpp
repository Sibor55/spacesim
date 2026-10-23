#include "PhysicsEngine.hpp"
#include <cmath>

void PhysicsEngine::Step(WorldState& s, double dt) {
    for (int i = 0; i < s.Count; i++) {
        double x = s.PosX[i];
        double y = s.PosY[i];
        double r2 = x*x + y*y;
        double r = std::sqrt(r2);
        double r3 = r2 * r;
        double invR3 = 1.0 / r3;

        double ax = -G * CentralMass * x * invR3;
        double ay = -G * CentralMass * y * invR3;

        s.VelX[i] += ax * dt;
        s.VelY[i] += ay * dt;
        s.PosX[i] += s.VelX[i] * dt;
        s.PosY[i] += s.VelY[i] * dt;
    }
}