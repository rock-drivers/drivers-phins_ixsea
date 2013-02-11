/*
 * Driver.cpp
 *
 *  Created on: 12.06.2012
 *      Author: jrenken
 */

#include "Driver.hpp"

using namespace phins_ixsea;



Driver::Driver(Protocol protocol)
    : iodrivers_base::Driver(10000),
      mParser(0),
      mUpdateFlags(0)
{
    mParser = Parser::createParser(protocol);
    mBuffer.resize(10000);
    mUtmPose.invalidate();
    mGeoPose.invalidate();
}

Driver::~Driver()
{
    delete mParser;
}

void Driver::setParser(Protocol protocol)
{
    delete mParser;
    mParser = Parser::createParser(protocol);
}

int Driver::extractPacket (uint8_t const *buffer, size_t buffer_size) const
{
    if (mParser)
        return mParser->extractPacket(buffer, buffer_size);
    return -buffer_size;
}


void Driver::read()
{
    int packet_size = readPacket(&mBuffer[0], mBuffer.size());
    if (packet_size) {
        mParser->parse(&mBuffer[0], packet_size);
        updateSamples();
    }
}


void Driver::updateSamples()
{
    if (mParser->hasAnyUpdate(UPD_UTMPOS | UPD_POSITION | UPD_SPEED | UPD_ATTITUDE)) {
        mUtmPose.time = base::Time::now();
        mGeoPose.time = mUtmPose.time;
    }

    if (mParser->hasUpdate(UPD_UTMPOS, true)) {
        mUtmPose.position.x() = mParser->mData.utm_pos_east;
        mUtmPose.position.y() = mParser->mData.utm_pos_north;
        mUtmPose.position.z() = mParser->mData.utm_altitude;
        mUpdateFlags |= UPD_UTMPOS;
    }
    if (mParser->hasUpdate(UPD_POSITION, true)) {
        mGeoPose.position.x() = mParser->mData.pos_longitude;
        mGeoPose.position.y() = mParser->mData.pos_latitude;
        mGeoPose.position.z() = mParser->mData.pos_altitude;
        mUpdateFlags |= UPD_POSITION;
    }
    if (mParser->hasUpdate(UPD_SPEED, true)) {
        mUtmPose.velocity.x() = mParser->mData.spd_east;
        mUtmPose.velocity.y() = mParser->mData.spd_north;
        mUtmPose.velocity.z() = mParser->mData.spd_up;
        mGeoPose.velocity = mUtmPose.velocity;
        mUpdateFlags |= UPD_SPEED;
    }
    if (mParser->hasUpdate(UPD_ATTITUDE, true)) {
        mUtmPose.orientation = Eigen::AngleAxisd(mParser->mData.att_heading * M_PI / 180.0, Eigen::Vector3d::UnitZ())
                        * Eigen::AngleAxisd(mParser->mData.att_pitch * M_PI / 180.0, Eigen::Vector3d::UnitY())
                        * Eigen::AngleAxisd(mParser->mData.att_roll * M_PI / 180.0, Eigen::Vector3d::UnitX());
        mGeoPose.orientation = mUtmPose.orientation;
        mUpdateFlags |= UPD_HPR;
    }
}

bool Driver::hasUpdate(uint32_t flags, bool reset)
{
    if ((mUpdateFlags & flags) == flags) {
        if (reset) {
            mUpdateFlags &= ~flags;
        }
        return true;
    }
    return false;
}


const base::samples::RigidBodyState& Driver::utmPose() const
{
    return mUtmPose;
}
const base::samples::RigidBodyState& Driver::geoPose() const
{
    return mGeoPose;
}

base::samples::RigidBodyState Driver::relativePose(const base::Position origin) const
{
    base::samples::RigidBodyState rbs = mUtmPose;
    rbs.position(0) -= origin(0);
    rbs.position(1) -= origin(1);
    return rbs;
}

