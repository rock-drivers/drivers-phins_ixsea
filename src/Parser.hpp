/*
 * Parser.hpp
 *
 *  Created on: 12.06.2012
 *      Author: jrenken
 */

#ifndef  _PHINS_IXSEA_PARSER_HPP_
#define  _PHINS_IXSEA_PARSER_HPP_

#include <stdint.h>
#include <stdlib.h>
#include <string>
#include <phins_ixsea/PhinsTypes.hpp>
#include <phins_ixsea/PhinsRaw.hpp>

namespace phins_ixsea
{

    /** Base class for parsing the Phins output and extracting the data
     *  It contains an implementation of extractPackage.
     *  The base class is pure virtual and can not be instantiated
     */
    class Parser
    {


    public:
        Parser();

        static Parser* createParser(Protocol protocol);

        /** extract a package from the incoming data stream
         *  this method is called be the drivers extractPackage method
         */
        virtual int extractPacket (uint8_t const *buffer, size_t buffer_size) const = 0;

        /**
         * parse a data packet
         * pure virtual, has to be implemented in the specific protocol parser
         */
        virtual void parse(uint8_t const *buffer, size_t size) = 0;

        /**
         * checks if actual data is available
         * if true and reset is true, the flasg are reset
         * \return true if all flags are set
         * \return if true, reset the set flags
         */
        bool hasUpdate(uint32_t flags, bool reset = false);

        bool hasAnyUpdate(uint32_t flags);

        PhinsRawData    mData;
        uint32_t        mUpdateFlags;
    };


    class NmeaParser : public Parser
    {

    public:
        NmeaParser();
        /** extracts a NMEA 183 sentence from the datastream
         * each sentence starts with a '$' and end with "\r\n"
         * The sentence may contain a checksum
         */
        virtual int extractPacket (uint8_t const *buffer, size_t buffer_size) const;

    protected:
        /** convert degree, decimal minutes to decimal degrees
         *
         */
        double ddm2dd(const double);

    };

} /* namespace phins_ixsea */
#endif /*  _PHINS_IXSEA_PARSER_HPP_ */
