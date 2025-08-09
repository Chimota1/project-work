#include "Computer.h"
#include "iostream"

using namespace std;

Computer::Computer() {};

Computer::~Computer() 
{
	cout << "Destructor of abstract class is called";
};