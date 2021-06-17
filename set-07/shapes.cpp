#include <iostream>

class Shape {
public:
    virtual void draw() = 0;
};

class Circle : public Shape {
public:
    void draw() override {
        std::cout << "circle" << std::endl;
    }
};

class Square : public Shape {
public:
    void draw() override {
        std::cout << "square" << std::endl;
    }
};

class Triangle : public Shape {
public:
    void draw() override {
        std::cout << "triangle" << std::endl;
    }
};

int main() {

    Circle circle;
    Square square;
    Triangle triangle;

    circle.draw();
    square.draw();
    triangle.draw();

    return 0;
}
