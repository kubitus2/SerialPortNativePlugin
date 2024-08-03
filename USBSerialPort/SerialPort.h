#pragma once

#include <windows.h>
#include <string>

#ifdef SERIALPORT_EXPORTS
#define EXPORT __declspec(dllexport)
#else
#define EXPORT __declspec(dllimport)
#endif

class EXPORT SerialPort {
private:
	HANDLE handle;
	bool isOpen;
	DWORD baudRate;
	char* portName;
public:
	SerialPort(char* portName, DWORD baudRate);
	~SerialPort();

	bool Open();
	void Close();
	int Write(const char* data, DWORD length);
	int Read(char* buffer, DWORD bufferSize);
	bool IsOpen() const;
};