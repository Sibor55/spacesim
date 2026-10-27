#include <cmath>
#include <vector>

struct Body
{
    double x, y, vx, vy, mass;
};

class PhysicsEngineAoS
{
    public:
        static constexpr double G = 6.67430e-11;
        double CentralMass = 0.0; // Масса большого тела
        void Step(std::vector<Body>& bodies, double dt) 
        {
            for (auto& b : bodies) {
                double r2 = b.x*b.x + b.y*b.y;
                double r = std::sqrt(r2);
                double r3 = r2 * r;
                double invR3 = 1.0 / r3; 
                double ax = -G * CentralMass * b.x * invR3;
                double ay = -G * CentralMass * b.y * invR3;

                b.vx += ax * dt;
                b.vy += ay * dt;
                b.x += b.vx * dt;
                b.y += b.vy * dt;
            }
        }
};