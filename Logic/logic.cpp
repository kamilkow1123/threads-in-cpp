#include <iostream>
#include <ncurses.h>
#include <unistd.h>
#include <stdlib.h>
#include <thread>
#include <list>
#include <vector>
#include <random>
#include <mutex>
#include <condition_variable>

bool shouldEnd = false;

#include "../Circle/circle.cpp"
#include "../Rectangle/rectangle.cpp"

list<Circle> circleList;

void moveCircle(Circle *circle, Rectangle *rectangle)
{
    int x, y;
    for (;;)
    {
        if (circle->getNumberOfBounces() > BOUNCE_LIMIT || shouldEnd)
            break;

        x = circle->getX();
        y = circle->getY();

        if (x == BOARD_WIDTH - 2 || x == 1)
            circle->bounceX();

        if (y == BOARD_LENGTH - 2 || y == 1)
            circle->bounceY();

        circle->setX(x + circle->getDeltaX());
        circle->setY(y + circle->getDeltaY());

        if (circle->touchedRectangle(
                rectangle->getTopEdge(),
                rectangle->getWidth(),
                rectangle->getHeight()))
        {
            circle->setNumberOfBounces(100);
            rectangle->negateIsSleeping();
        }

        int sleepTime = circle->getSpeed();
        this_thread::sleep_for(chrono::milliseconds(sleepTime));
    }
}

void printCircles(WINDOW *win, Rectangle *rectangle)
{
    for (Circle circle : circleList)
    {
        if (circle.getNumberOfBounces() > BOUNCE_LIMIT)
            continue;

        wattron(win, COLOR_PAIR(1));
        mvwprintw(win, circle.getX(), circle.getY(), circle.getSymbol());
        wattroff(win, COLOR_PAIR(1));
    }
}

void printRectangle(WINDOW *win, Rectangle *rectangle)
{
    wattron(win, A_STANDOUT);
    for (int i = 0; i < rectangle->getWidth(); i++)
        for (int j = 0; j < rectangle->getHeight(); j++)
        {
            if (rectangle->getIsSleeping())
            {
                wattron(win, COLOR_PAIR(2));
                mvwprintw(win, rectangle->getTopEdge() + i, j + RECTANGLE_OFFSET, " ");
                wattroff(win, COLOR_PAIR(2));
            }
            else
                mvwprintw(win, rectangle->getTopEdge() + i, j + RECTANGLE_OFFSET, " ");
        }

    wattroff(win, A_STANDOUT);
}

void printBoard(WINDOW *win, Rectangle *rectangle)
{
    init_pair(1, COLOR_BLACK, COLOR_BLUE);
    init_pair(2, COLOR_BLACK, COLOR_RED);
    for (;;)
    {
        if (shouldEnd)
            break;

        werase(win);

        box(win, 0, 0);
        printCircles(win, rectangle);
        printRectangle(win, rectangle);

        wrefresh(win);

        this_thread::sleep_for(10ms);
    }
}

void endProgram(WINDOW *win)
{
    char key;
    do
    {
        key = wgetch(win);
    } while (key != 'q');
    shouldEnd = true;
}

void run()
{
    random_device rd;
    mt19937 gen(rd());

    initscr();
    noecho();
    curs_set(0);
    start_color();
    use_default_colors();
    WINDOW *win = newwin(BOARD_WIDTH, BOARD_LENGTH, 15, 15);

    Rectangle rectangle = Rectangle(10, 10);

    thread endProgramThread(endProgram, win);
    thread printBoardThread(printBoard, win, &rectangle);
    thread moveRectangleThread(&Rectangle::moveRectangle, &rectangle);
    list<thread> threadList;

    while (!shouldEnd)
    {
        Circle newCircle = Circle(symbols[symbolsIndex(gen)], sleepTime(gen), circleDirection(gen));
        circleList.push_back(newCircle);
        threadList.push_back(thread(moveCircle, &(circleList.back()), &rectangle));
        this_thread::sleep_for(chrono::milliseconds(drawBreakTime(gen)));
    }

    endProgramThread.join();
    printBoardThread.join();
    rectangle.notify();
    moveRectangleThread.join();

    while (!threadList.empty())
    {
        threadList.front().join();
        threadList.pop_front();
    }

    endwin();
}

//pilka stuka w prostokat i znika, prostokat sie usypia czyli zatrzymuje, jak kolejna pilka stuknie w prostokat to go obudzi