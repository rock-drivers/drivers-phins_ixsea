/*
 * HalliburtonSASParser.cpp
 *
 *  Created on: 12.06.2012
 *      Author: jrenken
 */

#include "HalliburtonSASParser.hpp"
#include "NmeaRecord.hpp"
#include <iostream>

using namespace phins_ixsea;


HalliburtonSASParser::HalliburtonSASParser()
{
    // TODO Auto-generated constructor stub

}

void HalliburtonSASParser::parse(uint8_t const *buffer, size_t size)
{
    NmeaRecord nmea((const char*)buffer, size);

    if (nmea.isValid()) {
        std::cout << "New Record: " << nmea.header() << " " << nmea[1] << std::endl;
    } else {
        std::cout << "not valid: " << nmea.sentence() << std::endl;
    }
}



