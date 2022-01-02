//
// Created by rocve on 31/12/2021.
//

#include "Raycaster.h"

Raycaster::Raycaster()
{
    _deltaClock = std::make_unique<sf::Clock>();
    _deltaClock->restart();
    _deltaTime = _deltaClock->restart().asSeconds();

    _renderWindow = std::make_shared<sf::RenderWindow>(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Raycaster");
    _renderWindow->setFramerateLimit(FPS);

    sf::View view(sf::FloatRect(0, 0, WINDOW_LOGICAL_WIDTH, WINDOW_LOGICAL_HEIGHT));
    _renderWindow->setView(view);

    _fps = std::make_unique<Fps>();

    _map = std::make_shared<Map>();
    _player = std::make_shared<Player>();

    _rays = std::vector<std::unique_ptr<Ray>>();
    for (int i = 0; i < WINDOW_LOGICAL_WIDTH; i++)
        _rays.push_back(std::make_unique<Ray>(WINDOW_LOGICAL_WIDTH, WINDOW_LOGICAL_HEIGHT));

    if (_renderWindow->isOpen())
        _isRunning = true;
}

void Raycaster::Loop()
{
    ProcessEvents();
    Update();
    Render();
}

bool Raycaster::GetIsRunning() const
{
    return _isRunning;
}

void Raycaster::ProcessEvents()
{
    while (_renderWindow->pollEvent(_event))
    {
        switch (_event.type)
        {
            case sf::Event::Closed:
                _isRunning = false;
                break;
            case sf::Event::KeyPressed:
                ProcessKey(_event.key, true);
                break;
            case sf::Event::KeyReleased:
                ProcessKey(_event.key, false);
                break;
            default:
                break;
        }
    }
}

void Raycaster::Update()
{
    _deltaTime = _deltaClock->restart().asSeconds();

    _player->Update(_deltaTime, _map);
    CastRays();
}

void Raycaster::Render()
{
    _renderWindow->clear(sf::Color(0, 0, 0, 0));

    RenderWalls();
    _map->Render(_renderWindow);
    RenderRays();
    _player->Render(_renderWindow);

    _fps->Render(_renderWindow);

    _renderWindow->display();
}

void Raycaster::ProcessKey(sf::Event::KeyEvent keyEvent, bool keyPressed)
{
    if (keyPressed)
    {
        switch (keyEvent.code)
        {
            case sf::Keyboard::Escape:
                _isRunning = false;
                break;

            case sf::Keyboard::Up:
            case sf::Keyboard::W:
                _player->walkDirection = +1;
                break;
            case sf::Keyboard::Down:
            case sf::Keyboard::S:
                _player->walkDirection = -1;
                break;

            case sf::Keyboard::Right:
            case sf::Keyboard::D:
                _player->turnDirection = +1;
                break;
            case sf::Keyboard::Left:
            case sf::Keyboard::A:
                _player->turnDirection = -1;
                break;

            default:
                break;
        }
    }
    else
    {
        switch (keyEvent.code)
        {
            case sf::Keyboard::Up:
            case sf::Keyboard::W:
            case sf::Keyboard::Down:
            case sf::Keyboard::S:
                _player->walkDirection = 0;
                break;

            case sf::Keyboard::Right:
            case sf::Keyboard::D:
            case sf::Keyboard::Left:
            case sf::Keyboard::A:
                _player->turnDirection = 0;
                break;

            default:
                break;
        }
    }
}

void Raycaster::CastRays()
{
    float rayAngle = _player->GetRotationAngle() - FOV / 2.0f;

    for (auto & _ray : _rays)
    {
        _ray->Cast(rayAngle, _player, _map);
        rayAngle += FOV / (float) WINDOW_LOGICAL_WIDTH;
    }
}

void Raycaster::RenderRays()
{
    for (auto & _ray : _rays)
        _ray->Render(_player, _renderWindow);
}

void Raycaster::RenderWalls()
{
    for (int i = 0; i < WINDOW_LOGICAL_WIDTH; i++)
        _rays[i]->RenderWall(i, FOV, _player, _renderWindow);
}
