/*
 * HalliburtonSASParser.hpp
 *
 *  Created on: 12.06.2012
 *      Author: jrenken
 */

#ifndef _PHINS_IXSEA_HALLIBURTONSASPARSER_HPP_
#define _PHINS_IXSEA_HALLIBURTONSASPARSER_HPP_

#include <phins_ixsea/Parser.hpp>
#include <phins_ixsea/NmeaRecord.hpp>

namespace phins_ixsea
{

    /*
     *
     */
    class HalliburtonSASParser: public phins_ixsea::NmeaParser
    {

        void parsePosition(const NmeaRecord& nmea);
        void parseAttitude(const NmeaRecord& nmea);
        void parseStatus(const NmeaRecord& nmea);


    public:
        HalliburtonSASParser();

        virtual void parse(uint8_t const *buffer, size_t size);

    };

} /* namespace phins_ixsea */
#endif /* _PHINS_IXSEA_HALLIBURTONSASPARSER_HPP_ */
