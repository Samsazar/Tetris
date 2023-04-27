#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "time.h"
#include "field.h"
// https://gitlab.com/Zedespook/sfml-tetris/-/blob/master/src/main.cpp
using namespace sf;




// Main function for running the game.
int main()
{

    int width = 10, height = 20;
    Field field(width, height);
    Field field1(width, height);
    Figure a, b;
    b = a;
    // Generates a random seed for the session.
    srand(time(0));

    // The main render for the window.
    RenderWindow window(VideoMode(320, 480), "Tetris Clone");

    // This is the tile for the tetris block.
    RectangleShape shape(Vector2f(18.f, 18.f));
    shape.setFillColor(Color::Blue);


    // Shape modifiers.
    int dx = 0;
    bool rotate = false;
    int color = 1;

    int padding = 50;


    // Game clock variables.
    float timer = 0.f, delay = 0.3f;
    static Clock clock;

    int score = 0.f;

    static Font font;
    if (!font.loadFromFile("../font.ttf"))
//        std::cout << "Error loading font file." << std::endl;
        int a;
    static Text scoreTextLabel;
    scoreTextLabel.setFont(font);
    scoreTextLabel.setString("Cleared:");
    scoreTextLabel.setCharacterSize(20);
    scoreTextLabel.setFillColor(Color::White);

    static Text scoreLabel;
    scoreLabel.setFont(font);
    scoreLabel.setCharacterSize(24);
    scoreLabel.setFillColor(Color::White);

    bool FINAL = false;

    int aboba = 0;

    while (window.isOpen()) {
        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        timer += time;

        Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
                case Event::Closed:
                    window.close();
                    break;

                case Event::KeyPressed:

                    switch (event.key.code) {
                        case Keyboard::Up:
                            rotate = true;
                            break;
                        case Keyboard::Left:
                            dx = -1;
                            break;
                        case Keyboard::Right:
                            dx = 1;
                            break;

                        default:
                            break;
                    }
                    break;

                default:
                    break;
            }
        }

        if (Keyboard::isKeyPressed(Keyboard::Down))
            delay = 0.05;

        if (!FINAL) {
            // * Movement
            b = a;

            a.movement(dx);
            if (!a.check(field)) {
                a = b;
            } else {
                b.fromfield(field);
                a.tofield(field);
            }

            b = a;
            // * Rotation
            if (rotate) a.rotate();

            if (!a.check(field)) {
                a = b;
//                std::cout << "not" << " ";
            } else {
//                std::cout << "yes1" << " ";
                b.fromfield(field);
//                std::cout << "yes2" << " ";
                a.tofield(field);
//                std::cout << "yes3" << " ";
            }

            b = a;
            // * Tick system (falling)
            if (timer > delay) {
                a.fall();

                if (!a.check(field)) {
                    b.stop();
                    b.tofield(field);
                    for (int i = 0; i < width; ++i) {
                        if (field[1][i].getStat() == 1) {
//                            std::cout << "stop";
                            FINAL = true;
                        }
                    }
                    Figure c;
                    a = c;
                    a.tofield(field);
                } else {
                    b.fromfield(field);
                    a.tofield(field);
                }

                timer = 0;
            }
            b = a;

            // * Line clear
            int k = height - 1;

            for (int i = height - 1; i > 0; i--) {
                int count = 0;

                for (int j = 0; j < width; j++) {
                    if (field[i][j].getStat() == 1)
                        count++;

                    field[k][j] = field[i][j];
                }

                if (count < width)
                    k--;
            }

            //         * Scores
            score += k;
            scoreLabel.setString(std::to_string(score));

            // * Draw to window
            window.clear(Color(0x685850FF));

            for (int i = 0; i < height; i++) {
                for (int j = 0; j < width; j++) {
                    if (field[i][j].getI() == '#') {
                        if (field[i][j].getColor() == 1) {
                            shape.setFillColor(Color(0xCCA8D8FF));
                        }
                        else if (field[i][j].getColor() == 2) {
                            shape.setFillColor(Color(0xF886A8FF));
                        }
                        else if (field[i][j].getColor() == 3) {
                            shape.setFillColor(Color(0xFDC453FF));
                        }
                        else if (field[i][j].getColor() == 4) {
                            shape.setFillColor(Color(0x9ADBC5FF));
                        }
                        else if (field[i][j].getColor() == 5) {
                            shape.setFillColor(Color(0xA0DDE0FF));
                        }
                        else if (field[i][j].getColor() == 6) {
                            shape.setFillColor(Color(0xFE8D6FFF));
                        }
                        else if (field[i][j].getColor() == 7) {
                            shape.setFillColor(Color(0xFCC1B1FF));
                        }
                        shape.setPosition(j * 18+padding*1.5, i * 18+padding*1.5);
                        window.draw(shape);
                    }
                }
            }
        }

        for (int i = 0; i < width; ++i) {
            RectangleShape line(sf::Vector2f((height-1)*18+5, 2));
            line.move(padding*1.5+18*i, padding*1.5);
            line.setFillColor(Color(0x12120D44));
            line.rotate(90);

            window.draw(line);
        }
        for (int i = 0; i < height; ++i) {
            RectangleShape line(sf::Vector2f(width*18, 2));
            line.move(padding*1.5, padding*1.5+i*18);
            line.setFillColor(Color(0x12120D44));

            window.draw(line);
        }

//        RectangleShape line(sf::Vector2f(padding*1.5, 5));
        RectangleShape line1(sf::Vector2f((height-1)*18+5, 5));
        line1.move(padding*1.5, padding*1.5);

        RectangleShape line2(sf::Vector2f(width*18, 5));
        line2.move(padding*1.5, padding*1.5);

        RectangleShape line3(sf::Vector2f((height-1)*18+5, 5));
        line3.move(padding*1.5+(width*18)+5, padding*1.5);

        RectangleShape line4(sf::Vector2f(width*18, 5));
        line4.move(padding*1.5, (height-1)*18+padding*1.5);

        line1.setFillColor(Color(0x766092FF));
        line2.setFillColor(Color(0x766092FF));
        line3.setFillColor(Color(0x766092FF));
        line4.setFillColor(Color(0x766092FF));

        line1.rotate(90);
        line3.rotate(90);

//        line.rotate(45);
        window.draw(line1);
        window.draw(line2);
        window.draw(line3);
        window.draw(line4);

        dx = 0;
        rotate = false;
        delay = 0.3f;

        aboba++;
        scoreTextLabel.setPosition(window.getSize().x / 2 - 75, 240-padding*2);
        window.draw(scoreTextLabel);

        scoreLabel.setPosition(window.getSize().x / 2 - 15, 270-padding*2);
        window.draw(scoreLabel);
        window.display();
    }
//    field.printField();
//    std::cout << "SCORE: "<< score << " points";
    return 0;
}
