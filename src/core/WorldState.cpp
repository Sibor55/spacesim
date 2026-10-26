#include "WorldState.hpp"
#include <stdexcept>

WorldState::WorldState(int capacity)
{
    Capacity = ((capacity +3) / 4) * 4; // Всегда кратное 4
    PosX.resize(Capacity);
    PosY.resize(Capacity);
    VelX.resize(Capacity);
    VelY.resize(Capacity);
    Mass.resize(Capacity);
    Count = 0;
}
int WorldState::Add(double x, double y, double vx, double vy, double mass) {
    if (Count >= Capacity) throw std::runtime_error("WorldState is full");
    int i = Count;
    PosX[i] = x; PosY[i] = y;
    VelX[i] = vx; VelY[i] = vy;
    Mass[i] = mass;
    Count++;
    return i;
}