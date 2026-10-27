This is a small orbital mechanics simulator written in C++.

The project simulates the motion of bodies under the gravitational influence of a central mass. It includes a basic physics engine, a renderer, and experiments with different ways of storing simulation data.

Current Features
- Orbital motion simulation
- Numerical integration
- Basic orbital visualization
- AoS and SoA data layout experiments
- Basic verification and benchmarking tools

This project is the starting point for my bachelor's thesis.

I want to investigate how analytical orbital methods, numerical integration, and data-oriented optimization can be combined in a computational kernel.

My main areas of interest are:

- Orbital mechanics and conic sections
- Numerical integration
- Data-Oriented Design (DOD)
- SIMD optimization

The hybrid approach is still under development.

Requirements: C++20 and CMake 3.16 or newer.


```bash
git clone https://github.com/Sibor55/spacesim.git
cd spacesim
cmake -S . -B build
cmake --build build
```
Plans for future:
- Improve simulation accuracy and verification
- Investigate analytical and numerical orbital propagation
- Benchmark AoS and SoA implementations
- Explore SIMD optimization
- Evaluate the accuracy and performance of the resulting computational kernel
