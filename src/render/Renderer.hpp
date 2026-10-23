#pragma once
#include <SFML/Graphics.hpp>

class WorldState;

class Renderer {
public:
    Renderer(int w, int h, const char* title);
    bool IsOpen() const;
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