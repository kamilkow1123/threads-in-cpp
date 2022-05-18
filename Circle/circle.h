#include <iostream>
using namespace std;

class Circle
{
private:
    const char *symbol;
    int x;
    int y;
    int speed;
    int numberOfBounces;
    int deltaX;
    int deltaY;

public:
    Circle();
    Circle(const char *, int, int);
    ~Circle();
    const char *getSymbol();
    int getX();
    void setX(int);
    int getY();
    void setY(int);
    int getSpeed();
    int getNumberOfBounces();
    void setNumberOfBounces(int);
    void incrementNumberOfBounces();
    int getDeltaX();
    void bounceX();
    int getDeltaY();
    void bounceY();
    bool touchedRectangle(int, int, int);
};