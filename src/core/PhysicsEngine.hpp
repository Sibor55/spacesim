#pragma once
#include "WorldState.hpp"

class PhysicsEngine {
    public:
        static constexpr double G = 6.67430e-11;
        double CentralMass = 0.0;
        void Step(WorldState& s, double dt);
};