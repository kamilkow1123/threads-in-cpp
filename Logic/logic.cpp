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

list<Circle> circleList;
bool shouldEnd = false;

void moveCircle(Circle *circle)
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

        int sleepTime = circle->getSpeed();
        this_thread::sleep_for(chrono::milliseconds(sleepTime));
    }
}

void moveRectangle(Rectangle *rectangle)
{
    int topEdge;

    for (;;)
    {
        if (shouldEnd)
            break;

        if (rectangle->getTopEdge() == 1 || rectangle->getBottomEdge() == BOARD_WIDTH - 1)
            rectangle->bounce();

        topEdge = rectangle->getTopEdge();
        if (rectangle->getIsDirectionUp())
            rectangle->setTopEdge(--topEdge);
        else
            rectangle->setTopEdge(++topEdge);

        int sleepTime = rectangle->getSpeed();
        this_thread::sleep_for(chrono::milliseconds(sleepTime));
    }
}

void printCircles(WINDOW *win)
{
    for (Circle circle : circleList)
    {
        if (circle.getNumberOfBounces() > BOUNCE_LIMIT)
            continue;

        mvwprintw(win, circle.getX(), circle.getY(), circle.getSymbol());
    }
}

void printRectangle(WINDOW *win, Rectangle *rectangle)
{
    wattron(win, A_STANDOUT);
    for (int i = 0; i < rectangle->getWidth(); i++)
        for (int j = 0; j < rectangle->getHeight(); j++)
            mvwprintw(win, rectangle->getTopEdge() + i, j + RECTANGLE_OFFSET, " ");

    wattroff(win, A_STANDOUT);
}

void printBoard(WINDOW *win, Rectangle *rectangle)
{
    for (;;)
    {
        if (shouldEnd)
            break;

        werase(win);

        box(win, 0, 0);
        printCircles(win);
        printRectangle(win, rectangle);

        wrefresh(win);

        this_thread::sleep_for(10ms);
    }
}

void endProgram()
{
    char key;
    do
    {
        key = getch();
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

    thread endProgramThread(endProgram);
    thread printBoardThread(printBoard, win, &rectangle);
    thread moveRectangleThread(moveRectangle, &rectangle);
    list<thread> threadList;

    while (!shouldEnd)
    {
        Circle newCircle = Circle(symbols[symbolsIndex(gen)], sleepTime(gen), circleDirection(gen));
        circleList.push_back(newCircle);
        threadList.push_back(thread(moveCircle, &(circleList.back())));
        this_thread::sleep_for(chrono::milliseconds(drawBreakTime(gen)));
    }

    endProgramThread.join();
    printBoardThread.join();
    moveRectangleThread.join();

    while (!threadList.empty())
    {
        threadList.front().join();
        threadList.pop_front();
    }

    endwin();
}