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
Computer::Computer(
    string cpu,
    string gpu,
    string monitor,
    string keyboard,
    bool hasCdRom,
    bool hasFloppyDisk,
    int sizeOfRom,
    int inventoryNumber,
    int auditoriumNumber):
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

//Set-метод
void Computer::SetComputer(
	string cpu,
	string gpu,
	string monitor,
	string keyboard,
	bool hasCdRom,
	bool hasFloppyDisk,
	int sizeOfRom,
	int inventoryNumber,
	int auditoriumNumber)
{
        m_cpu = cpu;
        m_gpu = gpu;
	    m_monitor = monitor;
	    m_keyboard = keyboard;
	    m_hasCdRom = hasCdRom;
	    m_hasFloppyDisk = hasFloppyDisk;
	    m_sizeOfRom = sizeOfRom;
	    m_inventoryNumber = inventoryNumber;
	    m_auditoriumNumber = auditoriumNumber;
};

//Get-метод
string Computer::GetComputer()
{
  return
   "Cpu: " + m_cpu
  + " Gpu: " + m_gpu
  + " Monitor: " + m_monitor
  + " Keyboard: " + m_keyboard
  + " Has CD-ROM? " + (m_hasCdRom ? "Yes" : "No")
  + " Has Floppy disk? " + (m_hasFloppyDisk ? "Yes" : "No")
  + " ROM capacity: " + to_string(m_sizeOfRom)
  + " Inventory number: " + to_string(m_inventoryNumber)
  + " Auditor number: " + to_string(m_auditoriumNumber);
};

//Копіювальний конструктор
Computer::Computer(const Computer &other):
	m_cpu{other.m_cpu},
    m_gpu{other.m_gpu},
	m_monitor{other.m_monitor},
	m_keyboard{other.m_keyboard},
	m_hasCdRom{other.m_hasCdRom},
	m_hasFloppyDisk{other.m_hasFloppyDisk},
	m_sizeOfRom{other.m_sizeOfRom},
	m_inventoryNumber{other.m_inventoryNumber},
	m_auditoriumNumber{other.m_auditoriumNumber}
{
};

//Конструктор переміщення
Computer::Computer(Computer &&other) noexcept:
	m_cpu{other.m_cpu},
	m_gpu{other.m_gpu},
	m_monitor{other.m_monitor},
	m_keyboard{other.m_keyboard},
	m_hasCdRom{other.m_hasCdRom},
	m_hasFloppyDisk{other.m_hasFloppyDisk},
	m_sizeOfRom{other.m_sizeOfRom},
	m_inventoryNumber{other.m_inventoryNumber},
	m_auditoriumNumber{other.m_auditoriumNumber}
{
};

// Метод демонстрування стану
void Computer::ShowStatus()
{
	cout << "Unknown status" << endl;
};

// Метод демонстрування вартості осблуговування
int Computer::ServiceCost()
{
  	return 0;
};

// Метод який змінює номер аудиторії де знаходиться ПК
void Computer::MoveAuditorium(int number)
{
  cout << "Write new number auditorium" << endl;
  cin >> number;
  m_auditoriumNumber = number;
};

//Деструктор
Computer::~Computer() 
{
	cout << "Destructor of abstract class is called";
};