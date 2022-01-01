//
// Created by rocve on 31/12/2021.
//

#include "Player.h"
#include <iostream>

Player::Player()
{
    _position = sf::Vector2f(480, 352);
}

void Player::Update(float deltaTime, const std::shared_ptr<Map>& map)
{
    _rotationAngle += turnDirection * ROTATION_SPEED * deltaTime;
    float moveStep = walkDirection * MOVE_SPEED * deltaTime;

    sf::Vector2f newPosition = sf::Vector2f (_position.x + cos(_rotationAngle) * moveStep,
                                             _position.y + sin(_rotationAngle) * moveStep);

    if (map->HasWallAt(newPosition))
        return;

    _position = newPosition;
}

void Player::Render(const std::shared_ptr<sf::RenderWindow>& renderWindow) const
{
    sf::RectangleShape playerRect;
    playerRect.setPosition(_position.x * MINIMAP_SCALE_FACTOR - PLAYER_SIZE / 2.0f,
                           _position.y * MINIMAP_SCALE_FACTOR - PLAYER_SIZE / 2.0f);
    playerRect.setSize(sf::Vector2f(PLAYER_SIZE, PLAYER_SIZE));
    playerRect.setFillColor(sf::Color(0,0, 255, 255));

    renderWindow->draw(playerRect);
}

sf::Vector2f Player::GetPosition()
{
    return _position;
}

float Player::GetRotationAngle() const
{
    return _rotationAngle;
}
