class Rectangle
{
private:
    int topLeftCorner;
    bool isDirectionUp;
    int width;
    int height;
    int speed;
    bool isSleeping;
    condition_variable cv;

public:
    Rectangle(const Rectangle &);
    Rectangle(int, int);
    void drawSpeed();
    int getTopEdge();
    void setTopEdge(int);
    int getBottomEdge();
    bool getIsDirectionUp();
    void changeDirection();
    int getSpeed();
    int getWidth();
    int getHeight();
    void bounce();
    void moveRectangle();
    void notify();
    void negateIsSleeping();
    bool getIsSleeping();
};