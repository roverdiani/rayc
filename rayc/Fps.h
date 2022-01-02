//
// Created by rocve on 01/01/2022.
//

#ifndef RAYC_FPS_H
#define RAYC_FPS_H

#include <memory>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

class Fps
{
public:
    Fps();
    void Render(const std::shared_ptr<sf::RenderWindow>& renderWindow);

private:
    float GetFps();

    std::unique_ptr<sf::Clock> _clock;
    sf::Time _previousTime;
    sf::Time _currentTime;
    sf::Text _fpsText;
    sf::Font _arialFont;
};

#endif //RAYC_FPS_H
