/*
 * PhinsStandardParser.cpp
 *
 *  Created on: 12.06.2012
 *      Author: jrenken
 */

#include "PhinsStandardParser.hpp"
#include "NmeaRecord.hpp"
#include <iostream>

using namespace phins_ixsea;
using namespace std;

/**
 * $HEHDT,116.581,T*25
 * $PIXSE,ATITUD,-1.641,-0.490*6D
 * $PIXSE,POSITI,53.10245714,8.83994382,-0.115*71
 * $PIXSE,SPEED_,-0.802,-1.243,0.000*6F
 * $PIXSE,UTMWGS,U,32,489284.019,5883680.109,-0.115*39
 * $PIXSE,HEAVE_,-0.000,-0.000,0.014*7C
 * $PIXSE,TIME__,003356.016693*64
 * $PIXSE,STDHRP,1.997,0.082,0.101*7C
 * $PIXSE,STDPOS,20563.20,18004.65,50.00*7D
 * $PIXSE,STDSPD,19.747,13.032,10.002*41
 * $PIXSE,ALGSTS,00000045,00004000*60
 * $PIXSE,STATUS,00000000,00000000*6F
 * $PIXSE,HT_STS,FFFD5551*46
 *
 *
 */

#define MY_DEBUG(a, b, c, d, e) //cout << a << b << " " << c << " " << d << " " << e << endl

PhinsStandardParser::PhinsStandardParser()
{

}

void PhinsStandardParser::parse(uint8_t const *buffer, size_t size)
{
    NmeaRecord nmea((const char*)buffer, size);

    if (nmea.isValid()) {
//        cout << "New Record: " << nmea.header() << " " << nmea[1] << endl;
        string header = nmea.header();
        string subHeader;
        if (header == "$PIXSE") {
            subHeader = nmea[1];
            if (subHeader == "ATITUD") {
                parseAttitude(nmea);
            } else if (subHeader == "POSITI") {
                parsePosition(nmea);
            } else if (subHeader == "SPEED_") {
                parseSpeed(nmea);
            } else if (subHeader == "UTMWGS") {
                parseUtmWgs(nmea);
            } else if (subHeader == "HEAVE_") {
                parseHeave(nmea);
            } else if (subHeader == "STDHRP") {
                parseStddevHrp(nmea);
            } else if (subHeader == "TIME__") {
                parseTime(nmea);
            } else if (subHeader == "STDPOS") {
                parseStddevPos(nmea);
            } else if (subHeader == "STDSPD") {
                parseStddevSpeed(nmea);
            } else if (subHeader == "ALGSTS") {
                parseAlgoStatus(nmea);
            } else if (subHeader == "STATUS") {
                parseStatus(nmea);
            } else if (subHeader == "HT_STS") {
                parseUserStatus(nmea);
            }
        } else if (header == "$HEHDT") {
            parseHeading(nmea);
        }
    } else {
        std::cout << "not valid: " << nmea.sentence() << std::endl;
    }
}

void PhinsStandardParser::parseAttitude(const NmeaRecord& nmea)
{
    mData.att_roll = strtod(nmea[2].c_str(), 0);
    mData.att_pitch = strtod(nmea[3].c_str(), 0);
    mUpdateFlags |= UPD_ATTITUDE;
//    MY_DEBUG("Attitude: ", mData.att_roll, mData.att_pitch, "", "");
}


void PhinsStandardParser::parsePosition(const NmeaRecord& nmea)
{
    mData.pos_latitude = strtod(nmea[2].c_str(), 0);
    mData.pos_longitude = strtod(nmea[3].c_str(), 0);
    mData.pos_altitude = strtod(nmea[4].c_str(), 0);
    mUpdateFlags |= UPD_POSITION;
//    MY_DEBUG("Position: ", mData.pos_latitude, mData.pos_longitude, mData.pos_altitude, "");
}

void PhinsStandardParser::parseSpeed(const NmeaRecord& nmea)
{
    mData.spd_east = strtod(nmea[2].c_str(), 0);
    mData.spd_north = strtod(nmea[3].c_str(), 0);
    mData.spd_up = strtod(nmea[4].c_str(), 0);
    mUpdateFlags |= UPD_SPEED;
//    MY_DEBUG("Speed: ", mData.spd_east, mData.spd_north, mData.spd_up, "");
}

