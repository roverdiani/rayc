//
// Created by rocve on 31/12/2021.
//

#include "Map.h"
#include <iostream>

bool Map::HasWallAt(sf::Vector2f position)
{
    float maxX = MAP_NUM_COLS * TILE_SIZE;
    float maxY = MAP_NUM_ROWS * TILE_SIZE;
    if (position.x < 0 || position.x >= maxX || position.y < 0 || position.y >= maxY)
        return true;

    int gridIndexX = (int) floor(position.x / TILE_SIZE);
    int gridIndexY = (int) floor(position.y / TILE_SIZE);

    return _data[gridIndexY][gridIndexX] != 0;
}

void Map::Render(const std::shared_ptr<sf::RenderWindow> &renderWindow)
{
    sf::Color tileColor;
    sf::RectangleShape tileRect;

    for (int y = 0; y < MAP_NUM_ROWS; y++)
        for (int x = 0; x < MAP_NUM_COLS; x++)
        {
            if (_data[y][x] == 1)
                tileColor = sf::Color(127, 127, 127, 255);
            else
                tileColor = sf::Color(255, 255, 255, 255);

            tileRect.setPosition(sf::Vector2f((float) x * TILE_SIZE * MINIMAP_SCALE_FACTOR,
                                              (float) y * TILE_SIZE * MINIMAP_SCALE_FACTOR));
            tileRect.setSize(sf::Vector2f(TILE_SIZE * MINIMAP_SCALE_FACTOR,
                                          TILE_SIZE * MINIMAP_SCALE_FACTOR));
            tileRect.setFillColor(tileColor);
            renderWindow->draw(tileRect);
        }
}
