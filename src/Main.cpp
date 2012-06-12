/*
 * main.cpp
 *
 *  Created on: 12.06.2012
 *      Author: jrenken
 */

#include <iostream>
#include <phins_ixsea/Driver.hpp>

int main(int argc, char** argv)
{
	phins_ixsea::Driver driver;

	driver.openURI("serial:///dev/ttyS0:9600");
	uint8_t buffer[10000];

	while (1) {
	    int n = driver.readPacket(buffer, 8192, 2000, 2000);
	    if (n > 0) {
	        buffer[n] = 0;
	        std::cout << buffer;
	    }
	}

	return 0;
}
