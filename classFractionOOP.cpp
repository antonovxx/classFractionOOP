#include<iostream>
using std::cin;
using std::cout;
using std::endl;

//#define OPERATORS_CHECK
#pragma warning (disable: 4356)

//#define TYPE_CONVERSIONS_BASICS
//#define HOMEWORK

class Fraction;
Fraction operator*(Fraction left, Fraction right);



class Fraction
{
	int integer;
	int numerator;
	int denominator;
public:
	int get_integer()const
	{
		return integer;
	}
	int get_numerator()const
	{
		return numerator;
	}
	int get_denominator()const
	{
		return denominator;
	}
	void set_integer(int integer)
	{
		this->integer = integer;
	}
	void set_numerator(int numerator)
	{
		this->numerator = numerator;
	}
	void set_denominator(int denominator)
	{
		if (denominator == 0)denominator = 1;	//Отфильтровываем 0
		this->denominator = denominator;
	}
	//				Constructors:
	Fraction()
	{
		this->integer = 0;
		this->numerator = 0;
		this->denominator = 1;
		cout << "DefaultConstruct:\t" << this << endl;
	}
	explicit Fraction(int integer)
	{
		this->integer = integer;
		this->numerator = 0;
		this->denominator = 1;
		cout << "1argConstructor:\t" << this << endl;
	}
	Fraction(double decimal)
	{
		decimal += 1e-11;
		integer = decimal;
		denominator = 1e+9; // 1 * 10^9 = 1 в 9 степени
		decimal -= integer; // Убираем целую часть из десятичной дроби
		numerator = decimal * denominator;
		reduce();
	}
	Fraction(int numerator, int denominator)
	{
		this->integer = 0;
		this->numerator = numerator;
		set_denominator(denominator);	//Чтобы не обойти фильтрацию данных
		cout << "Constructor:\t" << this << endl;
	}
	Fraction(int integer, int numerator, int denominator)
	{
		this->integer = integer;
		this->numerator = numerator;
		set_denominator(denominator);
		cout << "Constructor:\t" << this << endl;
	}
	~Fraction()
	{
		cout << "Destructor:\t" << this << endl;
	}

	//                            Operators:
	Fraction& operator=(const Fraction& other)
	{
		this->integer = other.integer;
		this->numerator = other.numerator;
		this->denominator = other.denominator;
		cout << "Copy Assignment: \t" << this << endl;
		return* this;
	}

	Fraction& operator*= (const Fraction& other)
	{
		return *this = *this * other;
	}
	// Type- cast operators:
	
	explicit operator int() const
	{
		return integer;
	}
	operator double() const
	{
		return integer + (double) numerator / denominator; //
	}
	//					Methods:
	Fraction& to_improper()//Переводит дробь в неправильну
	{
		numerator += integer * denominator;
		integer = 0;
		return *this;

	}
	Fraction& to_proper()//Переводит дробь в правильную
	{
		integer += numerator / denominator;
		numerator %= denominator;
		//numerator = numerator % denominator;
		return *this;
	}
	Fraction& reduce()
	{
		if (numerator == 0) return *this;

		int more, less;
		int rest;
		if (numerator > denominator)
		{
			more = numerator;
			less = denominator;
		}
		else
		{
			less = numerator;
			more = denominator;
		}
		do
		{
			rest = more % less;
			more = less;
			less = rest;
		} while (rest);
		int GCD = more; // GCD - greatest common divisor
		numerator /= GCD;
		denominator /= GCD;
		return *this;
	}

	Fraction inverted()
	{
		to_improper();
		return Fraction(this->denominator, this->numerator);
	}

	std::ostream& print(std::ostream& os)const
	{
		if (integer)os << integer;//Если есть целая часть, выводим ее на экран
		if (numerator)
		{
			if (integer)os << "(";
			os << numerator << "/" << denominator;
			if (integer)os << ")";
		}
		else if (integer == 0)os << 0;
		return os;
	}
};

Fraction operator*(Fraction left, Fraction right)
{
	left.to_improper();
	right.to_improper();
	//Fraction result
	//(
	//	left.get_numerator() * right.get_numerator(),
	//	left.get_denominator() * right.get_denominator()
	//);
	/*result.set_numerator(left.get_numerator()*right.get_numerator());
	result.set_denominator(left.get_denominator()*right.get_denominator());*/
	//result.to_proper();
	//return result;
	return Fraction
	(
		left.get_numerator() * right.get_numerator(),
		left.get_denominator() * right.get_denominator()
	).to_proper().reduce(); // Явный вызов конструктора, который вызывает временный безымянный объект
}

