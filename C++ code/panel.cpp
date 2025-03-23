#include "panel.h"
#include <iostream>
#include "frame.h"
#include <string>
#include <thread>

Atmega atmega; // Atmega instance
bool _stopFlag = false; // A stop flag used in Stop button 
int _failCount = 0; // Failcount occurs when robot did not gripped a brick, then stops
int _failCount_show = 0; // Shows the failcount on screen
int _big_brick = 0; // Visualizes the data look lines 240-242
int _medium_brick = 0; // Visualizes the data look lines 240-242
int _small_brick = 0; // Visualizes the data look lines 240-242 


MyPanel::MyPanel(wxWindow *parent, wxWindowID id, const wxPoint &pos, const wxSize &size, MyFrame* frame) : wxPanel(parent, wxID_ANY, pos, size), frame(frame)
{
    setWait_Close(0); // Reset Wait_Close 
    setWait_Open(0); // Reset Wait_Open
    system("clear");

}

void MyPanel::setPickupLocation()
{
    setX(264); // Setting register to X = 264
    setY(255); // Setting register to Y = 255
    setZ(115); // Setting register to Z = 115
    setCO(1); // Setting Config_Out to 1
}

void MyPanel::setDropoffLocation()
{
    int _Z_drop = 190; // Height in z for UR5 robot
    std::chrono::duration<double, std::ratio<1L, 1L>> duration = atmega.getTime(); // Saving time variable
    int seconds = std::chrono::duration_cast<std::chrono::seconds>(duration).count(); // Change type to int
    while (true)
    {
        if (seconds >= 7 && seconds <= 10) // Condition for Large brick
        {
            setX_drop(0); // Setting register to X = 0
            setY_drop(254); // Setting register to Y = 254
            setZ_drop(_Z_drop);
            _big_brick++; // Last line for visualization of data for big bricks 
            frame -> updateBigBrickText(_big_brick);
            break;
        }
        else if (seconds >= 14 && seconds <= 16) // Condition for Medium brick
        {
            setX_drop(239);
            setY_drop(179);
            setZ_drop(_Z_drop);
            _medium_brick++; // Last line for visualization of data for medium bricks
            frame -> updateMediumBrickText(_medium_brick);
            break;
        }
        else if (seconds >= 20 && seconds <= 23) // Condition for Smallest brick
        {
            setX_drop(458);
            setY_drop(75);
            setZ_drop(_Z_drop);
            _small_brick++; // Last line for visualization of data for small bricks
            frame -> updateSmallBrickText(_small_brick);
            break;
        }
        else if (seconds > 23)
        {
            setCO(0); // Config_out set to 0, Robot will return to the start position
            _failCount++; // Increment _failCount which is by default 
            _failCount_show++; // Increment the failcount that shows on the GUI
            frame -> updateFailText(_failCount_show);

            break;
        }
    }
}

void MyPanel::setX(uint16_t val) // EXAMPLE for all other set functions
{

    modbus_t *ur5 = modbus_new_tcp("192.168.100.11", 502); // Connecting to UR5 ip and port
    modbus_connect(ur5); // Inizialing the connection
    int reg = modbus_write_register(ur5, 128, val); // Writing val input to register 128 in UR5 robot
    if (reg == -1) // If writing fails do this
    {
        std::cout << ("Modbus: Counldn't set x!") << std::endl;
    }
}

void MyPanel::setY(uint16_t val)
{
    modbus_t *ur5 = modbus_new_tcp("192.168.100.11", 502);
    modbus_connect(ur5);
    int reg = modbus_write_register(ur5, 129, val);
    if (reg == -1)
    {
        std::cout << ("Modbus: Counldn't set y!") << std::endl;
    }
}

void MyPanel::setZ(uint16_t val)
{
    modbus_t *ur5 = modbus_new_tcp("192.168.100.11", 502);
    modbus_connect(ur5);
    int reg = modbus_write_register(ur5, 130, val);
    if (reg == -1)
    {
        std::cout << ("Modbus: Counldn't set z!") << std::endl;
    }
}

void MyPanel::setCO(uint16_t val) // Special for Config_Out (CO) the register is 31
{
    modbus_t *ur5 = modbus_new_tcp("192.168.100.11", 502);
    modbus_connect(ur5);
    int reg = modbus_write_register(ur5, 31, val);
    if (reg == -1)
    {
        std::cout << ("Modbus: Counldn't set CO!") << std::endl;
    }
}

