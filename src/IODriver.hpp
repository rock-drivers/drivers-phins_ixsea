/*
 * IODriver.h
 *
 *  Created on: 15.02.2013
 *      Author: jrenken
 */

#ifndef _PHINS_IXSEA__IODRIVER_H_
#define _PHINS_IXSEA_IODRIVER_H_

#include <iodrivers_base/Driver.hpp>


namespace phins_ixsea
{

    /* basic IO driver for sending and reading uninterpreted external sensor rawdata
     *
     */
    class IODriver : public iodrivers_base::Driver
    {
    public:
        IODriver(int max_packet_size = 2048, bool extract_last = false);
    private:
        int extractPacket (uint8_t const *buffer, size_t buffer_size) const;
    };

} /* namespace phins_ixsea */
#endif /* _PHINS_IXSEA_IODRIVER_H_ */
