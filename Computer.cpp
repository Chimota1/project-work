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

Computer::~Computer() 
{
	cout << "Destructor of abstract class is called";
};