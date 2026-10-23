#include "Renderer.hpp"
#include "WorldState.hpp"
Renderer::Renderer(int w, int h, const char* title)
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

void Renderer::PollEvents() {
    // 3. Новый цикл обработки событий с std::optional
    while (const std::optional event = window.pollEvent()) {
        // 4. Проверка типа события через is<T>()
        if (event->is<sf::Event::Closed>()) {
            window.close();
        }
    }
}

void Renderer::Draw(WorldState& world) {
    window.clear(sf::Color::Black);
    if (world.Count > 0) {
        float sx = centerX + (float)(world.PosX[0] * scale);
        float sy = centerY - (float)(world.PosY[0] * scale); // минус!
        circle.setPosition({sx, sy});
        window.draw(circle);
    }
    window.display();
}