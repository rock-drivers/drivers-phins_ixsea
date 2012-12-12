/*
 * HalliburtonSASParser.cpp

#include <base/eigen.h>
 *
 *  Created on: 12.06.2012
 *      Author: jrenken
 *
 *    Halliburton strings are
 *    	$PIXSE,HSPOS_,hhmmss.ss, LLll.llllll,H,LLLmm.mmmmmm,D,d.dd,a.aa,x.xx,y.yy,z.zz,d.dd,nn,c,e.e
			,n.n,m.mmmm,s.ssss,v.v*hh<CR><LF>
		$PIXSE,HSATIT,h.hhh,r.rrr,p.ppp,h.h,a.aaa,b.bbb,c.ccc,d.ddd,e.eee,f.fff,g.ggg,h.hhh,i.ii,j.jj,k.kk,l.ll,m.mm,n.nn
		*hh<CR><LF>

 *
 */


#include <iostream>
#include <base/eigen.h>

#include "HalliburtonSASParser.hpp"

namespace phins_ixsea
{

    HalliburtonSASParser::HalliburtonSASParser()
    {
        // TODO Auto-generated constructor stub
    	std::cout<< "hallis konstruktor"<<std::endl;
    	initHallisHeaderMap();

    }

    void HalliburtonSASParser::parseEnsemble(std::string buffer, size_t size){
    	std::cout<< " ...HalliburtonSASParser is parsing.. "<<std::endl;

    	if(mNmeaRecord.setRecord(buffer)){

    		if ( ! mNmeaRecord.header().compare("PIXSE")){
    			// std::cout<<"hspo"<<std::endl;
				 switch(hallisHeaderMap[mNmeaRecord.header2()])
					{

					case sHspos :
						//std::cout<<"hspo"<<std::endl;
						parseHspos();
						break;
					case sHsatit:
						parseHsatit();
						break;
					case sHsstat: // parse system status
						parseHsstat();
						break;
					default:
						//std::cout<< " default"<<std::endl;
						break;

					}
			 }
    		else{
    			std::cout<<"found no PIXSE"<<std::endl;
    		}
    	}else{
    		std::cout<<".. found nothing to parse "<<std::endl;
    	}
    }

    int HalliburtonSASParser::extractPacket (uint8_t const *buffer, size_t buffer_size) const {

    	return Parser::extractPacket(buffer,  buffer_size);
    }

    /**
        * @brief
        *
        *  $PIXSE,HSPOS_,hhmmss.ss, LLll.llllll,H,LLLmm.mmmmmm,D,d.dd,a.aa,x.xx,y.yy,z.zz,d.dd,nn,c,e.e
		*,n.n,m.mmmm,s.ssss,v.v*hh<CR><LF>
		*
        *  0 string PIXSE
        *  1 string HSPOS_
        *  2 hhmmss.ss  UTC time stamp if system is UTC synchronized,or in system time if not   float (0.12)
        *  3 LLll.llllll   Latitude in degress(LL), Iminutes(II) and decimals of minutes (IIIIII)(0.123456)
        *  4 H Hemisphere N or S  character
        *  5 LLLmm.mmmmmm  Longitude integer degrees(LLL),minutes(mm) and decimals of minutes (mmmmmm) (0.123456)
        *  6 D Hemisphere N or S  character
        *  7 d.dd Depth in meters  float (0.12) [m]
        *  8 a.aa altitude of dvl  float (0.12) [m]
        *  9 x.xx  Latitude standard deviation error in meters  float (0.12) [m]
        *  10 y.yy  Longitude standard deviation error in meters  float (0.12) [m]
        *  11 z.zz  Longitude/Latitude covraiance error in meters  float (0.12) [m]
        *  12 d.dd  Depth standard deviation float (0.12) [m]
        *  13 nn UTM Zone Latitude integer
        *  14 c UTM Zone Longitude character
        *  15 e.e UTM Postition East in meters float (0.1) [m]
        *  16 n.n UTM Postition North in meters float (0.1) [m]
        *  17 m.mmmm    Estimtate of DVL course misalignment in degrees float (0.1234) s [deg]
        *  18 s.ssss    Estimtate of DVL  scale factor correction% float (0.1234) s [%]
        *  19 v.v speed of sound in float (0.1) [m/s]
        *  20 hh checksum nmea
        *
        */

