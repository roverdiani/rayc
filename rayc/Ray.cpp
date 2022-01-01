//
// Created by rocve on 31/12/2021.
//

#include "Ray.h"

void Ray::Cast(float angle, const std::shared_ptr<Player>& player, std::shared_ptr<Map>& map)
{
    _normalizedAngle = Utils::NormalizeAngle(angle);

    _isFacingDown = _normalizedAngle > 0 && _normalizedAngle < PI;
    _isFacingRight = _normalizedAngle < 0.5f * PI || _normalizedAngle > 1.5f * PI;

    bool foundHorizontalWallHit = CheckHorizontalIntersection(player->GetPosition(), map, &_horizontalWallHit);
    bool foundVerticalWallHit = CheckVerticalIntersection(player->GetPosition(), &_verticalWallHit, map);

    float horizontalHitDistance = foundHorizontalWallHit ? Utils::DistanceBetweenPoints(player->GetPosition(), _horizontalWallHit) : FLT_MAX;
    float verticalHitDistance = foundVerticalWallHit ? Utils::DistanceBetweenPoints(player->GetPosition(), _verticalWallHit) : FLT_MAX;

    if (verticalHitDistance < horizontalHitDistance)
    {
        _wallHitPos.x = _verticalWallHit.x;
        _wallHitPos.y = _verticalWallHit.y;
        _distance = verticalHitDistance;
        _wasHitVertical = true;
    }
    else
    {
        _wallHitPos.x = _horizontalWallHit.x;
        _wallHitPos.y = _horizontalWallHit.y;
        _distance = horizontalHitDistance;
        _wasHitVertical = false;
    }
}

bool Ray::CheckHorizontalIntersection(sf::Vector2f playerPos, std::shared_ptr<Map> &map, sf::Vector2f *horizontalWallHit)
{
    _intercept.y = floorf(playerPos.y / TILE_SIZE) * TILE_SIZE + (_isFacingDown ? TILE_SIZE : 0.0f);
    _intercept.x = playerPos.x + (_intercept.y - playerPos.y) / tanf(_normalizedAngle);

    _step.y = TILE_SIZE * (!_isFacingDown ? -1.0f : 1.0f);
    _step.x = TILE_SIZE / tanf(_normalizedAngle);
    _step.x *= !_isFacingRight && _step.x > 0 ? -1 : 1;
    _step.x *= _isFacingRight && _step.x < 0 ? -1 : 1;

    while (_intercept.x >= 0 && _intercept.x <= MAP_NUM_COLS * TILE_SIZE && _intercept.y >= 0 && _intercept.y <= MAP_NUM_ROWS * TILE_SIZE)
    {
        if (map->HasWallAt(sf::Vector2f(_intercept.x, _intercept.y - (!_isFacingDown ? 1.0f : 0.0f))))
        {
            horizontalWallHit->x = _intercept.x;
            horizontalWallHit->y = _intercept.y;
            return true;
        }

        _intercept.x += _step.x;
        _intercept.y += _step.y;
    }

    return false;
}

bool Ray::CheckVerticalIntersection(sf::Vector2f playerPos, sf::Vector2f *verticalWallHit, std::shared_ptr<Map> &map)
{
    _intercept.x = floorf(playerPos.x / TILE_SIZE) * TILE_SIZE + (_isFacingRight ? TILE_SIZE : 0.0f);
    _intercept.y = playerPos.y + (_intercept.x - playerPos.x) * tanf(_normalizedAngle);

    _step.x = TILE_SIZE * (!_isFacingRight ? -1.0f : 1.0f);
    _step.y = TILE_SIZE * tanf(_normalizedAngle);
    _step.y *= !_isFacingDown && _step.y > 0 ? -1.0f : 1.0f;
    _step.y *= _isFacingDown && _step.y < 0 ? -1.0f : 1.0f;

    while (_intercept.x >= 0 && _intercept.x < MAP_NUM_COLS * TILE_SIZE && _intercept.y >= 0 && _intercept.y <= MAP_NUM_ROWS * TILE_SIZE)
    {
        if (map->HasWallAt(sf::Vector2f(_intercept.x - (!_isFacingRight ? 1.0f : 0.0f), _intercept.y)))
        {
            verticalWallHit->x = _intercept.x;
            verticalWallHit->y = _intercept.y;
            return true;
        }

        _intercept.x += _step.x;
        _intercept.y += _step.y;
    }

    return false;
}

void Ray::Render(const std::shared_ptr<Player> &player, const std::shared_ptr<sf::RenderWindow>& renderWindow) const
{
    sf::Color rayColor= sf::Color(255, 0, 0, 255);
    sf::VertexArray vArray = sf::VertexArray(sf::Lines, 2);
    vArray.append(sf::Vertex(sf::Vector2f(player->GetPosition().x * MINIMAP_SCALE_FACTOR,
                                          player->GetPosition().y * MINIMAP_SCALE_FACTOR), rayColor));
    vArray.append(sf::Vertex(sf::Vector2f(_wallHitPos.x * MINIMAP_SCALE_FACTOR,
                                          _wallHitPos.y * MINIMAP_SCALE_FACTOR), rayColor));
    renderWindow->draw(vArray);
}

void Ray::RenderWall(int x, float fovAngle, const std::shared_ptr<Player> &player,
                     const std::shared_ptr<sf::RenderWindow>& renderWindow) const
{
    float correctWallDistance = _distance * cosf(_normalizedAngle - player->GetRotationAngle());
    float distanceToProjectionPlane = _windowLogicalWidth * 0.5f / tanf(fovAngle * 0.5f);
    float wallStripHeight = TILE_SIZE / correctWallDistance * distanceToProjectionPlane;

    float wallTopPixel = _windowLogicalHeight * 0.5f - wallStripHeight * 0.5f;
    wallTopPixel = wallTopPixel < 0 ? 0 : wallTopPixel;

    float wallBottomPixel = _windowLogicalHeight * 0.5f + wallStripHeight * 0.5f;
    wallBottomPixel = wallBottomPixel > _windowLogicalHeight ? _windowLogicalHeight : wallBottomPixel;

    // Draw ceiling
    sf::RectangleShape ceilingRect;
    ceilingRect.setPosition(sf::Vector2f(x, 0));
    ceilingRect.setSize(sf::Vector2f(1, wallTopPixel));
    ceilingRect.setFillColor(sf::Color(255, 127, 0, 255));
    renderWindow->draw(ceilingRect);

    // Draw wall
    sf::Color wallColor = _wasHitVertical ? sf::Color(255, 255, 255, 255)
            : sf::Color(127, 127, 127, 255);
    sf::RectangleShape wallRect;
    wallRect.setPosition(sf::Vector2f((float) x, wallTopPixel));
    wallRect.setSize(sf::Vector2f(1, wallStripHeight));
    wallRect.setFillColor(wallColor);
    renderWindow->draw(wallRect);

    // Draw floor
    sf::RectangleShape floorRect;
    floorRect.setPosition(sf::Vector2f((float) x, wallBottomPixel));
    floorRect.setSize(sf::Vector2f(1, _windowLogicalHeight - wallBottomPixel));
    floorRect.setFillColor(sf::Color(255, 255, 0, 255));
    renderWindow->draw(floorRect);
}

Ray::Ray(int windowLogicalWidth, int windowLogicalHeight)
{
    _windowLogicalWidth = windowLogicalWidth;
    _windowLogicalHeight = windowLogicalHeight;
}
