/*
 * PhinsTypes.hpp
 *
 *  Created on: 14.06.2012
 *      Author: jrenken
 */

#ifndef _PHINS_IXSEA_PHINSTYPES_HPP_
#define _PHINS_IXSEA_PHINSTYPES_HPP_

#include <base/time.h>
/* DataTypes provided by the Phins
 *
 * Phins can provide the following data
 *
 *                          available in       Phins Standard        Halliburton SAS
 *  - IMU Data
 *  - Heading  \                                    x                       x
 *  - Roll      > attitude                          x                       x
 *  - Pitch    /                                    x                       x
 *
 *  - Heading standard deviation                    x                       x
 *  - Roll sd                                       x                       x
 *  - Pitch sd                                      x                       x
 *  - Heading rate (speed)
 *  - Roll rate
 *  - Pitch rate
 *
 *  - Rotation rate xv1                                                     x
 *  - Rotation rate xv2                                                     x
 *  - Rotation rate xv3                                                     x
 *
 *  - Delayed Heave
 *  - Heave                                         x                       x
 *  - Surge                                         x
 *  - Sway                                          x
 *
 *  - Heave speed
 *  - Surge speed
 *  - Sway speed
 *
 *  - Acceleration xv1
 *  - Acceleration xv2
 *  - Acceleration xv3
 *
 *  - Date of data
 *  - Timerstamp of data                            x                       x
 *  - Pulse Reception Time
 *
 *  - Latitude                                      x                       x
 *  - Longitude                                     x                       x
 *  - Altitude or depth                             x                       x
 *  - Latitude standard deviation                   x                       x
 *  - Longitude sd                                  x                       x
 *  - Altitude or depth sd                          x                       x
 *
 *  - Speed xv1                                                             x
 *  - Speed xv2                                                             x
 *  - Speed xv3                                                             x
 *  - North/South speed                             x
 *  - East/West speed                               x
 *  - Vertical Speed                                x
 *  - North speed sd                                x                       x
 *  - East speed sd                                 x                       x
 *  - Vertical speed sd                             x                       x
 *  - Horizontal speed norm                                                 x
 *  - True course                                                           x
 *  - Travelled distance
 *
 *  - INS system status                             x
 *  - INS algorythm status                          x
 *  - INS user status                               x
 *  - INS sensor status                             x
 *  - Other status                                  x                       x
 *  - Checksum                                      x
 *
 *  Secondary data
 *  - Log speed                                     x
 *  - Log heading misalignement                     x                       x
 *  - Log pitch misalignement                       x
 *  - Log scale factor error %                      x                       x
 *  - Sound velocity                                x                       x
 *  - Dvl altitude                                  x                       x
 *  - Conductivity
 *  - Temperature
 *  - Pressure or depth                             x
 *  - GPS Latitude                                  x
 *  - GPS Longitude                                 x
 *  - GPS Altitude                                  x
 *  - USBL Latitude                                 x
 *  - USBL Longitude                                x
 *  - USBL Altitude                                 x
 *  - LBL Latitude                                  x
 *  - LBL Longitude                                 x
 *  - LBL Altitude                                  x
 *  - LBL Range                                     x
 *  - LOCH EM Speed                                 x
 *  - UTC Time                                      x
 *  - Dead Reckoning Data                           x
 *
 *
 *  Grouped data provided through Halliburton SAS
 *  -
 *
 */

namespace phins_ixsea {

    enum Protocol {
         PhinsStandard,
         HalliburtonSAS
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
        NAVIGATION_BIT = 0x00000001,
        ALIGNMENT = 0x00000002,
        FINE_ALIGNMENT = 0x00000004,
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
        SPEED_SATURATION = 0x00003000,
        ALTITUDE_SATURATION = 0x00004000,
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
        DEGRADED_MODE = 0x40000000,
        FAILURE_MODE = 0x80000000
    };

    enum NavigationMode {
        UNKNOWN_MODE = 0,
        COARSE_ALIGN_MODE,
        FINE_ALIGN_MODE,
        NAVIGATION_MODE,
        ERROR_MODE
    };


//    enum PhinsInputStatus {
//        INP_IDLE = 0x00000000,
//        INP_R_ERROR = 0x00000001,
//        INP_R_ACTIVITY = 0x00000002,
//        INP_R_MASK = 0x0000000f,
//        INP_A_ERROR = 0x00000010,
//        INP_A_ACTIVITY = 0x00000020,
//        INP_A_MASK = 0x000000f0,
//        INP_B_ERROR = 0x00000100,
//        INP_B_ACTIVITY = 0x00000200,
//        INP_b_MASK = 0x00000f00,
//        INP_C_ERROR = 0x00001000,
//        INP_C_ACTIVITY = 0x00002000,
//        INP_c_MASK = 0x0000f000,
//        INP_D_ERROR = 0x00010000,
//        INP_D_ACTIVITY = 0x00020000,
//        INP_D_MASK = 0x000f0000,
//        INP_E_ERROR = 0x00100000,
//        INP_E_ACTIVITY = 0x00200000,
//        INP_E_MASK = 0x00f00000,
//        ETH_ACTIVITY = 0x01000000,
//        ETH_FULL = 0x02000000,
//        ETH_MASK = 0x0f000000
//    };
//
//    enum PhinsOutputStatus {
//        OUT_R_FULL  = 1,
//        OUT_A_FULL  = 2,
//        OUT_B_FULL  = 4,
//        OUT_C_FULL  = 8,
//        OUT_D_FULL  = 16,
//        OUT_E_FULL  = 32,
//    };
//
//    enum PhinsPulsInput {
//        PULS_INP_A = 1,
//        PULS_INP_B = 1,
//        PULS_INP_C = 1,
//        PULS_INP_D = 1
//    };
//
//    enum ExtSensorStatus {
//        SENSOR_DETECTED = 1,
//        SENSOR_RECEIVED = 2,
//        SENSOR_VALID = 4,
//        SENSOR_REJECTED = 8
//    };
//
//
//    struct PhinsStatus {
//        base::Time  time;
//        uint32_t    input_status;
//        uint32_t    puls_status;
//        uint32_t    output_status;
//        uint32_t    device_status;
//        uint32_t    dvl_bt_status;
//        uint32_t    dvl_wt_status;
//        uint32_t    gps_status;
//        uint32_t    gps2_status;
//        uint32_t    man_gps_status;
//        uint32_t    usbl_status;
//        uint32_t    lbl_status;
//        uint32_t    depth_status;
//        uint32_t    altitude_status;
//        uint32_t    processing_status;
//    };
    struct PhinsStatus {
        base::Time  time;
        uint32_t    status_lsb;
        uint32_t    status_msb;
        uint32_t    algo_status_lsb;
        uint32_t    algo_status_msb;
        uint32_t    user_status;
    };

}  // namespace phins_ixsea

#endif /* _PHINS_IXSEA_PHINSTYPES_HPP_ */
