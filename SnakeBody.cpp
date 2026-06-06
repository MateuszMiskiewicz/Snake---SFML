#include "SnakeBody.h"
#include<SFML/Graphics.hpp>
#include<cstdlib>
#include<ctime>
#include"GameMode.h"
#include <unordered_map>
#include <algorithm>

// w konstruktorze generowane jest poczatkowe miejsce weza,
// jedzenia i przeszkod, w takich sposob by ze soba nie kolidowaly
SnakeBody::SnakeBody() {

    S.push_back({x,y});
    srand(time(nullptr));
    Foodpos.x = ((rand()%600 - 10) + 5) / 10 * 10;
    Foodpos.y = (rand()%(400 - 60) + 5) / 10 * 10 + 50;

    for(int i = 0; i < 10; i ++)
    {
        Obstaclex = ((rand()%600 - 10) + 5) / 10 * 10;
        Obstacley = (rand()%(400 - 60) + 5) / 10 * 10 + 50;
        if((Obstaclex == Foodpos.x and Obstacley == Foodpos.y) or (Obstaclex == x and Obstacley == y))
        {
            while(true)
            {
                Obstaclex = ((rand()%600 - 10) + 5) / 10 * 10;
                Obstacley = (rand()%(400 - 60) + 5) / 10 * 10 + 50;

                if((Obstaclex != Foodpos.x or Obstacley != Foodpos.y) or (Obstaclex != x or Obstacley != y))
                {
                    Obstaclepos.push_back({Obstaclex,Obstacley});
                    break;
                }

            }
        }

            Obstaclepos.push_back({Obstaclex,Obstacley});

    }
}
//tworzy weza na planszy
void SnakeBody::body(sf::RenderWindow &window) {
    // Iteracja przez każdy segment ciała węża
    for (auto &i : S) {
        // Tworzenie prostokąta reprezentującego segment ciała węża
        sf::RectangleShape bodyS(sf::Vector2f(10, 10));

        // Ustawienie koloru segmentu na niebieski
        bodyS.setFillColor(sf::Color::Blue);

        // Ustawienie pozycji segmentu na współrzędne segmentu w ciele węża
        bodyS.setPosition(i.x, i.y);

        // Rysowanie segmentu ciała węża w oknie
        window.draw(bodyS);
    }
}

//odpowiada za ruch weza
void SnakeBody::move() {
    // Sprawdzenie naciśniętych klawiszy i zmiany kierunku węża
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !LR) {
        xchange = -10;  // Zmiana współrzędnej x o -10 (przesunięcie w lewo)
        ychange = 0;    // Brak zmiany współrzędnej y (ruch w poziomie)

        LR = true;      // Ustawienie flagi LR na true (wąż skręca w lewo)
        UD = false;     // Ustawienie flagi UD na false (wąż nie skręca w górę ani w dół)
        sf::sleep(sf::milliseconds(30));  // Oczekiwanie 30 milisekund
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !LR) {
        xchange = 10;   // Zmiana współrzędnej x o 10 (przesunięcie w prawo)
        ychange = 0;    // Brak zmiany współrzędnej y (ruch w poziomie)

        LR = true;      // Ustawienie flagi LR na true (wąż skręca w prawo)
        UD = false;     // Ustawienie flagi UD na false (wąż nie skręca w górę ani w dół)
        sf::sleep(sf::milliseconds(30));  // Oczekiwanie 30 milisekund
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !UD) {
        xchange = 0;    // Brak zmiany współrzędnej x (ruch w pionie)
        ychange = -10;  // Zmiana współrzędnej y o -10 (przesunięcie w górę)

        UD = true;      // Ustawienie flagi UD na true (wąż skręca w górę)
        LR = false;     // Ustawienie flagi LR na false (wąż nie skręca w lewo ani w prawo)
        sf::sleep(sf::milliseconds(30));  // Oczekiwanie 30 milisekund
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && !UD) {
        xchange = 0;    // Brak zmiany współrzędnej x (ruch w pionie)
        ychange = 10;   // Zmiana współrzędnej y o 10 (przesunięcie w dół)

        UD = true;      // Ustawienie flagi UD na true (wąż skręca w dół)
        LR = false;     // Ustawienie flagi LR na false (wąż nie skręca w lewo ani w prawo)
        sf::sleep(sf::milliseconds(30));  // Oczekiwanie 30 milisekund
    }

    // Aktualizacja pozycji głowy węża
    x += xchange;
    y += ychange;

    // Usunięcie ostatniego segmentu ciała węża i dodanie nowej głowy
    S.pop_back();
    S.insert(S.begin(), {x, y});
}

