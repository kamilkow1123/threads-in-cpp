class Rectangle
{
private:
    int topLeftCorner;
    bool isDirectionUp;
    int width;
    int height;
    int speed;

public:
    Rectangle(int width, int height);
    void drawSpeed();
    int getTopEdge();
    void setTopEdge(int position);
    int getBottomEdge();
    bool getIsDirectionUp();
    void changeDirection();
    int getSpeed();
    int getWidth();
    int getHeight();
    void bounce();
};