void PhinsStandardParser::parseUtmWgs(const NmeaRecord& nmea)
{
    mData.utm_lat_zone = nmea[2].at(0);
    mData.utm_lon_zone = strtol(nmea[3].c_str(), 0, 10);
    mData.utm_pos_east = strtod(nmea[4].c_str(), 0);
    mData.utm_pos_north = strtod(nmea[5].c_str(), 0);
    mData.utm_altitude = strtod(nmea[6].c_str(), 0);
    mUpdateFlags |= UPD_UTMPOS;
//    MY_DEBUG("UtmWgs: ", mData.utm_lat_zone, mData.utm_lon_zone, mData.utm_pos_east, mData.utm_pos_north);
}

void PhinsStandardParser::parseHeave(const NmeaRecord& nmea)
{
    mData.heave_surge = strtod(nmea[2].c_str(), 0);
    mData.heave_sway = strtod(nmea[3].c_str(), 0);
    mData.heave_heave = strtod(nmea[4].c_str(), 0);
    mUpdateFlags |= UPD_HEAVE;
//    MY_DEBUG("Heave: ", mData.heave_surge, mData.heave_sway, mData.heave_heave, "");
}

void PhinsStandardParser::parseStddevHrp(const NmeaRecord& nmea)
{
    mData.stddev_att_heading = strtod(nmea[2].c_str(), 0);
    mData.stddev_att_roll = strtod(nmea[3].c_str(), 0);
    mData.stddev_att_pitch = strtod(nmea[4].c_str(), 0);
    mUpdateFlags |= UPD_DEV_ATT;
//    MY_DEBUG("Stddev Attitude: ", mData.stddev_att_heading, mData.stddev_att_roll, mData.stddev_att_pitch, "");

}

void PhinsStandardParser::parseTime(const NmeaRecord& nmea)
{

}

void PhinsStandardParser::parseStddevPos(const NmeaRecord& nmea)
{
    mData.stddev_pos_latitude = strtod(nmea[2].c_str(), 0);
    mData.stddev_pos_longitude = strtod(nmea[3].c_str(), 0);
    mData.stddev_pos_altitude = strtod(nmea[4].c_str(), 0);
    mUpdateFlags |= UPD_DEV_POS;
//    MY_DEBUG("Stddev Position: ", mData.stddev_pos_latitude, mData.stddev_pos_longitude, mData.stddev_pos_altitude, "");

}

void PhinsStandardParser::parseHeading(const NmeaRecord& nmea)
{
    mData.att_heading = strtod(nmea[1].c_str(), 0);
    mUpdateFlags |= UPD_HEADING;
//    MY_DEBUG("Heading: ", mData.att_heading, "", "", "" );
}

void PhinsStandardParser::parseStddevSpeed(const NmeaRecord& nmea)
{
    mData.stddev_spd_north = strtod(nmea[2].c_str(), 0);
    mData.stddev_spd_east = strtod(nmea[3].c_str(), 0);
    mData.stddev_spd_up = strtod(nmea[4].c_str(), 0);
    mUpdateFlags |= UPD_DEV_SPD;
//    MY_DEBUG("Stddev Speed: ", mData.stddev_spd_east, mData.stddev_spd_north, mData.stddev_spd_up, "");
}

void PhinsStandardParser::parseAlgoStatus(const NmeaRecord& nmea)
{
    mData.algo_status_LSB = strtoul(nmea[2].c_str(), 0, 16);
    mData.algo_status_MSB = strtoul(nmea[3].c_str(), 0, 16);
    mUpdateFlags |= UPD_ALGO_STATUS;
    MY_DEBUG("Algo Status: ", mData.algo_status_LSB, mData.algo_status_MSB, reverseBytes(nmea[2]), nmea[2]);

}

void PhinsStandardParser::parseStatus(const NmeaRecord& nmea)
{
    mData.status_LSB = strtoul(nmea[2].c_str(), 0, 16);
    mData.status_MSB = strtoul(nmea[3].c_str(), 0, 16);
    mUpdateFlags |= UPD_IO_STATUS;
    MY_DEBUG("Status: ", mData.status_LSB, mData.status_MSB, reverseBytes(nmea[3]), "");
}


void PhinsStandardParser::parseUserStatus(const NmeaRecord& nmea)
{
    mData.user_status = strtoul(nmea[2].c_str(), 0, 16);
    mUpdateFlags |= UPD_USER_STATUS;
//    MY_DEBUG("Status: ", mData.user_status, "", "", "");
}


