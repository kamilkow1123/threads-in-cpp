#include "circle.h"
#include "../Logic/constants.cpp"

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

const char *Circle::getSymbol() { return this->symbol; }

int Circle::getX() { return this->x; }

void Circle::setX(int coordinate) { this->x = coordinate; }

int Circle::getY() { return this->y; }

void Circle::setY(int coordinate) { this->y = coordinate; }

int Circle::getSpeed() { return this->speed; }

int Circle::getNumberOfBounces() { return this->numberOfBounces; }

void Circle::setNumberOfBounces(int num)
{
    this->numberOfBounces = num;
}

void Circle::incrementNumberOfBounces() { this->numberOfBounces++; }

int Circle::getDeltaX() { return this->deltaX; }

void Circle::bounceX()
{
    this->deltaX *= -1;
    this->incrementNumberOfBounces();
}

int Circle::getDeltaY() { return this->deltaY; }

void Circle::bounceY()
{
    this->deltaY *= -1;
    this->incrementNumberOfBounces();
}

bool Circle::touchedRectangle(int topLeftCorner, int width, int height)
{
    return (
        y >= RECTANGLE_OFFSET &&
        y <= RECTANGLE_OFFSET + width &&
        x >= topLeftCorner &&
        x <= topLeftCorner + height);
}
