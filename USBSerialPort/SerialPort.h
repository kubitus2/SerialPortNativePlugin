#pragma once
#include <windows.h>
#include <string>


#ifdef SERIALPORT_EXPORTS
#define SERIALPORT_API __declspec(dllexport)
#else
#define SERIALPORT_API __declspec(dllimport)
#endif

class SerialPort {
private:
	HANDLE handle;
	bool isOpen;
	DWORD baudeRate;
	char* portName;
public:
	SerialPort(char* portName, DWORD baudeRate);
	~SerialPort();

	bool Open();
	void Close();
	int Write(const char* data, DWORD length);
	int Read(char* buffer, DWORD bufferSize);
	bool IsOpen() const;
};

extern "C" {
	SerialPort* Internal_CreateSerialPort(char* portName, DWORD baudeRate);
	void Internal_DestroySerialPort(SerialPort* obj);

	bool Internal_Open(SerialPort* obj);
	void Internal_Close(SerialPort* close);
	int Internal_Write(SerialPort* obj, const char* data, DWORD length);
	int Internal_Read(SerialPort* obj, const char* buffer, DWORD bufferSize);
	bool Internal_IsOpen(SerialPort* obj);
}