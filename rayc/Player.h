//
// Created by rocve on 31/12/2021.
//

#ifndef RAYC_PLAYER_H
#define RAYC_PLAYER_H

#include <memory>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "Utils.h"
#include "Map.h"

#define PLAYER_SIZE 2.0f
#define MOVE_SPEED 75.0f
#define ROTATION_SPEED (float) (40.0f * (PI / 180.0f))

class Player
{
public:
    Player();

    void Update(float deltaTime, const std::shared_ptr<Map>& map);
    void Render(const std::shared_ptr<sf::RenderWindow>& renderWindow) const;
    sf::Vector2f GetPosition();
    float GetRotationAngle() const;

    float turnDirection = 0;
    float walkDirection = 0;

private:
    sf::Vector2f _position;
    float _rotationAngle = PI / 2.0f;
};

#endif //RAYC_PLAYER_H
