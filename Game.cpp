#include "Game.h"
#include "SnakeBody.h"
#include <SFML/Graphics.hpp>
#include "GameMode.h"
#include <iostream>
#include <fstream>
#include <vector>

//laduje wyniki z pliku
void Game::LoadScores(std::vector<int>& V) {
    // Otwarcie pliku zawierającego wyniki
    std::ifstream file("../score.txt");

    // Pętla wczytująca wyniki z pliku do wektora V
    while (file.is_open()) {
        int score;
        while (file >> score) // Wczytanie kolejnych wyników z pliku
            V.push_back(score); // Dodanie wczytanego wyniku do wektora V

        file.close(); // Zamknięcie pliku po wczytaniu wszystkich wyników
    }
}
//zapisuje do pliku wyniki
void Game::SaveScores(std::vector<int>& V) {
    // Otwarcie pliku do zapisu wyników
    std::ofstream file("../score.txt");

    // Pętla zapisująca wyniki z wektora V do pliku
    while (file.is_open()) {
        for (const auto& score : V) {
            file << score << std::endl; // Zapis wyniku do pliku, każdy wynik w nowej linii
        }
        file.close(); // Zamknięcie pliku po zapisaniu wszystkich wyników
    }
}
//tworzy licznik punktow w lewym gornym rogu, najlepszy wynik w prawym gornym rogu, oraz czerwony prostokat oddzielajacy wyniki od planszy
void Game::ScoreBoard(sf::RenderWindow& win, std::vector<int>& V) const {
    // Załadowanie czcionki Arial
    sf::Font font;
    font.loadFromFile("../arial.ttf");

    // Tekst wyświetlający bieżący wynik (counter)
    sf::Text ScoreText;
    ScoreText.setFont(font);
    ScoreText.setString("Score: " + std::to_string(counter)); // Konwersja liczby na tekst
    ScoreText.setCharacterSize(24);
    ScoreText.setFillColor(sf::Color::White);
    ScoreText.setPosition(10, 10);

    // Tekst wyświetlający najlepszy wynik z wektora V
    sf::Text TopScoreText;
    TopScoreText.setFont(font);
    TopScoreText.setString("Top Score: " + std::to_string(V.front())); // Konwersja liczby na tekst
    TopScoreText.setCharacterSize(24);
    TopScoreText.setFillColor(sf::Color::White);
    TopScoreText.setPosition(425, 10);

    // Pasek na górze okna, na którym wyświetlany jest wynik
    sf::RectangleShape Bar(sf::Vector2f(600,50));
    Bar.setFillColor(sf::Color::Red);
    Bar.setPosition(0, 0);

    // Rysowanie paska z wynikami na ekranie gry
    win.draw(Bar);

    // Rysowanie tekstu z bieżącym wynikiem
    win.draw(ScoreText);

    // Rysowanie tekstu z najlepszym wynikiem
    win.draw(TopScoreText);
}

//pokazuje na ekranie top 10 najlepszych wynikow
void Game::TopScore(sf::RenderWindow& win, std::vector<int>& V) {
    // Załadowanie czcionki Arial
    sf::Font font;
    font.loadFromFile("../arial.ttf");

    // Sortowanie wektora V malejąco, aby uzyskać najlepsze wyniki na początku
    std::sort(V.begin(), V.end(), std::greater<>());

    // Tekst tytułowy "Top 10 Scores"
    sf::Text title;
    title.setFont(font);
    title.setString("Top 10 Scores");
    title.setCharacterSize(30);
    title.setFillColor(sf::Color::White);
    title.setPosition(200, 50);
    win.draw(title); // Rysowanie tytułu na ekranie gry

    // Wyświetlenie 10 najlepszych wyników
    for (unsigned int i = 0; i < V.size() && i < 10; i++) {
        // Tekst z numerem miejsca i wynikiem
        sf::Text scoreText;
        scoreText.setFont(font);
        scoreText.setString(std::to_string(i + 1) + ". " + std::to_string(V[i])); // Numeracja od 1, a nie od 0
        scoreText.setCharacterSize(24);
        scoreText.setFillColor(sf::Color::White);
        scoreText.setPosition(275, 100 + i * 30); // Ustawienie pozycji tekstu na ekranie
        win.draw(scoreText); // Rysowanie tekstu z wynikiem na ekranie gry
    }
}

