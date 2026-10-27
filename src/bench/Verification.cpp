#include <cmath>
#include <iostream>

static const double G = 6.67430e-11;
static const double M = 5.972e24;
static const double R0 = 7e6;
static const double MU = G * M;
static const double V0 = std::sqrt(MU / R0);
static const double PI = 3.14159265358979323846;
static const double T = 2.0 * PI * std::sqrt(R0 * R0 * R0 / MU);

int main()
{
    std::cout << "dt,error\n";
    const double ratio_min = 50.0;
    const double ratio_max = 20000.0;
    const int n_points = 20;

    for (int k = 0; k < n_points; ++k)
    {
        double t = (double)k / (n_points - 1);                         // 0..1
        double ratio = ratio_min * std::pow(ratio_max / ratio_min, t); // равномерно
        int n = (int)ratio;
        double dt = T / n;

        double x = R0, y = 0.0, vx = 0.0, vy = V0;
        for (int i = 0; i < n; ++i)
        {
            double r2 = x * x + y * y;
            double invR3 = 1.0 / (r2 * std::sqrt(r2));
            vx += -MU * x * invR3 * dt;
            vy += -MU * y * invR3 * dt;
            x += vx * dt;
            y += vy * dt;
        }
        std::cout << dt << "," << std::hypot(x - R0, y) << "\n"; // разница в расстоянии между численным решением и точным за один период
    }
}