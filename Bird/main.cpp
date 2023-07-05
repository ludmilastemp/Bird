#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <chrono>

int y_bird = 100; int x_backGround = 0; int speed = 7; int location_pass[4]; int count = 0;

void Bird(sf::RenderWindow& window, sf::Image& img) {
    sf::ConvexShape bird(4);
    bird.setPoint(0, sf::Vector2f(300, y_bird));
    bird.setPoint(1, sf::Vector2f(300 + 20, y_bird));
    bird.setPoint(2, sf::Vector2f(300 + 20, y_bird + 20));
    bird.setPoint(3, sf::Vector2f(300, y_bird + 20));
    bird.setFillColor(sf::Color::Blue);
    window.draw(bird);
}

void Event(sf::RenderWindow& window, sf::Image& img) {
    int i = 0; location_pass[0] = 300;
    location_pass[1] = 350;
    location_pass[2] = 400;
    location_pass[3] = 300;
    auto beginbird = std::chrono::high_resolution_clock::now();
    auto endbird = std::chrono::high_resolution_clock::now();
    auto timebird = std::chrono::duration_cast<std::chrono::microseconds>(endbird - beginbird);
    sf::Font font;
    if (!font.loadFromFile("D:/Proga/Bird/Raleway-Regular.ttf"));
    sf::Texture backGround;
    backGround.loadFromFile("D:\\Proga\\Bird\\x64\\Debug\\backGround.png");
    sf::Texture pass;
    pass.loadFromFile("D:\\Proga\\Bird\\x64\\Debug\\15.png");
    sf::Sprite sprite_backGround;
    sprite_backGround.setTexture(backGround);
    sf::Sprite sprite_pass[7];
    for (int i = 1; i < 4; ++i) sprite_pass[i].setTexture(pass);
    for (int i = 4; i < 7; ++i) sprite_pass[i].setTexture(pass);
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();
            else if (event.type == sf::Event::MouseButtonPressed &&
                event.mouseButton.button == sf::Mouse::Left) {
                i = 20;
            }
        }
        window.clear();
        if (x_backGround < -1600) x_backGround = 0;
        sprite_backGround.setPosition(x_backGround, 0);
        window.draw(sprite_backGround);
        if (location_pass[0] > 220 - 500 && location_pass[0] < 300 - 500) {
            if (y_bird > location_pass[1] || y_bird < location_pass[1] - 245) window.close();
        }
        if (location_pass[0] < -650) {
            location_pass[0] += 500;
            location_pass[1] = location_pass[2];
            location_pass[2] = location_pass[3];
            location_pass[3] = rand() % 400 + 230;
        }
        for (int i = 1; i < 4; ++i) {
            sprite_pass[i].setPosition(location_pass[0] + 500 * i, location_pass[i] - 750);
            sprite_pass[i + 3].setPosition(location_pass[0] + 500 * i, location_pass[i]);
            window.draw(sprite_pass[i]); //высота 245
            window.draw(sprite_pass[i + 3]);
        }
        if (timebird.count() > 20000) {
            if (i > 0) {
                y_bird -= speed; --i;
            }
            else {
                y_bird += speed;
            }
            x_backGround -= speed - 4;
            location_pass[0] -= speed - 4;
            beginbird = std::chrono::high_resolution_clock::now();
        }
        endbird = std::chrono::high_resolution_clock::now();
        timebird = std::chrono::duration_cast<std::chrono::microseconds>(endbird - beginbird);
        Bird(window, img);
        /*
        sf::Text text;
        text.setFont(font);
        text.setString(std::to_string(count));
        text.setCharacterSize(35);
        text.setFillColor(sf::Color::Black);
        text.setStyle(sf::Text::Bold);
        text.setPosition(500, 40);
        */
        //window.draw(text);
        window.display();
    }
}

int main() {
    sf::RenderWindow window(sf::VideoMode(1000, 700), "Nice game!");
    sf::Image img;
    img.create(1000, 700, sf::Color::White);
    Event(window, img);
    return 0;
}