void MyPanel::setWait_Close(uint16_t val)
{
    modbus_t *ur5 = modbus_new_tcp("192.168.100.11", 502);
    modbus_connect(ur5);
    int reg = modbus_write_register(ur5, 135, val);
    if (reg == -1)
    {
        std::cout << ("Modbus: Counldn't set Wait_Close!") << std::endl;
    }
}

void MyPanel::setWait_Open(uint16_t val)
{
    modbus_t *ur5 = modbus_new_tcp("192.168.100.11", 502);
    modbus_connect(ur5);
    int reg = modbus_write_register(ur5, 136, val);
    if (reg == -1)
    {
        std::cout << ("Modbus: Counldn't set Wait_Open!") << std::endl;
    }
}

void MyPanel::setX_drop(uint16_t val)
{

    modbus_t *ur5 = modbus_new_tcp("192.168.100.11", 502);
    modbus_connect(ur5);
    int reg = modbus_write_register(ur5, 140, val);
    if (reg == -1)
    {
        std::cout << ("Modbus: Counldn't set X!") << std::endl;
    }
}

void MyPanel::setY_drop(uint16_t val)
{
    modbus_t *ur5 = modbus_new_tcp("192.168.100.11", 502);
    modbus_connect(ur5);
    int reg = modbus_write_register(ur5, 141, val);
    if (reg == -1)
    {
        std::cout << ("Modbus: Counldn't set Y!") << std::endl;
    }
}

void MyPanel::setZ_drop(uint16_t val)
{

    modbus_t *ur5 = modbus_new_tcp("192.168.100.11", 502);
    modbus_connect(ur5);
    int reg = modbus_write_register(ur5, 142, val);
    if (reg == -1)
    {
        std::cout << ("Modbus: Counldn't set Z!") << std::endl;
    }
}

void MyPanel::OnClick(wxCommandEvent &e)
{
    if (e.GetId() == Stop_button_id) // Stop button:
    {
        _stopFlag = true; // Sets the stopFlag to true
    }

    if (e.GetId() == OpenGripper_id) // When Open gripper button pressed then:
    {
        Atmega atmegaopen; // Inizialize 
        atmegaopen.write_open_Grip(); // Open gripper
    }

    if (e.GetId() == PickUp_button_id) // If pickup button is pressed do following:
    {
        _failCount = 0; // Reset failCount
        _stopFlag = false; // Reset stopFlag 

        setWait_Close(0); // Reset Wait_Close register
        setWait_Open(0); // Reset Wait_Open register
        
        std::thread *_pickAndPlaceThread = nullptr; // Open a new thread so that another button can be pressed
        if (_pickAndPlaceThread == nullptr || !_pickAndPlaceThread->joinable()) // If statement that checks if thread is a 
        // null pointer and not joinable, needed for the thread to work. 
        {
            _pickAndPlaceThread = new std::thread([&]()
                                                  {     // Inizializing the thread
                while (true)
                {
                    setPickupLocation(); // Setting Pickup location, it is always the same
                    atmega.write_close_Grip(); // Closing the gripper
                    atmega.read_Value(); // Waiting for the gripper to get a grip, Atmega board sends 69 number

                    while (true)
                    {

                        if (atmega.getValue() == 69) // When number is send, do following:
                        {
                            setDropoffLocation(); // Setting the DropoffLocation based of the timer
                            setWait_Close(1); // UR5 robot waited in the Pickup location for this register to be 1, If ur5 recieved this then robot moves to dropoff location
                            Atmega atmegastop; // Inizializing atmegastop connection
                            atmegastop.write_open_Grip(); // Opening the gripper at dropoff location
                            atmegastop.stop_Value(); // When gripper fully opened, Atmega board sends value 42
                            if (atmegastop.getValue() == 42) // When this value is 42 then :
                            {
                                setWait_Open(1); // Robot can go do the task again 
                                setCO(0); // Robot can go do the task again 
                                break;
                            }
                        }

                    }

                    if (_failCount == 1) // If fail count is 1 then stop the robot
                    {
                            setCO(0); // Go back to start position
                            break;
                    }


                    setWait_Close(0); // Reset Wait_Close register because it is in a while loop
                    setWait_Open(0); // Reset Wait_Open register because it is in a while loop

                    if (_stopFlag) // If stop button pressed the robot goes back to the start position, that means if _stopFlag == true
                    {
                        setCO(0); // Go back to start position
                        break;
                    }


                } });
        }
    }
}

wxBEGIN_EVENT_TABLE(MyPanel, wxPanel)
    EVT_BUTTON(wxID_ANY, MyPanel::OnClick)
        wxEND_EVENT_TABLE();