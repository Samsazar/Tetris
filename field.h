#pragma once
#include <vector>
#include <iostream>

class Tile {
    int x = 0, y = 0, status = 0, color = 0; // status = 0 - пустая клетка
                                  // status = 1 - статичная клетка
                                  // status = 2 - движение
    char image = '@';
public:
    Tile() {};
    Tile(int x, int y, char i = '@', int s = 0, int c = 0) : x(x), y(y), image(i), status(s), color(c) {};

    Tile& operator=(const Tile& a) {
        if (&a == this) return *this;
        x = a.x;
        y = a.y;
        color = a.color;
        status = a.status;
        image = a.image;
        return *this;
    }

    void fall() {
        y++;
    }
    void move(int dx) {
        x += dx;
    }

    int& getX() {
        return x;
    }
    int& getY() {
        return y;
    }
    char& getI() {
        return image;
    }
    void stop() {
        status = 1;
    }
    int& getStat() {
        return status;
    }
    int getColor() {
        return color;
    }
    void print() {
        std::cout << x << " " << y << std::endl;
    }

};

int shapes[7][4] = {
        1, 3, 5, 7, // I
        2, 4, 5, 7, // Z
        3, 5, 4, 6, // S
        3, 5, 4, 7, // T
        2, 3, 5, 7, // L
        3, 5, 7, 6, // J
        2, 3, 4, 5  // O
};

class Field
{
private:
    int width, height;
    std::vector <std::vector<Tile>> field;
public:
    Field(int w, int h) : width(w), height(h)
    {
        field.resize(height);
        for (int i = 0; i < height; i++)
        {
            std::vector<Tile> v(width);
            for (int j = 0; j < width; j++)
            {
                v[j].getX() = i;
                v[j].getY() = j;
                v[j].getI() = '@';
                v[j].getStat() = 0;
            }

            field[i] = v;
        }
    };

    std::vector<Tile>& operator[](int i) { return field[i]; }

    int get_width() {
        return width;
    }
    int get_height() {
        return height;
    }

    void printField()
    {
        for (int i = 0; i < field.size(); i++)
        {
            for (int j = 0; j < field[i].size(); j++)
                std::cout << field[i][j].getStat() << " ";
            std::cout << std::endl;
        }
    }
};

class Figure {
protected:
    int type, color; // 1 -
    std::vector<Tile> tiles;
public:
    Figure() {
        type = rand() % 7;
        color = 1 + type;
        for (int i = 0; i < 4; i++)
        {
            Tile newTile(shapes[type][i] % 2, shapes[type][i] / 2, '#', 2, color);
            tiles.push_back(newTile);
        }
    };
    Figure& operator=(const Figure& a) {
        if (&a == this) return *this;
        type = a.type;
        tiles.reserve(a.tiles.size());
        for (int i = 0; i < a.tiles.size(); i++)
            tiles[i] = a.tiles[i];
        return *this;
    }

    void tofield(Field &field) {
        for (int i = 0; i < tiles.size(); i++) {
            field[tiles[i].getY()][tiles[i].getX()] = tiles[i];
        }
    }

    void fromfield(Field &field) {
        for (int i = 0; i < tiles.size(); i++) {
            field[tiles[i].getY()][tiles[i].getX()] = Tile(tiles[i].getX(), tiles[i].getY(), '@', 0);
        }
    }

    void movement(int dx) {
        for (int i = 0; i < tiles.size(); ++i) {
            tiles[i].move(dx);
        }
    }

    void stop() {
        for (int i = 0; i < tiles.size(); ++i) {
            tiles[i].stop();
        }
    }

    void rotate() {
        if (type != 6) {
            // Center of the rotation.
            Tile point = tiles[1];

            for (int i = 0; i < tiles.size(); i++) {
                int x = tiles[i].getY() - point.getY();
                int y = tiles[i].getX() - point.getX();
                tiles[i].getX() = point.getX() - x;
                tiles[i].getY() = point.getY() + y;
            }
        }
    }

    void print() {
        std::vector<std::vector<Tile>> pole;
        for (int i = 0; i < 4; i++) {
            std::vector<Tile> v;
            for (int j = 0; j < 4; ++j) {
                v.push_back(Tile(i, j, '0', 0));
            }
//            v.resize(4, 0);
            pole.push_back(v);
        }
        for (int i = 0; i < tiles.size(); i++) {
            pole[tiles[i].getY()][tiles[i].getX()] = tiles[i];
            std::cout << tiles[i].getStat() << " " << pole[tiles[i].getY()][tiles[i].getX()].getStat() << " ";
        }
        std::cout << "\n";

        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                std::cout << pole[i][j].getStat() << " ";
            }
            std::cout << std::endl;
        }
    }
    bool check(Field field, int dx = 0) {
        for (int i = 0; i < tiles.size(); i++) {
            // Check for the shape being in the playfield.
            if (tiles[i].getX() < 0 || tiles[i].getX() >= field.get_width() || tiles[i].getY() < 0)
                return false;

            // The more I look at it, the more I want to puke.
            if (tiles[i].getY() == field.get_height()-1) {
//                std::cout << "zamena stat dno" << " ";
//                 проверка на stop
//                for (int j = 0; j < tiles.size(); ++j) {
//                    std::cout << "Stat " << j << ": "<< tiles[i].getStat() << " Stat in field: " << field[tiles[i].getY()][tiles[i].getX()].getStat();
//                }
//                std::cout << std::endl;
                return false;
            }
            if (field[tiles[i].getY()][tiles[i].getX()].getStat() == 1) {
//                std::cout << "zamena stat nyj" << " ";
                return false;
            }

//            if (field[tiles[i].getY()][tiles[i].getX()+dx].getStat() == 1) {
//                std::cout << "zamena stat bok" << " ";
//                return false;
//            }
        }

        return true;
    }
    void fall() {
        for (int i = 0; i < tiles.size(); ++i) {
            tiles[i].fall();
        }
    }
};

