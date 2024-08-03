#include "SerialPort.h"

SerialPort::SerialPort(char* name, DWORD bRate)
{
	isOpen = false;
	baudeRate = bRate;
	portName = name;
}

SerialPort::~SerialPort()
{
	if (handle == NULL)
		return;

	CloseHandle(handle);
}

bool SerialPort::Open()
{
	handle = CreateFileA(static_cast<LPCSTR>(portName), GENERIC_READ | GENERIC_WRITE,
		0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (handle == INVALID_HANDLE_VALUE) {
        return false;
	}

    DCB dcbSerialParams = { 0 };
    dcbSerialParams.DCBlength = sizeof(dcbSerialParams);

    if (!GetCommState(handle, &dcbSerialParams)) {
        Close();
        return false;
    }

    dcbSerialParams.BaudRate = baudeRate;
    dcbSerialParams.ByteSize = 8;
    dcbSerialParams.StopBits = ONESTOPBIT;
    dcbSerialParams.Parity = NOPARITY;

    if (!SetCommState(handle, &dcbSerialParams)) {
        Close();
        return false;
    }

    COMMTIMEOUTS timeouts = { 0 };
    timeouts.ReadIntervalTimeout = 50;
    timeouts.ReadTotalTimeoutConstant = 50;
    timeouts.ReadTotalTimeoutMultiplier = 10;
    timeouts.WriteTotalTimeoutConstant = 50;
    timeouts.WriteTotalTimeoutMultiplier = 10;

    if (!SetCommTimeouts(handle, &timeouts)) {
        Close();
        return false;
    }

    isOpen = true;
    return true;
}

void SerialPort::Close()
{
    if (handle != NULL) {
        CloseHandle(handle);
        handle = NULL;
    }

    isOpen = false;
}

int SerialPort::Write(const char* data, DWORD length)
{
    if (handle == NULL) {
        return -1;
    }

    DWORD bytesWritten;
    if (!WriteFile(handle, data, length, &bytesWritten, NULL)) {
        return -1;
    }

    return bytesWritten;
}

int SerialPort::Read(char* buffer, DWORD bufferSize)
{
    if (handle == NULL) {
        return -1;
    }

    DWORD bytesRead;
    if (!ReadFile(handle, buffer, bufferSize, &bytesRead, NULL)) {
        return -1;
    }

    return bytesRead;
}

bool SerialPort::IsOpen() const
{
	return isOpen;
}

SerialPort* Internal_CreateSerialPort(char* portName, DWORD baudeRate)
{
    SerialPort* obj = new SerialPort(portName, baudeRate);
    return obj;
}

void Internal_DestroySerialPort(SerialPort* obj)
{
    delete obj;
}

bool Internal_Open(SerialPort* obj)
{
    return obj->Open();
}

void Internal_Close(SerialPort* obj)
{
    obj->Close();
}

int Internal_Write(SerialPort* obj, const char* data, DWORD length)
{
	return obj->Write(data, length);
}

int Internal_Read(SerialPort* obj, char* buffer, DWORD bufferSize)
{
	return obj->Read(buffer, bufferSize);
}

bool Internal_IsOpen(SerialPort* obj)
{
	return obj->IsOpen();
}
