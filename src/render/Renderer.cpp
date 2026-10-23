#include "Renderer.hpp"
#include "WorldState.hpp"
Renderer::Renderer(int w, int h, const char *title)
    // 1. Используем список инициализации для VideoMode
    : window(sf::VideoMode({static_cast<unsigned int>(w), static_cast<unsigned int>(h)}), title),
      circle(4.0f),
      centerX(w / 2.0f),
      centerY(h / 2.0f),
      scale(250.0 / 7e6)
{
    // 2. setOrigin теперь принимает sf::Vector2f
    circle.setOrigin({4.0f, 4.0f});
    circle.setFillColor(sf::Color::White);
}

bool Renderer::IsOpen() const { return window.isOpen(); }

void Renderer::PollEvents()
{
    // 3. Новый цикл обработки событий с std::optional
    while (const std::optional event = window.pollEvent())
    {
        // 4. Проверка типа события через is<T>()
        if (event->is<sf::Event::Closed>())
        {
            window.close();
        }
    }
}

sf::Vector2f Renderer::WorldToScreen(double x, double y) const
{
    float sx = centerX + (float)(x * scale);
    float sy = centerY - (float)(y * scale); // минус!
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