//Tworzy jedzenie na planszy
void SnakeBody::Food(sf::RenderWindow &window) const {
    // Tworzenie prostokąta reprezentującego jedzenie dla węża
    sf::RectangleShape bodyS(sf::Vector2f(10, 10));

    // Ustawienie koloru jedzenia na zielony
    bodyS.setFillColor(sf::Color::Green);

    // Ustawienie pozycji jedzenia na współrzędne przechowywane w Foodpos
    bodyS.setPosition(Foodpos.x, Foodpos.y);

    // Rysowanie jedzenia w oknie gry
    window.draw(bodyS);
}

bool SnakeBody::Eat(Gamemode mode) {
    // Sprawdzenie, czy głowa węża trafila na  jedzenie
    if (S.front().x == Foodpos.x && S.front().y == Foodpos.y) {
        // Dodanie nowego segmentu do końca wektora reprezentującego ciało węża
        S.push_back({S.back().x + 10, S.back().y});

        // Losowanie nowej pozycji dla jedzenia
        for (unsigned int i = 1; i < S.size(); ++i) {
            while (true) {
                // Losowanie nowej pozycji Foodpos, która nie koliduje z ciałem węża
                Foodpos.x = ((rand() % 600 - 10) + 5) / 10 * 10;
                Foodpos.y = (rand() % (400 - 60) + 5) / 10 * 10 + 50;

                // Sprawdzenie, czy nowa pozycja jedzenia nie koliduje z żadnym segmentem ciała węża
                if (S[i].x != Foodpos.x && S[i].y != Foodpos.y)
                    break;
            }
        }

        return true; // Zwrócenie true, jeśli wąż zjadł jedzenie
    }

    // Jeśli tryb gry jest ustawiony na Hard, sprawdzanie kolizji z przeszkodami
    if (mode == Hard) {
        for (unsigned int i = 0; i < Obstaclepos.size(); ++i) {
            if (Obstaclepos[i].first == Foodpos.x && Obstaclepos[i].second == Foodpos.y) {
                // Ponowne losowanie nowej pozycji jedzenia, jeśli nowa pozycja koliduje z przeszkodą
                while (true) {
                    Foodpos.x = ((rand() % 600 - 10) + 5) / 10 * 10;
                    Foodpos.y = (rand() % (400 - 60) + 5) / 10 * 10 + 50;

                    // Sprawdzenie, czy nowa pozycja jedzenia nie koliduje z żadną przeszkodą
                    if (Obstaclepos[i].first != Foodpos.x && Obstaclepos[i].second != Foodpos.y)
                        break;
                }
            }
        }
    }

    return false; // Zwrócenie false, jeśli wąż nie zjadł jedzenia
}


//sprawdza kolizje weza ze soba, czy waz wyszedl poza plansze oraz w trybie Hard czy waz nie trafil w przeszkode
bool SnakeBody::SnakeCollision(Gamemode mode) {
    // Sprawdzenie kolizji głowy węża z jego ciałem
    for (unsigned int i = 1; i < S.size(); ++i) {
        if (S[0].x == S[i].x && S[0].y == S[i].y)
            return true; // Zwrócenie true, jeśli głowa węża koliduje z którąś częścią swojego ciała
    }

    // Sprawdzenie kolizji głowy węża z krawędziami okna gry
    if (S[0].x > 600 || S[0].x < 0 || S[0].y > 400 || S[0].y < 50)
        return true; // Zwrócenie true, jeśli głowa węża koliduje z krawędziami okna gry

    // Jeśli tryb gry jest ustawiony na Hard, sprawdzenie kolizji głowy węża z przeszkodami
    if (mode == Hard) {
        for (int i = 0; i < 10; ++i) {
            if (S[0].x == Obstaclepos[i].first && S[0].y == Obstaclepos[i].second)
                return true; // Zwrócenie true, jeśli głowa węża koliduje z jakąś przeszkodą
        }
    }

    return false; // Zwrócenie false, jeśli nie wystąpiła kolizja
}

//Tworzy na planszy 10 przeszkod
void SnakeBody::Obstacles(sf::RenderWindow &window) {
    // Rysowanie przeszkód na ekranie gry
    for (int i = 0; i < 10; ++i) {
        // Tworzenie prostokąta reprezentującego przeszkodę
        sf::RectangleShape Obstacle(sf::Vector2f(10, 10));

        // Ustawienie koloru przeszkody na magentę
        Obstacle.setFillColor(sf::Color::Magenta);

        // Ustawienie pozycji przeszkody na współrzędne przechowywane w Obstaclepos
        Obstacle.setPosition(Obstaclepos[i].first, Obstaclepos[i].second);

        // Rysowanie przeszkody w oknie gry
        window.draw(Obstacle);
    }
}
//sprawdzenie czy wygrana
bool SnakeBody::win()
{
   if(S.size() == (600*350)/10)//jesli rozmiar weza nie pozwala na dalsze generowanie jablka to wygrana
       return true;
   return false;

}
