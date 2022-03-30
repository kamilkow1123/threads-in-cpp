#include <random>
#include "rectangle.h"

using namespace std;

Rectangle::Rectangle(int length, int height)
{
    this->length = length;
    this->height = height;
    this->drawSpeed();
    this->leftUpCorner = 5;
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

int Rectangle::getDownPosition()
{
    return this->leftUpCorner + this->height;
}

int Rectangle::getUpPosition()
{
    return this->leftUpCorner;
}

void Rectangle::setUpPosition(int position)
{
    this->leftUpCorner = position;
}

void Rectangle::drawSpeed()
{
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> RectangleSpeed(100000, 1000000);
    this->speed = RectangleSpeed(gen);
}

int Rectangle::getSpeed()
{
    return this->speed;
}

int Rectangle::getLength()
{
    return this->length;
}

int Rectangle::getHeight()
{
    return this->height;
}