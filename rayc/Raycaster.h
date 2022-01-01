//
// Created by rocve on 31/12/2021.
//

#ifndef RAYC_RAYCASTER_H
#define RAYC_RAYCASTER_H

#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>
#include "Map.h"
#include "Player.h"
#include "Ray.h"

#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 768
#define WINDOW_LOGICAL_WIDTH 640
#define WINDOW_LOGICAL_HEIGHT 480
#define FPS 144
#define FOV 60.0f * (PI / 180.0f)

class Raycaster
{
public:
    Raycaster();

    void Loop();
    bool GetIsRunning() const;

private:
    bool _isRunning = false;
    float _deltaTime = 0;

    void CastRays();
    void RenderRays();
    void RenderWalls();
    void ProcessEvents();
    void Update();
    void Render();
    void ProcessKey(sf::Event::KeyEvent keyEvent, bool keyPressed);

    std::vector<std::unique_ptr<Ray>> _rays;

    std::shared_ptr<Map> _map;
    std::shared_ptr<Player> _player;

    sf::Event _event{};
    std::shared_ptr<sf::RenderWindow> _renderWindow;
    std::unique_ptr<sf::Clock> _deltaClock;
};

#endif //RAYC_RAYCASTER_H
