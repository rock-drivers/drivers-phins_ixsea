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

#include "NmeaRecord.hpp"
#include "PhinsTypes.hpp"
#include "phins_ixsea/Error.hpp"

#include <base/samples/rigid_body_state.h>

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

       // static Parser* createParser(Protocol protocol);
        static Parser* createParser(int protocol);

        /** extract a package from the incoming data stream
         *  this method is called be the drivers extractPackage method
         */
        virtual int extractPacket (uint8_t const *buffer, size_t buffer_size) const = 0;
        virtual void parseEnsemble(std::string buffer, size_t size) = 0;

        virtual void getRBS( base::samples::RigidBodyState *rbs) = 0;
        virtual void getUtmwgs( Utmwgs *utmwgs) = 0;



    };


    class NmeaParser : public phins_ixsea::Parser
    {
    public:
        NmeaParser();
        /** extracts a NMEA 183 sentence from the datastream
         * each sentence starts with a '$' and ends with "\r\n"
         * The sentence may contain a checksum
         */

        virtual void parseEnsemble(std::string buffer, size_t size) = 0;
        virtual void getRBS( base::samples::RigidBodyState *rbs) = 0;
        virtual void getUtmwgs(Utmwgs *utmwgs) = 0;

    protected:
        phins_ixsea::NmeaRecord mNmeaRecord;

    };

} /* namespace phins_ixsea */
#endif /*  _PHINS_IXSEA_PARSER_HPP_ */
