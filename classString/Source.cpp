#include "String.h"

#define delimiter "\n-------------------------------------------\n"


//#define CONSTRUCTORS_CHECK
//#define OPERATORS_CHECK

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

#if OPERATORS_CHECK
	String str1 = "Hello";
	String str2 = "World";
	cout << delimiter << endl;
	String str3 = str1 + str2;
	cout << delimiter << endl;
	cout << str3 << endl;
	cout << delimiter << endl;
	str1 += str2;
	cout << delimiter << endl;
	cout << str1 << endl;
#endif // OPERATORS_CHECK

	String str;
	cout << "Enter the line: " << endl;
	//cin >> str;
	getline(cin, str);
	cout << str << endl;
	str.print();
}