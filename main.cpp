#include <iostream>
#include <ncurses.h>
#include <unistd.h>
#include <stdlib.h>
#include <thread>
#include <list>
#include <vector>
#include <random>
#include "Circle/circle.cpp"

using namespace std;

const int BOARD_LENGTH = 71;
const int BOARD_WIDTH = 30;

vector<Circle> circleList;

void moveCircle(Circle *circle)
{
    int x, y;
    while (1)
    {
        x = circle->getX();
        y = circle->getY();

        // Bottom
        if (x == BOARD_WIDTH - 2)
        {
            circle->bounceX();
            circle->incrementNumberOfBounces();
        }
        // Upper
        else if (x == 1)
        {
            circle->bounceX();
            circle->incrementNumberOfBounces();
        }

        // Right
        if (y == BOARD_LENGTH - 2)
        {
            circle->bounceY();
            circle->incrementNumberOfBounces();
        }
        // Left
        else if (y == 1)
        {
            circle->bounceY();
            circle->incrementNumberOfBounces();
        }

        if (circle->getNumberOfBounces() >= 5)
        {
            break;
        }

        circle->setX(x + circle->getDeltaX());
        circle->setY(y + circle->getDeltaY());
        int sl = circle->getSpeed();
        usleep(sl);
    }
}

bool allcirclesDoneCheck()
{
    for (Circle circle : circleList)
    {
        if (circle.getNumberOfBounces() < 5)
        {
            return false;
        }
    }
    return true;
}

// void moveSquare(Square *square)
// {
//     int upPosition;

//     while (1)
//     {
//         if (allcirclesDoneCheck())
//         {
//             break;
//         }
//         upPosition = square->getUpPosition();
//         if (square->isUpDirection())
//         {
//             square->setUpPosition(upPosition -= 1);
//             if (square->getUpPosition() == 1)
//             {
//                 square->changeDirection();
//                 square->drawSpeed();
//             }
//         }
//         else
//         {
//             square->setUpPosition(upPosition += 1);
//             if (square->getDownPosition() == BOARD_WIDTH - 1)
//             {
//                 square->changeDirection();
//                 square->drawSpeed();
//             }
//         }
//         int sl = square->getSpeed();
//         usleep(sl);
//     }
// }

void printBoard(WINDOW *win)
{
    for (;;)
    {
        if (allcirclesDoneCheck())
        {
            break;
        }
        for (Circle circle : circleList)
        {
            if (circle.getNumberOfBounces() >= 5)
            {
                continue;
            }
            mvwprintw(win, circle.getX(), circle.getY(), circle.getName());
        }

        wrefresh(win);
        fflush(stdout);
        napms(100);
        werase(win);
        box(win, 0, 0);
    }
}

int main(int argc, char **argv)
{

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> sleepTime(300'000, 600'000);
    uniform_int_distribution<> circleDirection(1, 3);
    uniform_int_distribution<> squareSpeed(100000, 600000);

    initscr();
    noecho();
    curs_set(0);
    WINDOW *win = newwin(BOARD_WIDTH, BOARD_LENGTH, 15, 15);
    start_color();
    use_default_colors();
    box(win, 0, 0);

    char *namesArray[8] = {"O", "P", "B", "C", "G", "D", "U", "R"};

    for (int i = 0; i < 8; i++)
    {
        circleList.push_back(Circle(namesArray[i], sleepTime(gen), circleDirection(gen)));
    }

    list<thread> threadList;

    for (int i = 0; i < 8; i++)
    {
        threadList.push_back(thread(moveCircle, &(circleList[i])));
        this_thread::sleep_for(1s);
    }

    while (!threadList.empty())
    {
        threadList.front().join();
        threadList.pop_front();
    }

    endwin();

    return 0;
}