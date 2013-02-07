/*
 * PhinsStandardParser.cpp
 *
 *  Created on: 12.06.2012
 *      Author: jrenken
 */

#include "PhinsStandardParser.hpp"
#include "NmeaRecord.hpp"
#include <iostream>

using namespace phins_ixsea;


PhinsStandardParser::PhinsStandardParser()
{

}

void PhinsStandardParser::parse(uint8_t const *buffer, size_t size)
{
    NmeaRecord nmea((const char*)buffer, size);

    if (nmea.isValid()) {
        std::cout << "New Record: " << nmea.header() << " " << nmea[1] << std::endl;
    } else {
        std::cout << "not valid: " << nmea.sentence() << std::endl;
    }

}


