#include "atmega.h"
#include "serialib.h"

bool Atmega::_openDevice()
{
    char errorOpening = serial.openDevice("/dev/ttyUSB0", 9600);

    return device_open;
} 

void Atmega::write_close_Grip()
{
    _openDevice();
    int8_t num = 240;
    int8_t buffer[1] = {num};
    sleep(5);
    start = std::chrono::system_clock::now();
    serial.writeBytes(buffer,1);

}

void Atmega::write_open_Grip()
{
    _openDevice();
    int8_t num = 15;
    int8_t buffer[1] = {num};
    sleep(5);
    serial.writeBytes(buffer,1);

}

void Atmega::read_Value()
{
    _openDevice();

    uint8_t buffer[1];
    uint8_t val;
    while (true)
    {
        serial.readBytes(buffer, '\n', 1);
        val = buffer[0];
        if (val == 69)
        {
            this-> value = val;
            end = std::chrono::system_clock::now();
            this-> time = end - start;
            break;
        }
    }
}

void Atmega::stop_Value()
{
    _openDevice();

    uint8_t buffer[1];
    uint8_t val;
    while (true)
    {
        serial.readBytes(buffer, '\n', 2);
        val = buffer[0];
        if (val == 42)
        {
            this->value = val;
            break;
        }
    }
}

uint8_t Atmega::getValue()
{
    return value;
}

std::chrono::duration<double> Atmega::getTime()
{
    return time;
}
