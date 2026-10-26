#pragma once
#include <SFML/Graphics.hpp>

class WorldState;
// TODO: Floating Origin, cameraX/cameraY в double,
//   вычитание камеры в WorldToScreen до scale. 

// TODO(+- ~декабрь): зум камеры (колесо мыши или +/-),
//   меняет scale.

// TODO(декабрь): хвост траектории (последние N позиций,
//   sf::VertexArray + LineStrip).

class Renderer {
public:
    Renderer(int w, int h, const char* title);
    bool IsOpen() const;
    void FitOrbit(double r0, float margin);
    void PollEvents();
    void Draw(WorldState& world);

    Renderer(const Renderer&) = delete;
    Renderer& operator=(const Renderer&) = delete;

private:
    sf::Vector2f WorldToScreen(double x,double y) const;
    sf::RenderWindow window;
    sf::CircleShape  circle;
    float  centerX = 0.f;
    float  centerY = 0.f;
    double scale   = 1.0; // Масштаб в пикселях на метр
};
