#include <iostream>
using std::cin;
using std::cout;
using std::endl;

#define delimiter "\n-------------------------------------------\n"


/// <summary>
/// CLASS DECLARATION
/// </summary>


class String;
String operator+(const String& left, const String& right);

class String
{
	int size; 
	char* str; 
public:
	int get_size()const;
	const char* get_str() const; 
		
	char* get_str(); 

	explicit String(int size = 80);

	String(const char str[]);

	String(const String& other);

	String(String&& other)noexcept
	{
		//// Move-Constructor - do shallow copy
		//this->size = other.size;
		//this->str = other.str; //просто копируем адрес памяти, принадлежащей другому объекту
		//// Зануляем другой объект, чтобы его память не смог удалить деструктор
		//other.size = 0;
		//other.str = nullptr;
		this->str = nullptr;
		*this = std::move(other);
		cout << "Move - constructor" << this << endl;
	}

	~String();

	// Operators
	String& operator= (const String& other);

	String& operator+= (const String& other);

	String& operator=(String&& other)noexcept;

	const char& operator[](int i)const;

	char& operator[](int i);

	// Methods

	void print() const;
};

/// <summary>
/// CLASS DECLARATION - END
/// </summary>
/// <returns></returns>

int String::get_size()const
{
	return size;
}
const char* String::get_str() const // this is constant method for encapsulation
	// returns the constant pointer
{
	return str;
}
char* String::get_str() // unconstant method
{
	return str;
}
String::String(int size) :size(size), str(new char[size] {}) // Implicit conversion is prohibited
{
	//this->size = size;
	//this->str = new char[size] {}; // the memory allocated for the string must be zeroed
	cout << "Constructor: \t" << this << endl;
}
String::String(const char str[]) :String(strlen(str) + 1)
{
	//this->size = strlen(str) + 1; // + 1 for terminated zero in the end of the array of characters
	//this->str = new char[size] {};
	for (size_t i = 0; str[i]; i++)
	{
		this->str[i] = str[i];
	}
	cout << "Constructor:\t" << this << endl;
}
String::String(const String& other) :String(other.str) // copy-constructor
{
	// Deep copy 
	//this->size = other.size;
	//this->str = new char[size] {};
	//for (size_t i = 0; i < size; i++)
	//{
	//	this->str[i] = other.str[i];
	//}
	cout << "CopyConstructor: \t" << this << endl;
}


String::~String()
{
	delete[] str;
	cout << "Destructor:\t" << this << endl;
}
// Operators
String& String::operator= (const String& other)
{
	// We check this and other if it is the same object
	if (this == &other) return *this; // Any assignment operator strats from this
	delete[] this->str; // then we delete last oject of the memory
	// Then just copy code from copy constructor
	this->size = other.size;
	this->str = new char[size] {};
	for (size_t i = 0; i < size; i++)
	{
		this->str[i] = other.str[i];
	}
	cout << "CopyAssignment: \t" << this << endl;
	return *this;
}

String& String::operator=(String&& other)noexcept
{
	delete this->str;
	this->size = other.size;
	this->str = other.str;

	other.size = 0;
	other.str = 0;
	cout << "MoveAssignment: \t" << this << endl;
	return *this;
}

String& String::operator+= (const String& other)
{
	return *this = *this + other;
}

const char& String::operator[](int i)const
{
	return str[i];
}

char& String::operator[](int i)
{
	return str[i];
}

// Methods

void String::print()const
{
	cout << "Size: " << size << endl;
	cout << "Str: \t" << str << endl;
}


String operator+(const String& left, const String& right)
{
	// allocate memory for new object
	String result(left.get_size() + right.get_size() - 1); // - 1 deletes one terminated zero
	for (size_t i = 0; i < left.get_size(); i++)
	{
		result.get_str()[i] = left.get_str()[i];
	}

	for (size_t i = 0; i < right.get_size(); i++)
	{
		result.get_str()[i + left.get_size() - 1] = right.get_str()[i];
	}

	return result;
}

//#define CONSTRUCTORS_CHECK
#define OPERATORS_CHECK
//#define INPUT_CHECK

std::ostream& operator<< (std::ostream& os, const String& obj) // cout is an object of the ostream
// we cannot duplicate streams of output, so we need use the reference here
{
	return os << obj.get_str();
}
std::istream& operator >> (std::istream& is, String& obj)
{
	//return is >> obj.get_str();
	const int SIZE = 10240;
	char buffer[SIZE] = {};
	is >> buffer;
	obj = buffer;
	return is;
}

std::istream& getline(std::istream& is, String& obj)
{
	const int SIZE = 1024 * 1000;
	char buffer[SIZE] = {};
	is.getline(buffer, SIZE);
	obj = buffer;
	return is;
}

void main()
{
#ifdef CONSTRUCTORS_CHECK
	String str1; // Default constructor
	str1.print();
	cout << str1 << endl;

	String str2(25); // Single-argument constructor
	str2.print();

	String str3 = "Hello";
	str3 = str3;
	cout << str3 << endl;

	String str4 = str3; // Copy constructor
	// Deep copy
	// Shallow copy
	//Debug Assertation Failed
	cout << str4 << endl;

	String str5;
	str5 = str3; // Needed copyAssignment (operator =)
	cout << str5 << endl;
#endif // CONSTRUCTORS_CHECK

#ifdef OPERATORS_CHECK
	String str1 = "Hello";
	String str2 = "World";
	cout << delimiter << endl;
	String str3;
	str3 = str1 + str2;
	cout << delimiter << endl;
	cout << str3 << endl;
	cout << delimiter << endl;
//	str1 += str2;
//	cout << delimiter << endl;
//	cout << str1 << endl;

#endif // OPERATORS_CHECK

#if INPUT_CHECK
	String str;
	cout << "Enter the line: " << endl;
	//cin >> str;
	getline(cin, str);
	cout << str << endl;
	str.print();
#endif // INPUT_CHECK

}