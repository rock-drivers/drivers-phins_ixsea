/*
 * Parser.cpp
 *
 *  Created on: 12.06.2012
 *      Author: jrenken
 */

#include "Parser.hpp"
#include "PhinsStandardParser.hpp"
#include "HalliburtonSASParser.hpp"
#include <math.h>

namespace phins_ixsea
{

Parser::Parser()
    : mData(),
      mUpdateFlags(0)
{
}

Parser* Parser::createParser(Protocol protocol)
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

bool Parser::hasUpdate(uint32_t flags, bool reset)
{
    if ((mUpdateFlags & flags) == flags) {
        if (reset) {
            mUpdateFlags &= ~flags;
        }
        return true;
    }
    return false;
}

bool Parser::hasAnyUpdate(uint32_t flags)
{
    return mUpdateFlags & flags;
}


NmeaParser::NmeaParser()
    : Parser()
{
}

int NmeaParser::extractPacket (uint8_t const *buffer, size_t buffer_size) const
{
    if (buffer[0] == '$') {
        for (size_t i = 0; i < buffer_size; i++) {
            if (buffer[i] == '\n') {
                return i + 1;
            }
        }
        return 0;
    } else {
        for (size_t i = 0; i < buffer_size; i++) {
            if (buffer[i] == '$') {
                return -i;
            }
        }
    }
    return -buffer_size;
}

double NmeaParser::ddm2dd(const double ddm)
{
    int deg = floor(fabs(ddm) / 100);
    double res = (fabs(ddm) - deg * 100) / 60 + deg;
    if (ddm < 0) return -res;
    return res;
}


} /* namespace phins_ixsea */
