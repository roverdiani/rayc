//
// Created by rocve on 31/12/2021.
//

#ifndef RAYC_RAY_H
#define RAYC_RAY_H

#include <memory>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "Player.h"
#include "Map.h"
#include "Utils.h"

class Ray
{
public:
    Ray(int windowLogicalWidth, int windowLogicalHeight);

    void Cast(float angle, const std::shared_ptr<Player>& player, std::shared_ptr<Map>& map);
    void Render(const std::shared_ptr<Player> &player, const std::shared_ptr<sf::RenderWindow>& renderWindow) const;
    void RenderWall(int x, float fovAngle, const std::shared_ptr<Player> &player,
                    const std::shared_ptr<sf::RenderWindow>& renderWindow) const;

private:
    bool CheckHorizontalIntersection(sf::Vector2f playerPos, std::shared_ptr<Map> &map, sf::Vector2f *horizontalWallHit);
    bool CheckVerticalIntersection(sf::Vector2f playerPos, sf::Vector2f *verticalWallHit, std::shared_ptr<Map> &map);

    int _windowLogicalWidth = 0;
    int _windowLogicalHeight = 0;

    float _normalizedAngle = 0;
    float _distance = 0;
    bool _wasHitVertical = false;
    bool _isFacingDown = false;
    bool _isFacingRight = false;

    sf::Vector2f _wallHitPos{};
    sf::Vector2f _horizontalWallHit{};
    sf::Vector2f _verticalWallHit{};

    sf::Vector2f _intercept{};
    sf::Vector2f _step{};
};

#endif //RAYC_RAY_H
