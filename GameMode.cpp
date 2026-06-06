
#include "GameMode.h"
#include<SFML/Graphics.hpp>
#include"Game.h"

void GameMode::Mode() {
    Game g;

    // Ustawienie parametrów okna gry
    sf::VideoMode videomode(600, 400);
    sf::String Title("Wybierz poziom trudnosci");
    sf::Uint32 style = sf::Style::Titlebar | sf::Style::Close;
    sf::RenderWindow window(videomode, Title, style);

    // Ładowanie czcionki i ustawienie tytułu
    sf::Font font;
    font.loadFromFile("../Arial.ttf");
    sf::Text title;
    title.setFont(font);
    title.setString("Wybierz poziom trudnosci:");
    title.setCharacterSize(30);
    title.setFillColor(sf::Color::White);
    title.setPosition(125, 20);

    // Tworzenie obiektów tekstowych dla opcji poziomów trudności
    sf::Text easyText("Latwy", font, 50);
    sf::Text mediumText("Sredni", font, 50);
    sf::Text hardText("Trudny", font, 50);

    // Ustawienie pozycji opcji tekstowych
    easyText.setPosition(225, 75);
    mediumText.setPosition(225, 150);
    hardText.setPosition(225, 225);

    // Tworzenie prostokątów dla każdej opcji, aby je wyróżnić
    sf::RectangleShape r1(sf::Vector2f(200, 50));
    r1.setPosition(193, 86);
    r1.setFillColor(sf::Color::Transparent);
    r1.setOutlineThickness(5);
    r1.setOutlineColor(sf::Color::Red);

    sf::RectangleShape r2(sf::Vector2f(200, 50));
    r2.setPosition(193, 160);
    r2.setFillColor(sf::Color::Transparent);
    r2.setOutlineThickness(5.f);
    r2.setOutlineColor(sf::Color::Red);

    sf::RectangleShape r3(sf::Vector2f(200, 50));
    r3.setPosition(193, 235);
    r3.setFillColor(sf::Color::Transparent);
    r3.setOutlineThickness(5.f);
    r3.setOutlineColor(sf::Color::Red);

    // Główna pętla gry
    while (window.isOpen()) {
        sf::Event event;
        // Przetwarzanie zdarzeń
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close(); // Zamknięcie okna, gdy zostanie naciśnięty przycisk zamknięcia

            if (event.type == sf::Event::MouseButtonPressed) {
                int x = event.mouseButton.x;
                int y = event.mouseButton.y;
                if (event.mouseButton.button == sf::Mouse::Left) {
                    // Sprawdzanie, czy kliknięcie było w obszarze jednej z opcji trudności
                    if (x >= 192 && x <= 393 && y >= 86 && y <= 146) {
                        window.close();
                        g.Render(Easy); // Uruchomienie gry na poziomie łatwym
                    }
                    else if (x >= 192 && x <= 393 && y >= 160 && y <= 220) {
                        window.close();
                        g.Render(Normal); // Uruchomienie gry na poziomie średnim
                    }
                    else if (x >= 192 && x <= 393 && y >= 235 && y <= 295) {
                        window.close();
                        g.Render(Hard); // Uruchomienie gry na poziomie trudnym
                    }
                }
            }
        }

        // Czyszczenie okna i rysowanie wszystkich elementów
        window.clear();
        window.draw(title);
        window.draw(easyText);
        window.draw(mediumText);
        window.draw(hardText);
        window.draw(r1);
        window.draw(r2);
        window.draw(r3);
        window.display();
    }
}