//dodaje wynik do wektora przechowujacego wyniki
void Game::Add(int liczba, std::vector<int>& V)
{
    // Dodaj nową liczbę (wynik) na koniec wektora
    V.push_back(liczba);

    // Sortuj wektor malejąco, aby zachować wyniki w kolejności malejącej
    std::sort(V.begin(), V.end(), std::greater<>());

    // Jeśli liczba wyników przekracza 10, usuń najmniejszy wynik (ostatni element wektora)
    if (V.size() > 10)
        V.pop_back();
}
//odpowiada za logike rozgrywki
void Game::Render(Gamemode mode) {
    // Tworzenie głównego okna gry
    sf::RenderWindow win(sf::VideoMode(600, 400), "Snake");

    // Inicjalizacja wektora przechowującego wyniki
    std::vector<int> V;

    // Nazwa pliku, w którym przechowywane są wyniki
    const std::string scoreFile = "scores.txt";

    // Wczytanie wyników z pliku do wektora V
    LoadScores(V);

    // Inicjalizacja obiektu SnakeBody
    SnakeBody B;
    bool run = true;
    // Ustalenie prędkości gry w zależności od wybranego poziomu trudności
    int speed;
    if (mode == Easy)
        speed = 45;
    else
        speed = 25;

    // Pętla główna gry
    while (win.isOpen()) {
        sf::Event event{};
        while (win.pollEvent(event)) {
            // Obsługa zamknięcia okna gry
            if (event.type == sf::Event::Closed)
                win.close();
        }

        // Sprawdzenie czy gra nadal trwa
        if (run)
        {
            // Ruch węża
            B.move();

            // Sprawdzenie czy wąż zjadł jedzenie
            if (B.Eat(mode))
                counter++;

            // Sprawdzenie warunku wygranej
            if (B.win())
            {
                // Dodanie wyniku do listy i zapisanie wyników do pliku
                Add(counter, V);
                SaveScores(V);

                // Zamknięcie okna gry i otwarcie okna informującego o wygranej
                win.close();
                run = false;
                sf::RenderWindow window(sf::VideoMode(600, 400), "Koniec");
                while(window.isOpen())
                {
                    sf::Event event{};
                    while (window.pollEvent(event)) {
                        if (event.type == sf::Event::Closed)
                            window.close();
                    }

                    sf::Font font;
                    font.loadFromFile("../arial.ttf");
                    sf::Text title;
                    title.setFont(font);
                    title.setString("Wygrales");
                    title.setCharacterSize(30);
                    title.setFillColor(sf::Color::White);
                    title.setPosition(225, 100);
                    window.clear();
                    window.draw(title);
                    window.display();
                }
            }

            // Sprawdzenie warunku przegranej
            if (B.SnakeCollision(mode))
            {
                // Dodanie wyniku do listy i zapisanie wyników do pliku
                Add(counter, V);
                SaveScores(V);

                // Zamknięcie okna gry i otwarcie okna informującego o przegranej
                run = false;
                sf::RenderWindow window(sf::VideoMode(600, 400), "Koniec");
                while(window.isOpen())
                {
                    sf::Event event{};
                    while (window.pollEvent(event)) {
                        if (event.type == sf::Event::Closed)
                            window.close();
                    }

                    sf::Font font;
                    font.loadFromFile("../arial.ttf");
                    sf::Text title;
                    title.setFont(font);
                    title.setString("Przegrales");
                    title.setCharacterSize(30);
                    title.setFillColor(sf::Color::White);
                    title.setPosition(225, 100);
                    window.clear();
                    window.draw(title);
                    window.display();
                }
            }

            // Czyszczenie okna gry
            win.clear();

            // Rysowanie ciała węża
            B.body(win);

            // Rysowanie jedzenia
            B.Food(win);

            // Jeśli wybrano poziom trudny, rysowanie przeszkód
            if (mode == Hard)
                B.Obstacles(win);

            // Wyświetlanie wyników na ekranie gry
            ScoreBoard(win, V);

            // Wyświetlenie okna gry
            win.display();

            // Opóźnienie przed kolejną iteracją pętli gry
            sf::sleep(sf::milliseconds(speed));
        }
        else
        {
            // Po zakończeniu gry, wyświetlenie najlepszych wyników
            win.clear();
            TopScore(win, V);
            win.display();

            // Oczekiwanie na zamknięcie okna wyników
            while (win.isOpen()) {
                sf::Event event;
                while (win.pollEvent(event)) {
                    if (event.type == sf::Event::Closed)
                        win.close();
                }
            }
        }
    }
}