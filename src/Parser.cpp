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


bool Parser::getData(base::samples::RigidBodyState& rbs)
{
    bool res = false;
    rbs.invalidate();
    if (hasUpdate(UPD_UTMPOS, true)) {
        rbs.position.x() = mData.utm_pos_east;
        rbs.position.y() = mData.utm_pos_north;
        rbs.position.z() = mData.utm_altitude;
        res = true;
    }
    if (hasUpdate(UPD_SPEED, true)) {
        rbs.velocity.x() = mData.spd_east;
        rbs.velocity.y() = mData.spd_north;
        rbs.velocity.z() = mData.spd_up;
        res = true;
    }
    if (hasUpdate(UPD_ATTITUDE, true)) {
//        This seems to be rubbisch
        rbs.orientation = Eigen::AngleAxisd(mData.att_heading, Eigen::Vector3d::UnitZ())
        * Eigen::AngleAxisd(mData.att_pitch, Eigen::Vector3d::UnitY())
        * Eigen::AngleAxisd(mData.att_roll, Eigen::Vector3d::UnitX());
        res = true;
    }
    return res;
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


} /* namespace phins_ixsea */
