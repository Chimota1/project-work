#include "Computer.h"
#include <iostream>
#include <exception>

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

void Computer::SetCpu(string cpu) {
	m_cpu = cpu;
};

void Computer::SetGpu(string gpu) {
	m_gpu = gpu;
};

void Computer::SetMonitor(string monitor) {
	m_monitor = monitor;
};

void Computer::SetKeyboard(string keyboard) {
	m_keyboard = keyboard;
};

void Computer::SetHasCdRom(bool hasCdRom) {
	m_hasCdRom = hasCdRom;
};

void Computer::SetHasFloppyDisk(bool hasFloppyDisk) {
	m_hasFloppyDisk = hasFloppyDisk;
};


string Computer::GetCpu() {
	return m_cpu;
};

string Computer::GetGpu() {
	return m_gpu;
}

string Computer::GetMonitor() {
	return m_monitor;
}

string Computer::GetKeyboard() {
	return m_keyboard;
}

bool Computer::GetHasCdRom() {
	return m_hasCdRom;
}

bool Computer::GetHasFloppyDisk() {
	return m_hasFloppyDisk;
}


//Get-метод
string Computer::GetComputerFull()
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
Computer::Computer(const Computer &other)
{
	this->m_cpu = other.m_cpu;
	this->m_gpu = other.m_gpu;
	this->m_keyboard = other.m_keyboard;
	this->m_monitor = other.m_monitor;
	this->m_auditoriumNumber = other.m_auditoriumNumber;
	this->m_inventoryNumber = other.m_auditoriumNumber;
	this->m_hasCdRom = other.m_hasCdRom;
	this->m_hasFloppyDisk = other.m_hasFloppyDisk;
	this->m_sizeOfRom = other.m_sizeOfRom;
};

//Конструктор переміщення
Computer::Computer(Computer &&other) noexcept
{
	this->m_cpu = other.m_cpu;
	this->m_gpu = other.m_gpu;
	this->m_keyboard = other.m_keyboard;
	this->m_monitor = other.m_monitor;
	this->m_auditoriumNumber = other.m_auditoriumNumber;
	this->m_inventoryNumber = other.m_auditoriumNumber;
	this->m_hasCdRom = other.m_hasCdRom;
	this->m_hasFloppyDisk = other.m_hasFloppyDisk;
	this->m_sizeOfRom = other.m_sizeOfRom;
};

// Метод який змінює номер аудиторії де знаходиться ПК
void Computer::MoveAuditorium(int number)
{
  cout << "Write new number auditorium" << endl;
  cin >> number;
  m_auditoriumNumber = number;
};

void Computer::HasCdRomUpdate(bool hasCdRom)
{
  cout << "Update (1 if have, 0 if have not)" << endl;
  cin >> hasCdRom;
  m_hasCdRom = hasCdRom;
};

void Computer::HasFloppyDisk(bool hasFloppyDisk)
{
  cout << "Update (1 if have, 0 if have not)" << endl;
  cin >> hasFloppyDisk;
  m_hasFloppyDisk = hasFloppyDisk;
};


//Деструктор
Computer::~Computer() 
{
	cout << "Destructor of abstract class is called";
};