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
      mUpdateFlags(0),
      mPhinsStatus(),
      mPhinsExtStatus()
{
    mParser = Parser::createParser(protocol);
    mBuffer.resize(10000);
    mUtmPose.invalidate();
    mUtmPose.sourceFrame = "frame";
    mUtmPose.targetFrame = "world";
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
    base::Time time = base::Time::now();
    if (mParser->hasUpdate(UPD_UTMPOS, true)) {
        mUtmPose.time = time;
        mUtmPose.position.x() = mParser->mData.utm_pos_east;
        mUtmPose.position.y() = mParser->mData.utm_pos_north;
        mUtmPose.position.z() = mParser->mData.utm_altitude;
        mUpdateFlags |= UPD_UTMPOS;
    }
    if (mParser->hasUpdate(UPD_POSITION, true)) {
        mGeoPose.time = time;
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
        mUtmPose.time = time;
        mGeoPose.time = time;
        mUtmPose.orientation = Eigen::AngleAxisd(mParser->mData.att_heading, -Eigen::Vector3d::UnitZ())
                        * Eigen::AngleAxisd(mParser->mData.att_pitch, Eigen::Vector3d::UnitY())
                        * Eigen::AngleAxisd(mParser->mData.att_roll, Eigen::Vector3d::UnitX());
        mGeoPose.orientation = mUtmPose.orientation;
        mUpdateFlags |= UPD_HPR;
    }
    if (mParser->hasUpdate(UPD_BODY_ROTATION_RATE, true)) {
        mUtmPose.time = time;
        mGeoPose.time = time;
        mUtmPose.angular_velocity[0] = mParser->mData.rotation_rate_vessel_xv3; // yaw
        mUtmPose.angular_velocity[1] = mParser->mData.rotation_rate_vessel_xv2; // pitch
        mUtmPose.angular_velocity[2] = mParser->mData.rotation_rate_vessel_xv1; // roll
        mGeoPose.angular_velocity = mUtmPose.angular_velocity;
        mUpdateFlags |= UPD_BODY_ROTATION_RATE;
    }
    if (mParser->hasUpdate(UPD_USER_STATUS, true)) {
        uint32_t ust = mParser->mData.user_status;
        mPhinsStatus.time = time;
        mPhinsStatus.sensor_status = ust & 0x000001ff;
        mPhinsStatus.input_status = (ust >> 16) & 0x0000001f;
        mPhinsStatus.output_status = (ust >> 21) & 0x0000001f;
        mPhinsStatus.system_status = ((ust >> 9) & 0x0000007f) | ((ust >> 18) & 0x00000080);
        mPhinsStatus.mode = (ust >> 27) & 0x0000001f;
        mUpdateFlags |= UPD_USER_STATUS;

    }
    if (mParser->hasUpdate(UPD_EXT_STATUS, true)) {
        mPhinsExtStatus.time = time;
        mPhinsExtStatus.status_lsb = mParser->mData.status_LSB;
        mPhinsExtStatus.status_msb = mParser->mData.status_MSB;
        mPhinsExtStatus.algo_status_lsb = mParser->mData.algo_status_LSB;
        mPhinsExtStatus.algo_status_msb = mParser->mData.algo_status_MSB;
        mPhinsExtStatus.user_status = mParser->mData.user_status;
        mUpdateFlags |= UPD_EXT_STATUS;
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

PhinsStatus Driver::phinsStatus() const
{
    return mPhinsStatus;
}

PhinsExtStatus Driver::phinsExtStatus() const
{
    return mPhinsExtStatus;
}

NavigationMode Driver::navigationMode() const
{
    NavigationMode mode = UNKNOWN_MODE;

    uint32_t st = mPhinsExtStatus.algo_status_lsb;

    if (st & NAVIG)
        mode = NAVIGATION_MODE;
    if (st & FINE_ALIGNE)
        mode = FINE_ALIGN_MODE;
    if (st & ALIGNE)
        mode = COARSE_ALIGN_MODE;
    if (st & (ALT_SATURATION | SPD_SATURATION)) {
        mode = FAILURE_MODE;
    }
    return mode;
}
