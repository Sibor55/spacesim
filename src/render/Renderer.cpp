#include "Renderer.hpp"
#include "WorldState.hpp"
Renderer::Renderer(int w, int h, const char *title)
    : window(sf::VideoMode({static_cast<unsigned int>(w), static_cast<unsigned int>(h)}), title),
      circle(4.0f),
      centerX(w / 2.0f),
      centerY(h / 2.0f),
      scale(250.0 / 7e6)
{
    circle.setOrigin({4.0f, 4.0f});
    circle.setFillColor(sf::Color::White);
}

bool Renderer::IsOpen() const { return window.isOpen(); }

void Renderer::PollEvents()
{
    while (const std::optional event = window.pollEvent())
    {
        if (event->is<sf::Event::Closed>())
        {
            window.close();
        }
    }
}

sf::Vector2f Renderer::WorldToScreen(double x, double y) const
{
    float sx = centerX + (float)(x * scale);
    // Экранная ось Y направлена вниз, поэтому меняем знак
    float sy = centerY - (float)(y * scale);
    return {sx, sy};
}

void Renderer::Draw(WorldState &world)
{
    window.clear(sf::Color::Black);
    if (world.Count > 0)
    {
        for (int i = 0; i < world.Count; ++i)
        {
            circle.setPosition(WorldToScreen(world.PosX[i], world.PosY[i]));
            window.draw(circle);
        }
    }
    window.display();
}