    int HalliburtonSASParser::parseHspos(){

   	  const char* p;

   	  if (mNmeaRecord.size() > 19  ){

		  p = mNmeaRecord.field(2).c_str();
		  // std::cout<< "vel x "<< p<< std::endl;
			   //_velocity.x() = atof(p);

		// set
	    p = mNmeaRecord.field(13).c_str();
	      _utmwgs.latitudeZone = atoi(p); // int

	    p = mNmeaRecord.field(14).c_str();
	      _utmwgs.longitudeZone = *p ; //char

		p = mNmeaRecord.field(15).c_str();
		  _utmwgs.eastPosition = atof(p);

		p = mNmeaRecord.field(16).c_str();
			_utmwgs.northPosition = atof(p);

		p = mNmeaRecord.field(8).c_str();	 //altitude of dvl
		_utmwgs.altitude= atof(p);


   	  }
   	  else{
   		  return 1;
   	  }
   	  return 0;
    }

    /**
     * @brief
     *
     *  $PIXSE,HSATIT,h.hhh,r.rrr,p.ppp,h.h,a.aaa,b.bbb,c.ccc,d.ddd,e.eee,f.fff,g.ggg,h.hhh,
     *  ji.ii,j.jj,k.kk,l.ll,m.mm,n.nn*hh<CR><LF>
     *  $PIXSE,HSATIT,163.535,-1.800,-0.662,-0.0,0.002,-0.004,0.004,274.998,41.660,-15.242,-38.757,-1.041,1.99,0.07,0.10,18.65,13.58,10.00*4E
     *  0 string PIXSE
     *  1 string HSATIT
     *  2 h float(0.123) heading [deg]
     *  3 r float (0.123) roll [deg]
     *  4 p float (0.123) pitch [deg]
     *  5 h float (0.1) heave[m]
     *  6 a float (0.123) rotation rate xv3 [deg/m]
     *  7 b float (0.123) rotation rate xv2 [deg/m]
     *  8 c float (0.123) rotation rate xv3 [deg/m]
     *  9 d float (0.123) horz speed [deg]
     *  10 e float (0.123) horz speed  [m/s]
     *  11 f float (0.123) speed xv1 [m/s]
     *  12 g float (0.123) speed xv2 [m/s]
     *  13 h float (0.123) speed xv3 [m/s]
     *  14 i float (0.12) heading std dev error [deg]
     *  15 j float (0.12) roll std dev error [deg]
     *  16 k float (0.12) pitch std dev error [deg]
     *  17 l float (0.12) north speed std dev error [m/s]
     *  18 m float (0.12) east speed std dev error [m/s]
     *  19 n float (0.12) vertical  speed std dev error [m/s]
     *  20 checksum nmea
     *
     */
    int HalliburtonSASParser::parseHsatit(){

 	  const char* p;

 	  if (mNmeaRecord.size() > 19  && !mNmeaRecord.field(0).compare("PIXSE")   &&  !mNmeaRecord.field(1).compare("HSATIT") ){

 		  const char *h = mNmeaRecord.field(2).c_str();
 		  const char *r = mNmeaRecord.field(3).c_str();
 		  	  	  	  p = mNmeaRecord.field(4).c_str();

 		 _orientation =
 				   Eigen::AngleAxisd(M_PI / 180 * atof(r), Eigen::Vector3d::UnitX()) *
 			       Eigen::AngleAxisd(M_PI / 180 * atof(p), Eigen::Vector3d::UnitY()) *
 			       Eigen::AngleAxisd(M_PI / 180 * atof(h), Eigen::Vector3d::UnitZ());


		  p = mNmeaRecord.field(11).c_str();
		  // std::cout<< "vel x "<< p<< std::endl;
			   _velocity.x() = atof(p);
		  p = mNmeaRecord.field(12).c_str();
		 //std::cout<< "vel x "<< p<< std::endl;
			  _velocity.y() = atof(p);

		  p = mNmeaRecord.field(13).c_str();
		  //std::cout<< "vel x "<< p<< std::endl;
			   _velocity.z() = atof(p);
	  }
 	  else {

 		  return 1;

 	  }

 	  return 0;
    }
    /** @brief Sensor and System Status
     *
     */
    int HalliburtonSASParser::parseHsstat(){

		if ( !mNmeaRecord.field(0).compare("PIXSE")   &&  !mNmeaRecord.field(1).compare("HSSTAT") ){

			  std::cout<<"parse status "<<mNmeaRecord.field(2)<<std::endl;
			  const std::string& lsbStr = mNmeaRecord.field(2);
			  std::stringstream lsbStrs(lsbStr);
			  int nLsb;

			  lsbStrs >> std::hex >> nLsb;
			  std::string msg;

			  for (int i = 31; i >= 0 ; i-- ){
				  if(nLsb &  (1 << i)) { // lsb bit gesetzt
					  msg += halliburtonStatus[i] + "\n";
				  }
			  }

			  if(msg.size()== 0){
				  msg += "nothing to report \n";
			  }
			  else{ // write log message // @TODO nicht jede meldung soll abbrechen .
										  // wo wird das hingeschriebne ??
				  std::cout<< " else log message\n"<<std::endl;
				//  throw  oro_marum::LogMessage(oro_marum::Debug, msg);

			  }

			  std::cout<<"****** system status*************\n"<<msg<<
					  "*****************************************"<<std::endl;
		}
		else {
			return 1;

		}

    }

