/*
 * PhinsRaw.hpp
 *
 *  Created on: 08.02.2013
 *      Author: jrenken
 */

#ifndef _PHINS_IXSEA_PHINSRAW_HPP_
#define _PHINS_IXSEA_PHINSRAW_HPP_

#include <stdint.h>
#include <base/time.h>

namespace phins_ixsea {

    enum UpdateFlags  {
        UPD_POSITION = 1,
        UPD_HEADING = 2,
        UPD_ATTITUDE = 4,
        UPD_HPR = 6,
        UPD_SPEED = 8,
        UPD_UTMPOS = 16,
        UPD_HEAVE = 32,
        UPD_DEV_POS = 64,
        UPD_DEV_ATT = 128,
        UPD_DEV_SPD = 256,
        UPD_ALGO_STATUS = 512,
        UPD_IO_STATUS = 1024,
        UPD_USER_STATUS = 2048,
        UPD_STATUS = 3584,
        UPD_TIME = 8192
    };


    struct PhinsRawData {
        double  pos_latitude;
        double  pos_longitude;
        double  pos_altitude;

        double  att_heading;
        double  att_roll;
        double  att_pitch;

        double  spd_east;
        double  spd_north;
        double  spd_up;

        char    utm_lat_zone;
        int     utm_lon_zone;
        double  utm_pos_east;
        double  utm_pos_north;
        double  utm_altitude;

        double  heave_surge;
        double  heave_sway;
        double  heave_heave;

        double  stddev_pos_latitude;
        double  stddev_pos_longitude;
        double  stddev_pos_altitude;

        double  stddev_att_heading;
        double  stddev_att_roll;
        double  stddev_att_pitch;

        double  stddev_spd_north;
        double  stddev_spd_east;
        double  stddev_spd_up;


        uint32_t    status_LSB;
        uint32_t    status_MSB;
        uint32_t    algo_status_LSB;
        uint32_t    algo_status_MSB;

        uint32_t    user_status;

        base::Time time;

    };

}  // namespace phins_ixsea


#endif /* _PHINS_IXSEA_PHINSRAW_HPP_ */
