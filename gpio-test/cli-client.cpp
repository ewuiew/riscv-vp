/*
 * cli-client.cpp
 *
 *  Created on: 7 Nov 2018
 *      Author: dwd
 */


#include "gpio-client.hpp"
#include <iostream>
#include <unistd.h>

using namespace std;

int main(int argc, char* argv[])
{
	if(argc < 3)
	{
		cout << "usage: " << argv[0] << " host port (e.g. localhost 1339)" << endl;
		exit(-1);
	}

	GpioClient gpio;

	if(!gpio.setupConnection(argv[1], argv[2]))
	{
		cout << "cant setup connection" << endl;
		return -1;
	}

    for(uint8_t i = 0; i < 64; i++)
    {
    	if(!gpio.setBit(i, 1))
		{
    		cerr << "Error setting Bit " << i << endl;
    		return -1;
		}
    	if(!gpio.update())
    	{
    		cerr << "Error updating" << endl;
    		return -1;
    	}
    	bitPrint(reinterpret_cast<char*>(&gpio.state.val), sizeof(Gpio::Reg));
    	usleep(750);
    }


    for(uint8_t i = 0; i < 64; i++)
    {
    	if(!gpio.setBit(i, 0))
		{
    		cerr << "Error resetting Bit " << i << endl;
    		return -1;
		}
    	if(!gpio.update())
    	{
    		cerr << "Error updating" << endl;
    		return -1;
    	}
    	bitPrint(reinterpret_cast<char*>(&gpio.state.val), sizeof(Gpio::Reg));
    	usleep(750);
    }
}
