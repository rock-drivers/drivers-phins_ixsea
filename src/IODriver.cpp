/*
 * IODriver.cpp
 *
 *  Created on: 15.02.2013
 *      Author: jrenken
 */

#include <phins_ixsea/IODriver.hpp>

namespace phins_ixsea
{

    IODriver::IODriver(int max_packet_size, bool extract_last)
        : iodrivers_base::Driver(max_packet_size, extract_last)
    {
    }

    int IODriver::extractPacket (uint8_t const *buffer, size_t buffer_size) const
    {
        return buffer_size;
    }

} /* namespace phins_ixsea */
