#ifndef COMPUTER_H
#define COMPUTER_H

#include <string>

using namespace std;

class Computer
{
public:
	Computer();
	~Computer();

private:
	string cpu;
	string gpu;
	string monitor;
	string keyboard;
	int sizeOfRom;
    int inventoryNumber;
};
#endif // COMPUTER_H