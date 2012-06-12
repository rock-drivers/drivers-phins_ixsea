/*
 * Driver.cpp
 *
 *  Created on: 12.06.2012
 *      Author: jrenken
 */

#include "Driver.hpp"

using namespace phins_ixsea;



Driver::Driver()
    : iodrivers_base::Driver(8192),
      mParser(0)
{

}

int Driver::extractPacket (uint8_t const *buffer, size_t buffer_size) const
{
    if (mParser)
        return mParser->extractPacket(buffer, buffer_size);
    return -buffer_size;
}




