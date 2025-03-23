#include "serialib.h"
#include <iostream>
#include <cstdlib>
#include <chrono>

#ifndef ATMEGA
#define ATMEGA

class Atmega
{
private:
    serialib serial;

    std::chrono::time_point<std::chrono::system_clock> start;
    std::chrono::time_point<std::chrono::system_clock> end;
    std::chrono::duration<double> time;

    bool device_open;
    
    uint8_t value;

public:
    Atmega() : device_open(false) {}

    bool _openDevice();

    void write_close_Grip();
    void write_open_Grip();
    void read_Value();
    void stop_Value();

    uint8_t getValue();
    std::chrono::duration<double> getTime();

    
};

#endif
