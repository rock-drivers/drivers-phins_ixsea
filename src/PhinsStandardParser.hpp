/*
 * PhinsStandardParser.hpp
 *
 *  Created on: 12.06.2012
 *      Author: jrenken
 */

#ifndef _PHINS_IXSEA_PHINSSTANDARDPARSER_HPP_
#define _PHINS_IXSEA_PHINSSTANDARDPARSER_HPP_

#include <phins_ixsea/Parser.hpp>
#include <phins_ixsea/NmeaRecord.hpp>

namespace phins_ixsea
{

    /*
     *
     */
    class PhinsStandardParser: public phins_ixsea::NmeaParser
    {

        void parseAttitude(const NmeaRecord& nmea);
        void parsePosition(const NmeaRecord& nmea);
        void parseSpeed(const NmeaRecord& nmea);
        void parseUtmWgs(const NmeaRecord& nmea);
        void parseHeave(const NmeaRecord& nmea);
        void parseStddevHrp(const NmeaRecord& nmea);
        void parseTime(const NmeaRecord& nmea);
        void parseStddevPos(const NmeaRecord& nmea);
        void parseHeading(const NmeaRecord& nmea);
        void parseStddevSpeed(const NmeaRecord& nmea);
        void parseAlgoStatus(const NmeaRecord& nmea);
        void parseStatus(const NmeaRecord& nmea);


    public:
        PhinsStandardParser();

        virtual void parse(uint8_t const *buffer, size_t size);
    };

} /* namespace phins_ixsea */
#endif /* _PHINS_IXSEA_PHINSSTANDARDPARSER_HPP_ */
