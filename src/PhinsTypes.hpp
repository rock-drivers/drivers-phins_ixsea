#ifndef _PHINS_IXSEA_PHINSTYPES_HPP_
#define _PHINS_IXSEA_PHINSTYPES_HPP_
/**
 * @file PhinsTypes.hpp
 * @brief Phins ixsea's datatypes and configuration file
 */

/*
 * PhinsTypes.hpp
 *
 *  Created on: 14.06.2012
 *      Author: jrenken
 *
 * DataTypes provided by the Phins
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
 *
 *  Heading   - current compass direction
 *  	$HEHDT, x.xxxxx, T*hh<CR><LF>	- x.xxx(xx) is the true heading in degrees
 *
 *
 *
 * 	 $PIXSE,ATITUD,x.xxx,y.yyy*hh<CR><LF>
 * 	 	x.xxx  is the roll in degrees
 * 	 	y.yyy	is the pitch in degrees
 *
 *
 * 
 *
 *
 *
 */
 

#include <string>



 namespace phins_ixsea

 {


const int PORTX = 8110; // repater port input port
const int PORT_PHINS = 8113;
const int PORT_HALLI = 8111;
const int PORT_HEADING = 8112;

const int PHINS_PACKET_SIZE = 8192;

enum Protocol {
    PhinsStandard,
    HalliburtonSAS
};
 


/**
* @brief data from PHINS STANDARD  or HALLIBURTON SAS
*/
struct Utmwgs{

	char latitudeZone; // [C,D, E,...,X ]\ I, \O
	int longitudeZone; // [3,4, .., 60 ]
	double  eastPosition; // m
	double  northPosition; // m
	double  altitude; // m 

};
/**
 * @brief data struct  describing  phins system status,
 * Description in INS Part 5 Library Interface, Table V3(LSB) and V4(MSB)
 */
const  std::string phinsSystemStatus[] = {
	"serial_in_r_err", // start LSB
	"input_a_error",
	"input_b_error",
	"input_c_error",
	"input_d_error",
	"input_e_error",
	"reserved_6",	
	"reserved_7",
	"input_r_activity",
	"input_a_activity",
	"input_b_activity",
	"input_c_activity",
	"input_d_activity",
	"input_e_activity",
	"reserved_14",
	"reserved_15",
	"output_r_full",
	"output_a_full",
	"output_b_full",
	"output_c_full",
	"output_d_full",
	"output_e_full",
	"ethernet_port_full",
	"reserved_23",
	"external_time_used",
	"reserved_25",
	"ethernet_port_activity",
	"pulse_in_a_activity",
	"pulse_in_b_activity",
	"pulse_in_c_activity", // not used
	"pulse_in_d_activity", // not used
	"reserved_31",
	"dvl_bt_detected ",// start MSB
	"dvl_wt_detected",
	"gps_detected",
	"gps2_detected",
	"usbl_detected",
	"lbl_detected",
	"depth_detected",
	"emlog_detected",
	"dmi_detected",
	"utc_detected",
	"altitude_detected",
	"pps_detected",
	"zup_mode_activated",
	"reserved_45",
	"manual_gps_detected",
	"ctd_detected",
	"simulation_mode",
	"reserved_49",
	"dsp_incompability",
	"heading_alert",
	"position_alert",
	"wait_for_position",
	"reserved_54",
	"reserved_55",
	"reserved_56",
	"reserved_57",
	"reserved_58",
	"mpc_overload",
	"power_supply_failure",
	"rd_mode", // not used;
	"conviguration_saved",
	"reserved_63"
};
/**
 * @brief data struct  describing  phins agorithm,
 * Description in INS Part 5 Library Interface, Table V5(LSB) and V6(MSB)
 */
const std::string phinsAlgStatus[] = {
	"navigation", //start lsb bit0
	"alignment",
	"fine_alignement",
	"dead_reckoning",
	"gps_altitude",
	"depthsensor_altitude",
	"zero_altitude",
	"hydro_altitude",
	"log_received",
	"log_valid",
	"log_waiting",
	"log_rejected",
	"gps_received",
	"gps_valid",
	"gps_waiting",
	"gps_rejected",
	"usbl_received",
	"usbl_valid",
	"usbl_waiting",
	"usbl_rejected",
	"depth_received",
	"depth_valid",
	"depth_waiting",
	"depth_rejected",
	"lbl_received",
	"lbl_val3yyid",
	"lbl_waiting",
	"lbl_rejected",
	"altitude_saturation",
	"speed_saturation",
	"interpolation_missed",
	"heave_initialisation",
	"watertrack_received", // start msb bit 0
	"watertrack_valid",
	"watertrack_waiting",
	"watertrack_rejected",
	"gps2_received",
	"gps2_valid",
	"gps2_waiting",
	"gps2_rejected",
	"reserved_40",
	"reserved_41",
	"reserved_42",
	"reserved_43",
	"altitude_received",
	"altitude_valid",
	"altitude_waiting",
	"altitude_rejected",
	"zupt_mode_activated",
	"zupt_mode_valid",
	"autostaticbench_zupt_mode",
	"autostaticbench_zupt_valid",
	"reserved_51",
	"reserved_52",
	"fast_alignment",
	"emulation_mode",
	"emlog_received",
	"emlog_valid",
	"emlog_waiting",
	"emlog_rejected",
	"manualgps_received",
	"manualgps_valid",
	"manualgps_waiting",
	"manualgps_rejected",
	
};


enum PhinsHeaders {
	sPixse,
	sHehdt,
	sTime,
	sAtitude,
	sPosition,
	sSpeed,
	sUtmwgs,
	sHeave,
	sStdhrp,
	sStdpos,
	sStdspd,
	sLogin,
	sLogdvl,
	sLogwat,
	sGps1,
	sGps2,
	sGpsmin,
	sDepth,
	sUsbl,
	sLbl,
	sUtc,
	sEm,
	sDdreck,
	sAlgstatus,
	sSensor_hex,
	sStatus,
	sInstatus,
};


enum HallisHeaders{
	sPixseHalli,
	sHspos,
	sHsatit,
	sHsstat
	

};


} 
#endif /* _PHINS_IXSEA_PHINSTYPES_HPP_ */
