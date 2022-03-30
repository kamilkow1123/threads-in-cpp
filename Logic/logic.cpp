#include <iostream>
#include <ncurses.h>
#include <unistd.h>
#include <stdlib.h>
#include <thread>
#include <list>
#include <vector>
#include <random>
#include "../Circle/circle.cpp"
#include "../Rectangle/rectangle.cpp"
#include "./constants.cpp"

vector<Circle> circleList;

void moveCircle(Circle *circle)
{
    int x, y;
    for (;;)
    {
        x = circle->getX();
        y = circle->getY();

        if (x == BOARD_WIDTH - 2)
        {
            circle->bounceX();
            circle->incrementNumberOfBounces();
        }
        else if (x == 1)
        {
            circle->bounceX();
            circle->incrementNumberOfBounces();
        }
        if (y == BOARD_LENGTH - 2)
        {
            circle->bounceY();
            circle->incrementNumberOfBounces();
        }
        else if (y == 1)
        {
            circle->bounceY();
            circle->incrementNumberOfBounces();
        }

        if (circle->getNumberOfBounces() >= BOUNCE_LIMIT)
            break;

        circle->setX(x + circle->getDeltaX());
        circle->setY(y + circle->getDeltaY());
        int sl = circle->getSpeed();
        usleep(sl);
    }
}

bool areAllCirclesDone()
{
    for (Circle circle : circleList)
        if (circle.getNumberOfBounces() < BOUNCE_LIMIT)
            return false;

    return true;
}

void moveRectangle(Rectangle *rectangle)
{
    int upPosition;

    for (;;)
    {
        if (areAllCirclesDone())
            break;

        upPosition = rectangle->getUpPosition();
        if (rectangle->getIsDirectionUp())
        {
            rectangle->setUpPosition(upPosition -= 1);
            if (rectangle->getUpPosition() == 1)
            {
                rectangle->changeDirection();
                rectangle->drawSpeed();
            }
        }
        else
        {
            rectangle->setUpPosition(upPosition += 1);
            if (rectangle->getDownPosition() == BOARD_WIDTH - 1)
            {
                rectangle->changeDirection();
                rectangle->drawSpeed();
            }
        }
        int sl = rectangle->getSpeed();
        usleep(sl);
    }
}

void printBoard(WINDOW *win, Rectangle *rectangle)
{
    for (;;)
    {
        if (areAllCirclesDone())
            break;

        for (Circle circle : circleList)
        {
            if (circle.getNumberOfBounces() >= BOUNCE_LIMIT)
                continue;

            mvwprintw(win, circle.getX(), circle.getY(), circle.getSymbol());
        }
        wattron(win, A_STANDOUT);
        for (int i = 0; i < rectangle->getLength(); i++)
            for (int j = 0; j < rectangle->getHeight(); j++)
                mvwprintw(win, rectangle->getUpPosition() + i, j + RECTANGLE_OFFSET, " ");

        wattroff(win, A_STANDOUT);
        wrefresh(win);
        fflush(stdout);
        napms(100);
        werase(win);
        box(win, 0, 0);
    }
}

void run()
{
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> sleepTime(300'000, 600'000);
    uniform_int_distribution<> circleDirection(1, 3);
    uniform_int_distribution<> rectangleSpeed(100000, 600000);

    initscr();
    noecho();
    curs_set(0);
    WINDOW *win = newwin(BOARD_WIDTH, BOARD_LENGTH, 15, 15);
    start_color();
    use_default_colors();
    box(win, 0, 0);

    Rectangle rectangle = Rectangle(10, 10);
    thread printBoardThread(printBoard, win, &rectangle);
    thread moveRectangleThread(moveRectangle, &rectangle);

    char *namesArray[10] = {(char *)"a", (char *)"b", (char *)"c", (char *)"d", (char *)"e", (char *)"f", (char *)"g", (char *)"h", (char *)"i", (char *)"j"};

    for (int i = 0; i < 10; i++)
    {
        circleList.push_back(Circle(namesArray[i], sleepTime(gen), circleDirection(gen)));
    }

    list<thread> threadList;

    for (int i = 0; i < 10; i++)
    {
        threadList.push_back(thread(moveCircle, &(circleList[i])));
        this_thread::sleep_for(1s);
    }

    printBoardThread.join();
    moveRectangleThread.join();

    while (!threadList.empty())
    {
        threadList.front().join();
        threadList.pop_front();
    }

    endwin();
}