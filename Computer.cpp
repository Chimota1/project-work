#include "Computer.h"
#include "iostream"

using namespace std;

//Конструктор за замовчуванням
Computer::Computer():
	m_cpu{"unknown"},
	m_gpu{"unknown"},
    m_monitor{"unknown"},
    m_keyboard{"unknown"},
    m_hasCdRom{false},
    m_hasFloppyDisk{false},
    m_sizeOfRom{0},
    m_inventoryNumber{0},
    m_auditoriumNumber{0}
	{
    };

//Конструктор з параметрами
Computer::Computer(string cpu,string gpu,string monitor,string keyboard,bool hasCdRom,bool hasFloppyDisk,int sizeOfRom,int inventoryNumber,int auditoriumNumber):
	m_cpu{cpu},
	m_gpu{gpu},
	m_monitor{monitor},
	m_keyboard{keyboard},
	m_hasCdRom{hasCdRom},
	m_hasFloppyDisk{hasFloppyDisk},
	m_sizeOfRom{sizeOfRom},
	m_inventoryNumber{inventoryNumber},
	m_auditoriumNumber{auditoriumNumber}
{
};


Computer::~Computer() 
{
	cout << "Destructor of abstract class is called";
};