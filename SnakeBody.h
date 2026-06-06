#ifndef SNAKEBODY_H
#define SNAKEBODY_H

#include <SFML/Graphics.hpp>
#include<vector>
#include"GameMode.h"
#include <unordered_map>
#include <algorithm>

struct position{
    int x, y;


};

class SnakeBody {
    std::vector<position> S;
    sf::Vector2i Foodpos;
    std::vector<std::pair<int, int>> Obstaclepos;
    int x = 200, y = 200;
    int Obstaclex, Obstacley;
    int xchange = 0, ychange = 0;
    bool LR = false, UD = false;


public:
    SnakeBody();
    void body(sf::RenderWindow &window);
    void move();
    bool Eat(Gamemode mode);
    void Food(sf::RenderWindow &win) const;
    bool SnakeCollision(Gamemode mode);
    void Obstacles(sf::RenderWindow &window);
    bool win();

};

#endif // SNAKEBODY_H
