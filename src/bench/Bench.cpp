#include <algorithm>
#include <chrono>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <random>
#include <vector>

#include "AoS.hpp"
#include "WorldState.hpp"
#include "PhysicsEngine.hpp"

static constexpr double G = 6.67430e-11;
static constexpr double CENTRAL_MASS = 5.972e24;
static constexpr double MU = G * CENTRAL_MASS;
static constexpr double PI = 3.14159265358979323846;

class Generator
{
public:
    std::mt19937 rng;
    std::uniform_real_distribution<double> r0_dist;
    std::uniform_real_distribution<double> noise;
    std::uniform_real_distribution<double> angle;

    Generator()
        : rng(42), r0_dist(1e7, 1e8), noise(-0.1, 0.1), angle(0.0, 2.0 * PI)
    {
    }

    void Generate(int N, std::vector<Body> &aos, WorldState &soa)
    {
        aos.reserve(static_cast<size_t>(N));
        for (int i = 0; i < N; ++i)
        {
            const double r0 = r0_dist(rng);
            const double v0 = std::sqrt(MU / r0) * (1.0 + noise(rng));
            const double theta = angle(rng);

            const double x = r0 * std::cos(theta);
            const double y = r0 * std::sin(theta);
            const double vx = -v0 * std::sin(theta);
            const double vy = v0 * std::cos(theta);

            aos.push_back({x, y, vx, vy, 1.0});
            soa.Add(x, y, vx, vy, 1.0);
        }
    }
};

static double Median(std::vector<double> v)
{
    std::sort(v.begin(), v.end());
    return v[v.size() / 2];
}

static double time_aos(const std::vector<Body> &init, int steps, double dt, double &sink)
{
    PhysicsEngineAoS engine;
    engine.CentralMass = CENTRAL_MASS;

    constexpr int WARMUP_RUNS = 10;
    constexpr int MEASURE_RUNS = 5;

    // уходит в sink, чтобы компилятор не выкинул работу.
    for (int r = 0; r < WARMUP_RUNS; ++r)
    {
        std::vector<Body> work = init;
        for (int s = 0; s < steps; ++s)
            engine.Step(work, dt);
        for (const auto &b : work)
            sink += b.x + b.y + b.vx + b.vy;
    }

    std::vector<double> times;
    times.reserve(MEASURE_RUNS);
    for (int r = 0; r < MEASURE_RUNS; ++r)
    {
        std::vector<Body> work = init;
        const auto t0 = std::chrono::high_resolution_clock::now();
        for (int s = 0; s < steps; ++s)
            engine.Step(work, dt);
        const auto t1 = std::chrono::high_resolution_clock::now();
        for (const auto &b : work)
            sink += b.x + b.y + b.vx + b.vy;
        times.push_back(std::chrono::duration<double, std::milli>(t1 - t0).count());
    }
    return Median(std::move(times));
}

static double time_soa(const WorldState &init, int steps, double dt, double &sink)
{
    PhysicsEngine engine;
    engine.CentralMass = CENTRAL_MASS;

    constexpr int WARMUP_RUNS = 10;
    constexpr int MEASURE_RUNS = 5;

    for (int r = 0; r < WARMUP_RUNS; ++r)
    {
        WorldState work = init;
        for (int s = 0; s < steps; ++s)
            engine.Step(work, dt);
        for (int i = 0; i < work.Count; ++i)
            sink += work.PosX[i] + work.PosY[i] + work.VelX[i] + work.VelY[i];
    }

    std::vector<double> times;
    times.reserve(MEASURE_RUNS);
    for (int r = 0; r < MEASURE_RUNS; ++r)
    {
        WorldState work = init;
        const auto t0 = std::chrono::high_resolution_clock::now();
        for (int s = 0; s < steps; ++s)
            engine.Step(work, dt);
        const auto t1 = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < work.Count; ++i)
            sink += work.PosX[i] + work.PosY[i] + work.VelX[i] + work.VelY[i];
        times.push_back(std::chrono::duration<double, std::milli>(t1 - t0).count());
    }
    return Median(std::move(times));
}

int main()
{
    constexpr double DT = 0.1;
    constexpr int STEPS = 100;

    double sink = 0.0;

    std::cout << "N,t_aos_ms,t_soa_ms\n";

    for (int N : {1000, 10000, 100000})
    {
        Generator gen;
        std::vector<Body> aos;
        WorldState soa(N);
        gen.Generate(N, aos, soa);

        
        // сравнение результатов
        std::vector<Body> aos_copy = aos;
        WorldState soa_copy = soa;
        PhysicsEngineAoS engine_aos;
        PhysicsEngine engine_soa;
        engine_aos.CentralMass = CENTRAL_MASS;
        engine_soa.CentralMass = CENTRAL_MASS;
        for (int s = 0; s < STEPS; ++s)
        {
            engine_aos.Step(aos_copy, DT);
            engine_soa.Step(soa_copy, DT);
        }
        double max_diff = 0.0;
        for (int i = 0; i < N; ++i)
        {
            const double dx = std::abs(aos_copy[i].x - soa_copy.PosX[i]);
            const double dy = std::abs(aos_copy[i].y - soa_copy.PosY[i]);
            const double dvx = std::abs(aos_copy[i].vx - soa_copy.VelX[i]);
            const double dvy = std::abs(aos_copy[i].vy - soa_copy.VelY[i]);
            max_diff = std::max({max_diff, dx, dy, dvx, dvy});
        }
        std::cout << "max_diff " << max_diff << '\n';


        // сравнение производительности
        const double t_aos = time_aos(aos, STEPS, DT, sink);
        const double t_soa = time_soa(soa, STEPS, DT, sink);

        std::cout << N << ','
                  << std::fixed << std::setprecision(3)
                  << t_aos << ',' << t_soa << '\n';
    }

    // https://stackoverflow.com/questions/31195802/is-it-realistic-to-use-o3-or-ofast-to-compile-your-benchmark-code-or-will-it-r
    std::cout << "sink = " << sink << '\n';
    return 0;
}