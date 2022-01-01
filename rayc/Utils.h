//
// Created by rocve on 31/12/2021.
//

#ifndef RAYC_UTILS_H
#define RAYC_UTILS_H

#include <cmath>
#include <SFML/System.hpp>

#define PI 3.141593

class Utils
{
public:
    static float NormalizeAngle(float angle);
    static float DistanceBetweenPoints(sf::Vector2f v1, sf::Vector2f v2);
};

#endif //RAYC_UTILS_H