Fraction operator/(Fraction left, Fraction right)
{
	return left * right.inverted();
}

std::ostream& operator<<(std::ostream& os, const Fraction& obj)
{
	/*if (obj.get_integer())os << obj.get_integer();//Если есть целая часть, выводим ее на экран
	if (obj.get_numerator())
	{
		if (obj.get_integer())os << "(";
		os << obj.get_numerator() << "/" << obj.get_denominator();
		if (obj.get_integer())os << ")";
	}
	else if (obj.get_integer() == 0)os << 0;
	return os;*/
	return obj.print(os);
}
std::istream& operator>> (std::istream& is, Fraction& obj)
{
	//int integer;
	//int numerator;
	//int denominator;
	//is >> integer >> numerator >> denominator;
	//obj.set_integer(integer);
	//obj.set_numerator(numerator);
	//obj.set_denominator(denominator);
	//return is;
	obj = Fraction(); // Обнуление объекта
	const int SIZE = 256;
	char buffer[SIZE] = {};
	char delimiters[] = "() /";
	is.getline(buffer, SIZE);
	char* number[3] = {}; // этот массив будет хранить части строки, полученные при помощи strtok
	int n = 0;  // индекс элемента в массиве number;

	for(char* pch = strtok(buffer, delimiters); pch; pch = strtok(NULL, delimiters))
	{
		number[n++] = pch;
	}
	//for (size_t i = 0; i < n; i++)
	//{
	//	cout << number[i] << "\t";
	//}

	switch (n)
	{
	case 1: 
		obj.set_integer(atoi(number[0])); break;
	case 2: 
		obj.set_numerator(atoi(number[0]));
		obj.set_denominator(atoi(number[1]));
		break;
	case 3:
		obj.set_integer(atoi(number[0]));
		obj.set_numerator(atoi(number[1]));
		obj.set_denominator(atoi(number[2]));
	}

	return is;
}

//#define CONSTRUCTORS_CHECK
//#define OPERATORS_CHECK
//#define CONVERSIONS_FROM_OTHER_TO_CLASS

int main()
{
	setlocale(LC_ALL, "");
#ifdef CONSTRUCTORS_CHECK
	Fraction A;	//Default constructor
	A.print();
	double b = 5;
	Fraction B = 5;	//Single-argument constructor
	B.print();
	//Fraction C(7);	//Single-argument constructor
	//C.print();
	//Fraction D{ 8 };//Single-argument constructor
	//D.print();
	Fraction C(3, 4);
	C.print();
	Fraction D(2, 3, 4);
	D.print();
#endif // CONSTRUCTORS_CHECK

#ifdef OPERATORS_CHECK
	double a = 2.5;
	double b = 3.4;
	double c = a * b;
	cout << c << endl;

	Fraction A(2, 1, 2);
	Fraction B(3, 2, 5);
	/*Fraction C = A * B;
	C.reduce();
	C.print();*/

	//Fraction D(840, 3600);
	//D.reduce().print();

	/*C = A / B;
	C.print();*/

	A *= B;
	A.print();
#endif // OPERATORS_CHECK



#ifdef OPERATORS_CHECK
	// space for hw
#endif

#ifdef TYPE_CONVERSIONS_BASICS

	int a = 2;
	double b = 3;

	int c = b;
	int d = 4.5;
	cout << d << endl;
#endif // TYPE_CONVERSIONS_BASICS

#ifdef CONVERSIONS_FROM_OTHER_TO_CLASS
	double a = 2; //  from int to double
	Fraction A = 5; // from int to fraction
	A.print();

	Fraction B;
	B = 8;   // Copy Assignment 
	B.print();

	Fraction C = 12; // explicit constructor is imposible to call
	Fraction C(12); // вызов через explicit
	Fraction D{ 13 };

#endif // CONVERSIONS_FROM_OTHER_TO_CLASS

#ifdef HOMEWORK
	Fraction A(2, 4, 5);
	double a = A;
	cout << a << endl;

	double b = 2.76;
	Fraction B = b;
	B.print();
#endif

	Fraction A(2, 3, 4);
	cout << A << endl;

	cout << "Enter simple fraction: "; cin >> A;
	cout << A << endl;


	return 0;
}



