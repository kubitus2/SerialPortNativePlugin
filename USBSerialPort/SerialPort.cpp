#include "pch.h"
#include "SerialPort.h"

SerialPort::SerialPort(char* name, DWORD bRate)
{
	portName = name;
	baudRate = bRate;
	isOpen = false;
	handle = NULL;
}

SerialPort::~SerialPort()
{
	Close();
}

bool SerialPort::Open()
{
	handle = CreateFileA(static_cast<LPCSTR>(portName), GENERIC_READ | GENERIC_WRITE,
		0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (handle == INVALID_HANDLE_VALUE)
		return false;

	DCB dcbSerialParams = { 0 };

    if (!GetCommState(handle, &dcbSerialParams)) {
        CloseHandle(handle);
        return false;
    }

    dcbSerialParams.BaudRate = baudRate;
    dcbSerialParams.ByteSize = 8;
    dcbSerialParams.StopBits = ONESTOPBIT;
    dcbSerialParams.Parity = NOPARITY;

    if (!SetCommState(handle, &dcbSerialParams)) {
        CloseHandle(handle);
        return false;
    }

    COMMTIMEOUTS timeouts = { 0 };
    timeouts.ReadIntervalTimeout = 50;
    timeouts.ReadTotalTimeoutConstant = 50;
    timeouts.ReadTotalTimeoutMultiplier = 10;
    timeouts.WriteTotalTimeoutConstant = 50;
    timeouts.WriteTotalTimeoutMultiplier = 10;

    if (!SetCommTimeouts(handle, &timeouts)) {
        CloseHandle(handle);
        return false;
    }

    return true;
}

void SerialPort::Close()
{
    if (handle == NULL)
        return;

    CloseHandle(handle);
}

int SerialPort::Write(const char* data, DWORD length)
{
    if (handle == NULL)
        return -1;

    DWORD bytesWritten;

    if (!WriteFile(handle, data, length, &bytesWritten, NULL))
    {
        return -1;
    }

    return bytesWritten;
}

int SerialPort::Read(char* buffer, DWORD bufferSize)
{
    if (handle == NULL)
        return -1;

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
