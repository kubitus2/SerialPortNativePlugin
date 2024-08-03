#pragma once
#include "SerialPort.h"

#ifdef SERIALPORT_EXPORTS
#define EXPORT __declspec(dllexport)
#else
#define EXPORT __declspec(dllimport)
#endif

extern "C" {
	EXPORT SerialPort* Internal_CreateSerialPort(char* portName, DWORD baudRate);
	EXPORT void Internal_DestroySerialPort(SerialPort* obj);

	EXPORT bool Internal_Open(SerialPort* obj);
	EXPORT void Internal_Close(SerialPort* obj);
	EXPORT int Internal_Write(SerialPort* obj, const char* data, DWORD length);
	EXPORT int Internal_Read(SerialPort* obj, char* buffer, DWORD bufferSize);
	EXPORT bool Internal_IsOpen(SerialPort* obj);
}