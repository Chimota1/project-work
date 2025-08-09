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
  		cout << "write name CPU" ;
  		cin >> cpu;
        cpu = m_cpu;
  		cout << " write name GPU ";
  		cin >> gpu;
        gpu = m_gpu;
    	cout << " write name monitor ";
    	cin >> monitor;
	    monitor = m_monitor;
    	cout << "write type of keyboard";
    	cin >> keyboard;
	    keyboard = m_keyboard;
    	cout << "write have PC CD-ROM?\"if have write 1, else write 0";
    	cin >> hasCdRom;
	    hasCdRom = m_hasCdRom;
    	cout << "write have PC Floppy disk?\"if have write 1, else write 0";
    	cin >> hasFloppyDisk;
	    hasFloppyDisk = m_hasFloppyDisk;
    	cout << "write size of ROM";
    	cin >> sizeOfRom;
	    sizeOfRom = m_sizeOfRom;
    	cout << "write inventory number PC";
        cin >> inventoryNumber;
	    inventoryNumber = m_inventoryNumber;
        cout << "write auditorium number";
        cin >> auditoriumNumber;
	    auditoriumNumber = m_auditoriumNumber;
};

//Get-метод
void Computer::GetComputer()
{
  cout
  << "Cpu: " << m_cpu
  << " Gpu: " << m_gpu
  << " Monitor: " << m_monitor
  << " Keyboard: " << m_keyboard
  << " Has CD-ROM? " << m_hasCdRom
  << " Has Floppy disk? " << m_hasFloppyDisk
  << " ROM capacity: " << m_sizeOfRom
  << " Inventory number: " << m_inventoryNumber
  << " Auditor number: " << m_auditoriumNumber;
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
Computer::Computer(const Computer &&other):
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

//Деструктор
Computer::~Computer() 
{
	cout << "Destructor of abstract class is called";
};