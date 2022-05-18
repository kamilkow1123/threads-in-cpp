#include <random>
#include "rectangle.h"

using namespace std;

Rectangle::Rectangle(const Rectangle &rec)
{
    this->topLeftCorner = rec.topLeftCorner;
    this->isDirectionUp = rec.isDirectionUp;
    this->width = rec.width;
    this->height = rec.height;
    this->speed = rec.speed;
    this->isSleeping = rec.isSleeping;
}

Rectangle::Rectangle(int width, int height)
{
    this->width = width;
    this->height = height;
    this->drawSpeed();
    this->topLeftCorner = 10;
    this->isDirectionUp = true;
    this->isSleeping = false;
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

void Rectangle::moveRectangle()
{
    static mutex m;
    int topEdge;

    for (;;)
    {
        if (shouldEnd)
            break;

        if (this->getTopEdge() == 1 || this->getBottomEdge() == BOARD_WIDTH - 1)
            this->bounce();

        topEdge = this->getTopEdge();
        if (this->getIsDirectionUp())
            this->setTopEdge(--topEdge);
        else
            this->setTopEdge(++topEdge);

        {
            unique_lock<mutex> lk(m);
            if (this->isSleeping)
            {
                cv.wait(lk);
                this->isSleeping = false;
            }
        }

        int sleepTime = this->getSpeed();
        this_thread::sleep_for(chrono::milliseconds(sleepTime));
    }
}

void Rectangle::notify()
{
    cv.notify_one();
}

void Rectangle::negateIsSleeping()
{
    bool currIsSleeping = this->isSleeping;
    if (currIsSleeping)
        this->notify();
    else
        this->isSleeping = true;
}

bool Rectangle::getIsSleeping()
{
    return this->isSleeping;
}