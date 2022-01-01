//
// Created by rocve on 31/12/2021.
//

#include "Utils.h"

float Utils::NormalizeAngle(float angle)
{
    float normalizedAngle = remainderf(angle, 2 * PI);

    if (normalizedAngle < 0)
        normalizedAngle = 2 * (float) PI + normalizedAngle;

    return normalizedAngle;
}

float Utils::DistanceBetweenPoints(sf::Vector2f v1, sf::Vector2f v2)
{
    return sqrtf((v2.x - v1.x) * (v2.x - v1.x) + (v2.y - v1.y) * (v2.y - v1.y));
}
