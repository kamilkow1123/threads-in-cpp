class Rectangle
{
private:
    int leftUpCorner;
    bool isDirectionUp;
    int length;
    int height;
    int speed;

public:
    Rectangle(int length, int height);
    void drawSpeed();
    int getUpPosition();
    void setUpPosition(int position);
    int getDownPosition();
    bool getIsDirectionUp();
    void changeDirection();
    int getSpeed();
    int getLength();
    int getHeight();
};