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


    enum NavigationMode {
        UNKNOWN_MODE = 0,
        COARSE_ALIGN_MODE,
        FINE_ALIGN_MODE,
        NAVIGATION_MODE,
        DEGRADED_MODE,
        FAILURE_MODE,
    };


    struct PhinsStatus {
        base::Time  time;
        uint32_t    sensor_status;
        uint32_t    input_status;
        uint32_t    output_status;
        uint32_t    system_status;
        uint32_t    mode;

    };

    struct PhinsExtStatus {
        base::Time  time;
        uint32_t    status_lsb;
        uint32_t    status_msb;
        uint32_t    algo_status_lsb;
        uint32_t    algo_status_msb;
        uint32_t    user_status;
    };


}  // namespace phins_ixsea

#endif /* _PHINS_IXSEA_PHINSTYPES_HPP_ */
