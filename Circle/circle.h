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
    Circle(const char *symbol, int speed, int direction);
    ~Circle();
    int getX();
    void setX(int coordinate);
    int getY();
    void setY(int coordinate);
    int getSpeed();
    const char *getSymbol();
    int getNumberOfBounces();
    void incrementNumberOfBounces();
    void bounceX();
    void bounceY();
    int getDeltaX();
    int getDeltaY();
};