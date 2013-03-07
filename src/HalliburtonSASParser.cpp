/*
 * HalliburtonSASParser.cpp
 *
 *  Created on: 12.06.2012
 *      Author: jrenken
 */

#include "HalliburtonSASParser.hpp"
#include "NmeaRecord.hpp"
#include <iostream>

using namespace phins_ixsea;
using namespace std;


HalliburtonSASParser::HalliburtonSASParser()
{
    // TODO Auto-generated constructor stub

}

void HalliburtonSASParser::parse(uint8_t const *buffer, size_t size)
{
    NmeaRecord nmea((const char*)buffer, size);

    if (nmea.isValid()) {
//        std::cout << "New Record: " << nmea.header() << " " << nmea[1] << std::endl;
        string header = nmea.header();
        string subHeader;
        if (header == "$PIXSE") {
            subHeader = nmea[1];
            if (subHeader == "HSPOS_") {
                parsePosition(nmea);
            } else if (subHeader == "HSATIT") {
                parseAttitude(nmea);
            } else if (subHeader == "HSSTAT") {
                parseStatus(nmea);
            }
        }
    } else {
        std::cout << "not valid: " << nmea.sentence() << std::endl;
        throw std::runtime_error("Invalid NMEA sentence received");
    }
}


void HalliburtonSASParser::parsePosition(const NmeaRecord& nmea)
{
    mData.pos_latitude = ddm2dd(strtod(nmea[3].c_str(), 0));
    if (nmea[4] == "S") mData.pos_latitude *= -1;
    mData.pos_longitude = ddm2dd(strtod(nmea[5].c_str(), 0));
    if (nmea[6] == "W") mData.pos_longitude *= -1;
    mData.pos_altitude = - strtod(nmea[7].c_str(), 0);
    mData.dvl_altitude = strtod(nmea[8].c_str(), 0);
    mData.stddev_pos_latitude = strtod(nmea[9].c_str(), 0);
    mData.stddev_pos_longitude = strtod(nmea[10].c_str(), 0);
    mData.stddev_pos_altitude = strtod(nmea[12].c_str(), 0);

    mData.utm_lon_zone = strtol(nmea[13].c_str(), 0, 10);
    mData.utm_lat_zone = nmea[14].at(0);
    mData.utm_pos_east = strtod(nmea[15].c_str(), 0);
    mData.utm_pos_north = strtod(nmea[16].c_str(), 0);

    mData.dvl_misaligne_estimation = strtod(nmea[17].c_str(), 0);
    mData.dvl_scale_fcator_corr_estimation = strtod(nmea[18].c_str(), 0);

    mData.sound_speed = strtod(nmea[19].c_str(), 0);

    mUpdateFlags |= (UPD_UTMPOS | UPD_POSITION | UPD_DEV_POS | UPD_DVL );

}

void HalliburtonSASParser::parseAttitude(const NmeaRecord& nmea)
{
    mData.att_heading = strtod(nmea[2].c_str(), 0) * M_PI / 180.0;
    mData.att_roll = strtod(nmea[3].c_str(), 0) * M_PI / 180.0; //TODO: chek orientation
    mData.att_pitch = strtod(nmea[4].c_str(), 0) * M_PI / 180.0;

    mData.heave_heave = strtod(nmea[5].c_str(), 0);
    mData.rotation_rate_vessel_xv3 = strtod(nmea[6].c_str(), 0) * M_PI / 180.0;
    mData.rotation_rate_vessel_xv1 = strtod(nmea[7].c_str(), 0) * M_PI / 180.0;
    mData.rotation_rate_vessel_xv2 = strtod(nmea[8].c_str(), 0) * M_PI / 180.0;
    mData.horizontal_speed_course = strtod(nmea[9].c_str(), 0) * M_PI / 180.0;
    mData.spd_horizontal = strtod(nmea[10].c_str(), 0);
    mData.spd_vessel_xv1 = strtod(nmea[11].c_str(), 0);
    mData.spd_vessel_xv2 = strtod(nmea[12].c_str(), 0);
    mData.spd_vessel_xv3 = strtod(nmea[13].c_str(), 0);

    mData.stddev_att_heading = strtod(nmea[14].c_str(), 0) * M_PI / 180.0;
    mData.stddev_att_roll = strtod(nmea[15].c_str(), 0) * M_PI / 180.0;
    mData.stddev_att_pitch = strtod(nmea[16].c_str(), 0) * M_PI / 180.0;
    mData.stddev_spd_north = strtod(nmea[17].c_str(), 0);
    mData.stddev_spd_east = strtod(nmea[18].c_str(), 0);
    mData.stddev_spd_up = strtod(nmea[19].c_str(), 0);

    mUpdateFlags |= (UPD_HEADING | UPD_ATTITUDE | UPD_HEAVE
                        | UPD_BODY_ROTATION_RATE | UPD_BODY_SPEED
                        | UPD_DEV_ATT | UPD_DEV_SPD);
}

void HalliburtonSASParser::parseStatus(const NmeaRecord& nmea)
{
    uint32_t status = strtol(nmea[2].c_str(), 0, 16);

    mData.other_status = status;

    mData.status_LSB = ((status & 0x7c000000) >> 25)
            | ((status & 0x0000f000) >> 3);

    mData.algo_status_LSB = (status & 0x00000001 ? ALIGNE : 0)
            | (status & 0x00000002 ? FINE_ALIGNE : 0)
            | (status & 0x00000004 ? NAVIG : 0)
            | (status & 0x00000100 ? GPS_RECEIVED :0)
            | (status & 0x00000200 ? LOG_RECEIVED :0)
            | (status & 0x00000400 ? USBL_RECEIVED : 0)
            | (status & 0x00000800 ? DEPTH_RECEIVED :0)
            | (status & 0x00010000 ? GPS_VALID :0)
            | (status & 0x00020000 ? LOG_VALID :0)
            | (status & 0x00040000 ? USBL_VALID :0)
            | (status & 0x00080000 ? DEAD_RECKONING : 0)
            | (status & 0x02000000 ? (ALT_SATURATION | SPD_SATURATION | INTERPOLATION_MISSED) : 0);
    mData.algo_status_MSB = (status & 0x00000200 ? WATERTRACK_RECEIVED :0);


    mData.user_status = ((status & 0x7c0000000) >> 10)
          | (status & 0x00010000 ? GPS_RECEIVED_VALID : 0)
          | (status & 0x00020000 ? DVL_RECEIVED_VALID : 0)
          | (status & 0x00040000 ? USBL_RECEIVED_VALID : 0)
          | (status & 0x01000000 ? (FOG_ANOMALY | ACC_ANOMALY) : 0)
          | ((status & 0x00000007) << 27);
    mUpdateFlags |= UPD_STATUS;

}

