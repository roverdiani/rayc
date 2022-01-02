//
// Created by rocve on 01/01/2022.
//

#include "Fps.h"

Fps::Fps()
{
    _clock = std::make_unique<sf::Clock>();
    _previousTime = _clock->getElapsedTime();

    _arialFont = sf::Font();
    _arialFont.loadFromFile("arial.ttf");
}

void Fps::Render(const std::shared_ptr<sf::RenderWindow>& renderWindow)
{
    _fpsText = sf::Text();
    _fpsText.setFont(_arialFont);
    _fpsText.setCharacterSize(24);
    _fpsText.setFillColor(sf::Color(0, 255, 0, 255));
    _fpsText.setStyle(sf::Text::Bold);
    _fpsText.setString(sf::String("FPS: " + std::to_string(GetFps())));
    sf::FloatRect textRect = _fpsText.getLocalBounds();
    _fpsText.setOrigin(sf::Vector2f(textRect.left + textRect.width / 2.0f,
                                    textRect.top + textRect.height / 2.0f));
    _fpsText.setPosition(renderWindow->getView().getCenter().x, renderWindow->getView().getCenter().y * 1.5f);
    renderWindow->draw(_fpsText);
}

float Fps::GetFps()
{
    _currentTime = _clock->getElapsedTime();
    float fps = 1.0f / (_currentTime.asSeconds() - _previousTime.asSeconds());
    _previousTime = _currentTime;

    return fps;
}
