#include <random>
#include "rectangle.h"

using namespace std;

Rectangle::Rectangle(int width, int height)
{
    this->width = width;
    this->height = height;
    this->drawSpeed();
    this->topLeftCorner = 10;
    this->isDirectionUp = true;
}

void Rectangle::changeDirection()
{
    this->isDirectionUp = !isDirectionUp;
}

bool Rectangle::getIsDirectionUp()
{
    return isDirectionUp;
}

int Rectangle::getBottomEdge()
{
    return this->topLeftCorner + this->height;
}

int Rectangle::getTopEdge()
{
    return this->topLeftCorner;
}

void Rectangle::setTopEdge(int position)
{
    this->topLeftCorner = position;
}

void Rectangle::drawSpeed()
{
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> RectangleSpeed(100, 1000);
    this->speed = RectangleSpeed(gen);
}

int Rectangle::getSpeed()
{
    return this->speed;
}

int Rectangle::getWidth()
{
    return this->width;
}

int Rectangle::getHeight()
{
    return this->height;
}

void Rectangle::bounce()
{
    this->changeDirection();
    this->drawSpeed();
}