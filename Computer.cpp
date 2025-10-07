#include "Computer.h"
#include <iostream>
#include "Exeption.h"
#include <string>

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
	if (cpu.empty()) throw Exeption("CPU string is empty");
	m_cpu = cpu;
};

void Computer::SetGpu(string gpu) {
	if (gpu.empty()) throw Exeption("GPU string is empty");
	m_gpu = gpu;
};

void Computer::SetMonitor(string monitor) {
	if (monitor.empty()) throw Exeption("Monitor string is empty");
	m_monitor = monitor;
};

void Computer::SetKeyboard(string keyboard) {
	if (keyboard.empty()) throw Exeption("Keyboard string is empty");
	m_keyboard = keyboard;
};

void Computer::SetHasCdRom(bool hasCdRom) {
	if (hasCdRom != 0 && hasCdRom != 1) throw Exeption("hasCdRom must be 0 or 1");
	m_hasCdRom = hasCdRom;
};

void Computer::SetHasFloppyDisk(bool hasFloppyDisk) {
	if (hasFloppyDisk != 0 && hasFloppyDisk != 1) throw Exeption("hasFloppyDisk must be 0 or 1");
	m_hasFloppyDisk = hasFloppyDisk;
};

void Computer::SetSizeOfRom(int sizeOfRom) {
	if (sizeOfRom <= 0) throw Exeption("sizeOfRom must be positive");
	m_sizeOfRom = sizeOfRom;
};

void Computer::SetInventoryNumber(int inventoryNumber) {
	if (inventoryNumber <= 0) throw Exeption("inventoryNumber must be positive");
	m_inventoryNumber = inventoryNumber;
};

void Computer::SetAuditoriumNumber(int auditoriumNumber) {
	if (auditoriumNumber <= 0) throw Exeption("auditoriumNumber must be positive");
	m_auditoriumNumber = auditoriumNumber;
};


string Computer::GetCpu() const
{
	return m_cpu;
};

string Computer::GetGpu() const
{
	return m_gpu;
};

string Computer::GetMonitor() const
{
	return m_monitor;
};

string Computer::GetKeyboard() const
{
	return m_keyboard;
};

bool Computer::GetHasCdRom() const
{
	return m_hasCdRom;
};

bool Computer::GetHasFloppyDisk() const
{
	return m_hasFloppyDisk;
};

int Computer::GetSizeOfRom() const
{
	return m_sizeOfRom;
};

int Computer::GetInventoryNumber() const
{
	return m_inventoryNumber;
};

int Computer::GetAuditoriumNumber() const
{
	return m_auditoriumNumber;
}


//Get-метод
string Computer::GetComputerFull() const
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
	if (number <= 0)
	throw Exeption("number must be greater than 0");
    m_auditoriumNumber = number;
};

void Computer::HasCdRomUpdate(bool hasCdRom)
{
	m_hasCdRom = hasCdRom;
};

void Computer::HasFloppyDisk(bool hasFloppyDisk)
{
	if (hasFloppyDisk != 0 && hasFloppyDisk != 1) throw Exeption("hasFloppyDisk must be 0 or 1");
	m_hasFloppyDisk = hasFloppyDisk;
};


//Деструктор
Computer::~Computer() 
{
	cout << "Destructor of abstract class is called";
};