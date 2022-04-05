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
    const char *getSymbol();
    int getX();
    void setX(int coordinate);
    int getY();
    void setY(int coordinate);
    int getSpeed();
    int getNumberOfBounces();
    void incrementNumberOfBounces();
    int getDeltaX();
    void bounceX();
    int getDeltaY();
    void bounceY();
};