#include <iostream>
#include <Windows.h>

enum Color
{
	red = 0x000000FF, 
	green = 0x0000FF00,
	blue = 0x00FF0000,

	console_red = 0xCC,
	console_green = 0xAA,
	console_blue = 0x99,
	console_default = 0x07
};

class Shape
{
protected:
	unsigned int start_x;
	unsigned int start_y;
	unsigned int line_width;
	Color color;
public:
	void set_start_x(unsigned int start_x)
	{
		if (start_x > 300) start_x = 300;
		this->start_x = start_x;
	}
	void set_start_y(unsigned int start_y)
	{
		if (start_y > 300) start_y = 300;
		this->start_y = start_y;
	}
	void set_line_width(unsigned int line_width)
	{
		if (line_width > 20) line_width = 20;
		this->line_width = line_width;
	}

	Shape(Color color, unsigned int start_x, unsigned int start_y, unsigned int line_width) : color(color)
	{
		set_start_x(start_x);
		set_start_y(start_y);
		set_line_width(line_width);
	}
	virtual ~Shape() {}

	virtual double get_area() const = 0;
	virtual double get_perimetr() const = 0;
	virtual void draw() const = 0;
};

class Square : public Shape
{
	double side;

public:
	double get_side() const
	{
		return side;
	}

	void set_side(double side)
	{
		if (side <= 0)side = 10;
		this->side = side;
	}

	Square(double side,
		Color color, 
		unsigned int start_x, unsigned int start_y,
		unsigned int line_width)
		:Shape(color, start_x, start_y, line_width)
	{
		set_side(side);
	}
	~Square() {}

	double get_area() const
	{
		return side * side;
	}

	double get_perimetr() const
	{
		return side * 4;
	}

	void draw() const
	{
		/*HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, color);

		for (int i = 0; i < side; ++i)
		{
			for (int i = 0; i < side; ++i)
			{
				std::cout << " * ";
			}
			std::cout << std::endl;
		}
		SetConsoleTextAttribute(hConsole, Color::console_default);*/

		// H - Handle 
		HWND hConsole = GetConsoleWindow(); // Получаем окно консоли
		HDC hdc = GetDC(hConsole); // Создаем контекст устройства для полученного окна
		HPEN hPen = CreatePen(PS_SOLID, line_width, color); //Создаем карандаш

		SelectObject(hdc, hPen); // Выбираем созданный карандаш
		HBRUSH hBrush = CreateSolidBrush(color); // Создание кисть, которая закрашивает замкнутые фигуры
		SelectObject(hdc, hBrush); // выбираем созданную кисть (выбираются для того, чтобы функция Rectangle понимала чем рисовать) 
		Rectangle(hdc, start_x, start_y, start_x + side, start_y + side); // Рисует квадрат 

		// Удаление созданные кисть и карандаш
		DeleteObject(hBrush);
		DeleteObject(hPen);
		ReleaseDC(hConsole, hdc); // освобождение контекста устройства
	}
};

int main()
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD buffer = { 16, 16 };
	//SetConsoleDisplayMode(hConsole, CONSOLE_FULLSCREEN_MODE, &buffer);

	Square Square(250, Color::blue, 500, 500, 5);
	std::cout << "Square side:\t" << Square.get_side() << std::endl;
	std::cout << "Square area:\t" << Square.get_area() << std::endl;
	std::cout << "Square perimeter:\t" << Square.get_perimetr() << std::endl;
	Square.draw();

	return 0;
}
