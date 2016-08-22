/*
 * PhinsRaw.hpp
 *
 *  Created on: 08.02.2013
 *      Author: jrenken
 */

#ifndef _PHINS_IXSEA_PHINSRAW_HPP_
#define _PHINS_IXSEA_PHINSRAW_HPP_

#include <stdint.h>
#include <base/Time.hpp>

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
        UPD_IO_STATUS = 512,
        UPD_ALGO_STATUS = 1024,
        UPD_EXT_STATUS = 1536,
        UPD_USER_STATUS = 2048,
        UPD_STATUS = 3584,
        UPD_OTHER_STATUS = 8192,
        UPD_TIME = 16384,
        UPD_DVL = 16384,
        UPD_BODY_ROTATION_RATE = 0x00010000,
        UPD_BODY_SPEED = 0x00020000

    };

    enum PhinsStatusL {
        SERIAL_IN_R_ERR = 0x00000001,
        INP_A_ERR  = 0x00000002,
        INP_B_ERR  = 0x00000004,
        INP_C_ERR = 0x00000008,
        INP_D_ERR = 0x00000010,
        INP_E_ERR = 0x00000020,
        INPUT_R_ACTIVITY = 0x00000100,
        INPUT_A_ACTIVITY = 0x00000200,
        INPUT_B_ACTIVITY = 0x00000400,
        INPUT_C_ACTIVITY = 0x00000800,
        INPUT_D_ACTIVITY = 0x00001000,
        INPUT_E_ACTIVITY = 0x00002000,
        OUTPUT_R_FULL = 0x00010000,
        OUTPUT_A_FULL = 0x00020000,
        OUTPUT_B_FULL = 0x00040000,
        OUTPUT_C_FULL = 0x00080000,
        OUTPUT_D_FULL = 0x00100000,
        OUTPUT_E_FULL = 0x00200000,
        ETHERNET_PORT_FULL = 0x00400000,
        EXTERNAL_TIME_USED = 0x01000000,
        ETHERNET_PORT_ACTIVITY = 0x04000000,
        PULSE_IN_A_ACTIVITY = 0x08000000,
        PULSE_IN_B_ACTIVITY = 0x10000000,
        PULSE_IN_C_ACTIVITY =0x20000000,
        PULSE_IN_D_ACTIVITY = 0x40000000
    };

    enum PhinsStatusH {
        DVL_BT_DETECTED = 0x00000001,
        DVL_WT_DETECTED = 0x00000002,
        GPS_DETECTED = 0x00000004,
        GPS2_DETECTED = 0x00000008,
        USBL_DETECTED = 0x00000010,
        LBL_DETECTED  = 0x00000020,
        DEPTH_DETECTED = 0x00000040,
        EMLOG_DETECTED = 0x00000080,
        DMI_DETECTED = 0x00000100,
        UTC_DETECTED = 0x00000200,
        ALTITUDE_DETECTED  = 0x00000400,
        PPS_DETECTED = 0x00000800,
        ZUP_MODE_ACTIVATED = 0x00001000,
        MANUAL_GPS_DETECTED = 0x00004000,
        CTD_DETECTED = 0x00008000,
        SIMULATION_MODE = 0x00010000,
        DSP_INCOMPATIBILITY = 0x00040000,
        HEADING_ALERT = 0x00080000,
        POSITION_ALERT = 0x00100000,
        WAIT_FOR_POSITION = 0x00200000,
        MPC_OVERLOAD = 0x08000000,
        POWER_SUPPLY_FAILURE = 0x10000000,
        RD_MODE = 0x20000000,
        CONFIGURATION_SAVED = 0x40000000
    };

    enum PhinsAlgoStatusL {
        NAVIG = 0x00000001,
        ALIGNE = 0x00000002,
        FINE_ALIGNE = 0x00000004,
        DEAD_RECKONING =0x00000008,
        GPS_ALTITUDE =0x00000010,
        DEPTHSENSOR_ALTITUDE =0x00000020,
        ZERO_ALTITUDE =0x00000040,
        HYDRO_ALTITUDE =0x00000080,
        LOG_RECEIVED =0x00000100,
        LOG_VALID =0x00000200,
        LOG_WAITING =0x00000400,
        LOG_REJECTED =0x00000800,
        GPS_RECEIVED =0x00001000,
        GPS_VALID =0x00002000,
        GPS_WAITING =0x00004000,
        GPS_REJECTED =0x00008000,
        USBL_RECEIVED =0x00010000,
        USBL_VALID =0x00020000,
        USBL_WAITING =0x00040000,
        USBL_REJECTED  =0x00080000,
        DEPTH_RECEIVED  =0x00100000,
        DEPTH_VALID =0x00200000,
        DEPTH_WAITING  =0x00400000,
        DEPTH_REJECTED  =0x00800000,
        LBL_RECEIVED =0x01000000,
        LBL_VALID =0x02000000,
        LBL_WAITING = 0x04000000,
        LBL_REJECTED  =0x08000000,
        ALT_SATURATION =0x10000000,
        SPD_SATURATION  =0x20000000,
        INTERPOLATION_MISSED =0x40000000,
        HEAVE_INITIALISATION =0x80000000
    };

    enum PhinsAlgoStatusH {
        WATERTRACK_RECEIVED = 0x00000001,
        WATERTRACK_VALID = 0x00000002,
        WATERTRACK_WAITING = 0x00000004,
        WATERTRACK_REJECTED = 0x00000008,
        GPS2_RECEIVED = 0x00000010,
        GPS2_VALID = 0x00000020,
        GPS2_WAITING = 0x00000040,
        GPS2_REJECTED = 0x00000080,
        ALTITUDE_RECEIVED = 0x00001000,
        ALTITUDE_VALID = 0x00002000,
        ALTITUDE_WAITING = 0x00004000,
        ALTITUDE_REJECTED = 0x00008000,
        ZUPT_MODE_ACTIVATED = 0x00010000,
        ZUPT_MODE_VALID = 0x00020000,
        AUTOSTATICBENCH_ZUPT_MODE = 0x00040000,
        AUTOSTATICBENCH_ZUPT_VALID = 0x00080000,
        STATIC_CONVERGENCE_ON = 0x00100000,
        STATIC_CONV_GO_TO_NAV = 0x00200000,
        FAST_ALIGNEMENT = 0x00400000,
        EMULATION_MODE = 0x00800000,
        EMLOG_RECEIVED = 0x01000000,
        EMLOG_VALID = 0x02000000,
        EMLOG_WAITING = 0x04000000,
        EMLOG_REJECTED = 0x08000000,
        MANUALGPS_RECEIVED = 0x10000000,
        MANUALGPS_VALID = 0x20000000,
        MANUALGPS_WAITING = 0x40000000,
        MANUALGPS_REJECTED = 0x80000000
    };

    enum PhinsUserStatus {
        DVL_RECEIVED_VALID = 0x00000001,
        GPS_RECEIVED_VALID = 0x00000002,
        DEPTH_RECEIVED_VALID = 0x00000004,
        USBL_RECEIVED_VALID = 0x00000008,
        LBL_RECEIVED_VALID = 0x00000010,
        GPS2_RECEIVED_VALID = 0x00000020,
        EMLOG_RECEIVED_VALID = 0x00000040,
        MANUAL_GPS_RECEIVED_VALID = 0x00000080,
        TIME_RECEIVED_VALID = 0x00000100,
        FOG_ANOMALY = 0x00000200,
        ACC_ANOMALY = 0x00000400,
        TEMPERATURE_ERR = 0x00000800,
        CPU_OVERLOAD = 0x00001000,
        DYNAMIC_EXCEDEED = 0x00002000,
        SPEED_SATURATION = 0x00004000,
        ALTITUDE_SATURATION = 0x00008000,
        INPUT_A_ERR = 0x00010000,
        INPUT_B_ERR = 0x00020000,
        INPUT_C_ERR = 0x00040000,
        INPUT_D_ERR = 0x00080000,
        INPUT_E_ERR = 0x00100000,
        OUTPUT_A_ERR = 0x00200000,
        OUTPUT_B_ERR = 0x00400000,
        OUTPUT_C_ERR = 0x00800000,
        OUTPUT_D_ERR = 0x01000000,
        OUTPUT_E_ERR = 0x02000000,
        HRP_INVALID = 0x04000000,
        ALIGNEMENT = 0x08000000,
        FINE_ALIGNEMENT = 0x10000000,
        NAVIGATION = 0x20000000,
        DEGRADED = 0x40000000,
        FAILURE = 0x80000000
    };

    enum PhinsStatusSensor {
        STATUS_DV_VALID = 0x00000001,
        STATUS_GPS_VALID = 0x00000002,
        STATUS_DPTH_VALID = 0x00000004,
        STATUS_USBL_VALID = 0x00000008,
        STATUS_LBL_VALID = 0x00000010,
        STATUS_GPS2_VALID = 0x00000020,
        STATUS_EMLOG_VALID = 0x00000040,
        STATUS_MANGPS_VALID = 0x00000080,
        STATUS_TIME_VALID = 0x00000100
    };

    enum PhinsStatusInput {
        STATUS_INPUTA_ERR = 0x00000001,
        STATUS_INPUTB_ERR = 0x00000002,
        STATUS_INPUTC_ERR = 0x00000004,
        STATUS_INPUTD_ERR = 0x00000008,
        STATUS_INPUTE_ERR = 0x00000010
    };
    enum PhinsStatusOutput {
        STATUS_OUTPUTA_ERR = 0x00000001,
        STATUS_OUTPUTB_ERR = 0x00000002,
        STATUS_OUTPUTC_ERR = 0x00000004,
        STATUS_OUTPUTD_ERR = 0x00000008,
        STATUS_OUTPUTE_ERR = 0x00000010
    };

    enum PhinsStatusSystem {
        STATUS_FOG = 0x00000001,
        STATUS_ACC = 0x00000002,
        STATUS_TEMP = 0x00000004,
        STATUS_CPU = 0x00000008,
        STATUS_DYNAMIC = 0x00000010,
        STATUS_SPEED = 0x00000020,
        STATUS_ALTITUDE = 0x00000040,
        STATUS_HPR = 0x00000080,
    };

    enum PhinsStatusMode {
        STATUS_ALIGNE = 0x00000001,
        STATUS_FINE_ALIGNE = 0x00000002,
        STATUS_NAVIGATION = 0x00000004,
        STATUS_DEGRADED = 0x00000008,
        STATUS_FAILURE = 0x00000010,

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

        double  rotation_rate_vessel_xv1;
        double  rotation_rate_vessel_xv2;
        double  rotation_rate_vessel_xv3;

        double  horizontal_speed_course;
        double  spd_horizontal;
        double  spd_vessel_xv1;
        double  spd_vessel_xv2;
        double  spd_vessel_xv3;

        double  dvl_altitude;
        double  dvl_misaligne_estimation;
        double  dvl_scale_fcator_corr_estimation;

        double  sound_speed;

        uint32_t    status_LSB;
        uint32_t    status_MSB;
        uint32_t    algo_status_LSB;
        uint32_t    algo_status_MSB;

        uint32_t    user_status;

        uint32_t    other_status;

        base::Time time;

    };

}  // namespace phins_ixsea


#endif /* _PHINS_IXSEA_PHINSRAW_HPP_ */
