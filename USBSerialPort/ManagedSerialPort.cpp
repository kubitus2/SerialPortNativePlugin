#include "SerialPort.h"
#include "pch.h"
#include "ManagedSerialPort.h"

SerialPort* Internal_CreateSerialPort(char* portName, DWORD baudRate)
{
    SerialPort* port = new SerialPort(portName, baudRate);
    return port;
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