    Eigen::Vector3d HalliburtonSASParser::getVelocity(){
    	return _velocity;
    }

    void HalliburtonSASParser::initHallisHeaderMap(){

        	 hallisHeaderMap["PIXSE"] = sPixseHalli;
        	 hallisHeaderMap["HSPOS_"] = sHspos;
        	 hallisHeaderMap["HSATIT"] = sHsatit;
        	 hallisHeaderMap["HSSTAT"] = sHsstat;

    }


   void HalliburtonSASParser::getRBS( base::samples::RigidBodyState *rbs){

    	std::cout<< "get hallis rbs"<<std::endl;
    	//rbs -> position = getPosition();
    	rbs -> orientation = _orientation;
    	//rbs -> velocity = getVelocity();
    	//rbs -> angular_velocity = getAngularVelocity();

    }



   void HalliburtonSASParser::getUtmwgs(  Utmwgs *utmwgs){
		std::cout<< "get hallis utmwgs"<<std::endl;
		utmwgs-> latitudeZone  = _utmwgs.latitudeZone;
		utmwgs-> longitudeZone = _utmwgs.longitudeZone;
		utmwgs-> eastPosition  = _utmwgs.eastPosition;
		utmwgs-> northPosition  = _utmwgs.northPosition;
		utmwgs-> altitude  = _utmwgs.altitude;

   }


   const std::string HalliburtonSASParser::halliburtonStatus[] = {
                       		"FOG or Source error",
                       		"Accelerometer error",
                       		"Serial input or Ethernet port A error",
                       	     "Serial input or Ethernet port B error",
                       		"Serial input or Ethernet port C error",
                       		"Serial input or Ethernet port D error",
                       		"Serial input or Ethernet port E error",
                       		"GPS valid",
                       		"DVL Bottom track valid",
                       		"USBL valid",
                       		"Dead Reckoning",
                       		"GPS1 detected",
                       		"DVL Bottom or Water track detected"
                       		"USBL detected",
                       		"Depth detected",
                       		"Activity on serial input or Ethernet port A",
                       		"Activity on serial input or Ethernet port B",
                       		"Activity on serial input or Ethernet port C",
                       		"Activity on serial input or Ethernet port D",
                       		"Alignment",
                       		"Fine Alignement",
                       		"Navigation"

    };


} /* namespace phins_ixsea */
