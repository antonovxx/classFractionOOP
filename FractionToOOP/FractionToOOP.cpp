// FractionToOOP.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.

#include <iostream>

using std::cout;
using std::cin;
using std::endl;

class Point
{
    double x;
    double y;

public:
    double get_x() const
    {
        return x;
    }
    double get_y() const
    {
        return y;
    }
    void set_x(double x)
    {
        this->x = x;
    }
    void set_y(double y)
    {
        this->y = y;
    }

    // Constructors:

    Point(double x = 0,  double y = 0)
    {
        this->x = x;
        this->y = y;
    }
    ~Point()
    {
        cout << " Destructor: " << this << endl;
    }
    Point(const Point& other)
    {
        this->x = other.x;
        this->y = other.y;
    }

    // Methods:
    double distance(Point other)
    {
        double x_distance = this->x - other.x;
        double y_distance = this->y - other.y;
        double distance = sqrt(x_distance * x_distance + y_distance * y_distance);
        return distance;
    }
};


int main()
{
    Point A(2, 3);
    Point B(5, 6);

    cout << "Distance from A to B is " << A.distance(B) << endl;

    return 0;
}
