#include "Computer.h"
#include "iostream"

using namespace std;

//Конструктор за замовчуванням
Computer::Computer():
	cpu{"unknown"},
	gpu{"unknown"},
    monitor{"unknown"},
    keyboard{"unknown"},
    hasCdRom{false},
    hasFloppyDisk{false},
    sizeOfRom{0},
    inventoryNumber{0},
    auditoriumNumber{0}
	{
    };

//Конструктор з параметрами
Computer::Computer(string cpu,string gpu,string monitor,string keyboard,bool hasCdRom,bool hasFloppyDisk,int sizeOfRom,int inventoryNumber,int auditoriumNumber):
	cpu{cpu},
	gpu{gpu},
	monitor{monitor},
	keyboard{keyboard},
	hasCdRom{hasCdRom},
	hasFloppyDisk{hasFloppyDisk},
	sizeOfRom{sizeOfRom},
	inventoryNumber{inventoryNumber},
	auditoriumNumber{auditoriumNumber}
{
};


Computer::~Computer() 
{
	cout << "Destructor of abstract class is called";
};