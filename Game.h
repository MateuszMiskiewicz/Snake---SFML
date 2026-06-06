
#ifndef SNAKE_GAME_H
#define SNAKE_GAME_H
#include<SFML/Graphics.hpp>
#include"GameMode.h"
#include<vector>


class Game {
 int counter = 0;


public:
     static void Add(int liczba, std::vector<int> &V);
     void Render(Gamemode mode);
     void ScoreBoard(sf::RenderWindow& window, std::vector<int>& V) const;
     static void LoadScores(std::vector<int>& V);
     static void SaveScores(std::vector<int>& V);
     static void TopScore(sf::RenderWindow& window, std::vector<int> &V);

};


#endif //SNAKE_GAME_H
