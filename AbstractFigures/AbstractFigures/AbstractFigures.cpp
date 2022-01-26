#define _USE_MATH_DEFINES

#include <iostream>
#include <Windows.h>
#include <cmath>

namespace Geometry
{
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

		virtual void info() const
		{
			std::cout << "Area:\t" << get_area() << std::endl;
			std::cout << "Perimeter:\t" << get_perimetr() << std::endl;
			draw();
		}
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
			::Rectangle(hdc, start_x, start_y, start_x + side, start_y + side); // Рисует квадрат 

			// Удаление созданные кисть и карандаш
			DeleteObject(hBrush);
			DeleteObject(hPen);
			ReleaseDC(hConsole, hdc); // освобождение контекста устройства

		}

		void info() const
		{
			std::cout << typeid(*this).name() << std::endl;
			std::cout << "Lenght of the side: " << side << std::endl;
			Shape::info();
		}
	};
	class Rectangle : public Shape
	{
		double width;
		double length;
	public:
		double get_width()const
		{
			return width;
		}
		double get_length()const
		{
			return length;
		}
		void set_width(double width)
		{
			if (width <= 0) width = 10;
			this->width = width;
		}
		void set_length(double length)
		{
			if (length <= 0) length = 10;
			this->length = length;
		}
		Rectangle(double width, double length, Color color, unsigned int start_x, unsigned int start_y, unsigned int line_width) : Shape(color, start_x, start_y, line_width)
		{
			set_width(width);
			set_length(length);
		}
		~Rectangle() {}

		double get_area() const
		{
			return width * length;
		}
		double get_perimetr() const
		{
			return (width + length) * 2;
		}
		void draw()const
		{
			HWND hConsole = GetConsoleWindow(); // Получаем окно консоли
			HDC hdc = GetDC(hConsole); // Создаем контекст устройства для полученного окна
			HPEN hPen = CreatePen(PS_SOLID, line_width, color); //Создаем карандаш

			SelectObject(hdc, hPen); // Выбираем созданный карандаш
			HBRUSH hBrush = CreateSolidBrush(color); // Создание кисть, которая закрашивает замкнутые фигуры
			SelectObject(hdc, hBrush); // выбираем созданную кисть (выбираются для того, чтобы функция Rectangle понимала чем рисовать) 
			::Rectangle(hdc, start_x, start_y, start_x + width, start_y + length); // Рисует квадрат 

			// Удаление созданные кисть и карандаш
			DeleteObject(hBrush);
			DeleteObject(hPen);
			ReleaseDC(hConsole, hdc); // освобождение контекста устройства
		}

		void info()const
		{
			std::cout << typeid(*this).name() << std::endl;
			std::cout << "Width: " << width << std::endl;
			std::cout << "Length: " << length << std::endl;
			Shape::info();
		}
	};
	class Circle : public Shape
	{
		double radius;
	public:
		double get_radius()const
		{
			return radius;
		}
		double get_diameter()const
		{
			return radius * 2;
		}
		void set_radius(double radius)
		{
			if (radius <= 0) radius = 10;
			this->radius = radius;
		}
		Circle (double radius, Color color, unsigned int start_x, unsigned int start_y, unsigned int line_width) :Shape(color, start_x, start_y, line_width)
		{
			set_radius(radius);
		}
		~Circle() {}
		double get_area()const
		{
			return M_PI * radius * radius;
		}
		double get_perimetr()const
		{
			return 2 * M_PI * radius;
		}
		void draw()const
		{
			HWND hConsole = GetConsoleWindow(); 
			HDC hdc = GetDC(hConsole); 
			HPEN hPen = CreatePen(PS_SOLID, line_width, color); 

			SelectObject(hdc, hPen); 
			HBRUSH hBrush = CreateSolidBrush(color); 
			SelectObject(hdc, hBrush); 
			::Ellipse(hdc, start_x, start_y, start_x + get_diameter(), start_y + get_diameter()); 

			DeleteObject(hBrush);
			DeleteObject(hPen);
			ReleaseDC(hConsole, hdc); 
		}
		void info()const
		{
			std::cout << typeid(*this).name() << std::endl;
			std::cout << "Radius: " << radius << std::endl;
			Shape::info();
		}
	};
}


int main()
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD buffer = { 16, 16 };
	//SetConsoleDisplayMode(hConsole, CONSOLE_FULLSCREEN_MODE, &buffer);

	// Square //
	Geometry::Square Square(250, Geometry::Color::blue, 200, 450, 5);
	/*std::cout << "Square side:\t" << Square.get_side() << std::endl;
	std::cout << "Square area:\t" << Square.get_area() << std::endl;
	std::cout << "Square perimeter:\t" << Square.get_perimetr() << std::endl;*/
	Square.info();
	std::cout << std::endl;
	Square.draw();

	// Rectangle //

	Geometry::Rectangle Rect(300, 150, Geometry::Color::red, 1000, 1300, 5);
	Rect.info();
	std::cout << std::endl;
	Rect.draw();

	// Circle //

	Geometry::Circle circle(150, Geometry::Color::green, 300, 400, 5);
	circle.info();


	return 0;
}
