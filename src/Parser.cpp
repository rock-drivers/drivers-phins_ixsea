/*
 * Parser.cpp
 *
 *  Created on: 12.06.2012
 *      Author: jrenken
 */

#include "Parser.hpp"
#include "PhinsStandardParser.hpp"
#include "HalliburtonSASParser.hpp"

namespace phins_ixsea
{

Parser::Parser()
{
}

phins_ixsea::Parser* Parser::createParser(Protocol protocol)
{
    switch (protocol) {
    case PhinsStandard:
        return new PhinsStandardParser();
    case HalliburtonSAS:
        return new HalliburtonSASParser();
    default:
        return 0;
    }
    return 0;
}

NmeaParser::NmeaParser()
    : Parser()
{
}

int NmeaParser::extractPacket (uint8_t const *buffer, size_t buffer_size) const
{
    return -buffer_size;
}


} /* namespace phins_ixsea */
