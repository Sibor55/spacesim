#pragma once
#include <vector>

class WorldState {
    public:
        std::vector<double> PosX;
        std::vector<double> PosY;
        std::vector<double> VelX;
        std::vector<double> VelY;
        std::vector<double> Mass;
        int Count = 0;
        int Capacity = 0;

        explicit WorldState(int capacity);
        int Add(double x, double y, double vx, double vy, double mass);
};