#include "circle.h"

Circle::Circle(const char *symbol, int speed, int direction)
{
    this->x = 28;
    this->y = 35;
    this->symbol = symbol;
    this->speed = speed;
    this->deltaX = 1;
    this->numberOfBounces = 0;
    if (direction == 1)
    {
        this->deltaY = 1;
    }
    else if (direction == 2)
    {
        this->deltaY = -1;
    }
    else
    {
        this->deltaY = 0;
    }
}

Circle::~Circle() {}

int Circle::getX() { return this->x; }

int Circle::getY() { return this->y; }

int Circle::getSpeed() { return this->speed; }

int Circle::getNumberOfBounces() { return this->numberOfBounces; }

int Circle::getDeltaX() { return this->deltaX; }

int Circle::getDeltaY() { return this->deltaY; }

const char *Circle::getName() { return this->symbol; }

void Circle::setX(int coordinate) { this->x = coordinate; }

void Circle::setY(int coordinate) { this->y = coordinate; }

void Circle::incrementNumberOfBounces() { this->numberOfBounces++; }

void Circle::bounceX() { this->x *= -1; }

void Circle::bounceY() { this->y *= -1; }