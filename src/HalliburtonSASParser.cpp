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
using namespace std;


HalliburtonSASParser::HalliburtonSASParser()
{
    // TODO Auto-generated constructor stub

}

void HalliburtonSASParser::parse(uint8_t const *buffer, size_t size)
{
    NmeaRecord nmea((const char*)buffer, size);

    if (nmea.isValid()) {
//       std::cout << "New Record: " << nmea.header() << " " << nmea[1] << std::endl;
        string header = nmea.header();
        string subHeader;
        if (header == "$PIXSE") {
            subHeader = nmea[1];
            if (subHeader == "HSPOS") {
                parsePosition(nmea);
            } else if (subHeader == "HSATIT") {
                parseAttitude(nmea);
            } else if (subHeader == "HSSTAT") {
                parseStatus(nmea);
            }
        }
    } else {
        std::cout << "not valid: " << nmea.sentence() << std::endl;
        throw std::runtime_error("Invalid MEA sentence received");
    }
}


void HalliburtonSASParser::parsePosition(const NmeaRecord& nmea)
{

}

void HalliburtonSASParser::parseAttitude(const NmeaRecord& nmea)
{

}

void HalliburtonSASParser::parseStatus(const NmeaRecord& nmea)
{

}


