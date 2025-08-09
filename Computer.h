#ifndef COMPUTER_H
#define COMPUTER_H

#include <string>

using namespace std;

class Computer
{
public:
	Computer();
    Computer(
    	string cpu,
        string gpu,
        string monitor,
        string keyboard,
        bool hasCdRom,
        bool hasFloppyDisk,
        int sizeOfRom,
        int inventoryNumber,
        int auditoriumNumber);
	~Computer();

private:
	string cpu;
	string gpu;
	string monitor;
	string keyboard;
    bool hasCdRom;
    bool hasFloppyDisk;
	int sizeOfRom;
    int inventoryNumber;
    int auditoriumNumber;
};
#endif // COMPUTER_H