/*
 * PhinsStandardParser.cpp
 *
 *  Created on: 12.06.2012
 *      Author: jrenken
 *
 *
 *   RigidBodyState contains
 *   	- pose : Position , Orientation
 */


//#include <stdint.h>
//#include <stdlib.h>
//#include <string>
//#include <base/time.h>
#include <iostream>
//#include <base/eigen.h>
#include <base/angle.h>

#include "PhinsStandardParser.hpp"





using namespace phins_ixsea;


PhinsStandardParser::PhinsStandardParser()

    {

		std::cout<< "phins konstruktor"<<std::endl;

    	//PhinsStandardParser::mRigidBodyState.position = Eigen::Vector3d(0, 0, 0);
    	//mRigidBodyState.invalidate(); // init  with NaN
/*
    	_utmwgs.latitudeZone = 'A';
    	_utmwgs.longitudeZone = 0;
    	_utmwgs.eastPosition = 0;
    	_utmwgs.northPosition = 0;
    	_utmwgs.altitude = 0;
*/
    	_position.x() = -1;
    	_position.y() = -1;
    	_position.z() = -1;

    	_heading = -1;



        initPhinsHeaderMap();

        //mTime = time(NULL);
        baseTime = base::Time::now();

		std::cout<< ".. finished "<<std::endl;


    }


int PhinsStandardParser::extractPacket (uint8_t const *buffer, size_t buffer_size) const {

	return Parser::extractPacket(buffer,  buffer_size);

}

void PhinsStandardParser::parseEnsemble(std::string buffer, size_t size){


	 std::cout<< " ...phins standard is parsing .. "<<std::endl;

		   mNmeaRecord.setRecord(buffer);

	    	switch(phinsHeaderMap[mNmeaRecord.header()])
	    	{

	    	case sHehdt:
	    		parseHeading();
	    	 	setOrientation();
	    		break;
	    	case sPixse:

	    		parsePixse();
	    		break;
	    	case sTime:
	    		//PhinsStandardParser::mRigidBodyState.time = base::Time::now();
	    		//std::cout<< "time"<<std::endl;
	    		parseTime();
	    		break;
	    	default:
	    		std::cout<< " default"<<std::endl;
	    		break;
	    	}
	}



void PhinsStandardParser::getRBS( base::samples::RigidBodyState *rbs){

	std::cout<< "get phins rbs"<<std::endl;

	rbs -> position = getPosition();
	rbs -> orientation = getOrientation();
	rbs -> velocity = getVelocity();
	rbs -> angular_velocity = getAngularVelocity();


	//std::cout<< rbs->position.x()<< std::endl;
	//std::cout<< rbs->position.y()<< std::endl;
	//std::cout<< rbs->position.z()<< std::endl;


}

void PhinsStandardParser::getUtmwgs(  Utmwgs *utmwgs){

	std::cout<< "get phins utmwgs"<<std::endl;

	*utmwgs = getUtmwgsData();
}


/*
* "HEHDT, x.xxxx. T*hh"
*/
int PhinsStandardParser::parseHeading()
   {
	   const char* p;
	   if (!mNmeaRecord.field(2).compare("T")){
		   p = mNmeaRecord.field(1).c_str();
		   _heading = atof(p);
	   }
	   else {
		   throw std::runtime_error("no valid packet from Phins: Heading.");
	   }
	   setOrientation();
	   return 0;
   }

int PhinsStandardParser::parsePixse(){

	   const char* p;

	switch(phinsHeaderMap[mNmeaRecord.header2()]){
		case sAtitude : // roll , pitch in degrees
			p = mNmeaRecord.field(2).c_str();
			_roll = atof(p);
			p = mNmeaRecord.field(3).c_str();
			_pitch = atof(p);

			setOrientation();

				break;
		case sPosition : // latitude, longitude, altitude
			p = mNmeaRecord.field(2).c_str();
			_position.x() = atof(p);
			p = mNmeaRecord.field(3).c_str();
			_position.y() = atof(p);
			p = mNmeaRecord.field(4).c_str();
			_position.z() = atof(p);



			break;

		case sSpeed : //
			p = mNmeaRecord.field(2).c_str();
			_velocity.x() = atof(p);
			p = mNmeaRecord.field(3).c_str();
			_velocity.y() = atof(p);
			p = mNmeaRecord.field(4).c_str();
			_velocity.z() = atof(p);

			break;

		case sUtmwgs :

			_utmwgs.latitudeZone  = mNmeaRecord.field(2)[0];

			p = mNmeaRecord.field(3).c_str();
			_utmwgs.longitudeZone = atoi(p);

			p = mNmeaRecord.field(4).c_str();
			_utmwgs.eastPosition = atof(p);

			p = mNmeaRecord.field(5).c_str();
			_utmwgs.northPosition = atof(p);

			p = mNmeaRecord.field(6).c_str();
			_utmwgs.altitude = atof(p);

				break;
		case sHeave :
				break;
		case sStdhrp :
				break;
		case sStdpos :
				break;
		case sStdspd :
				break;
		case sLogin :
				break;
		case sLogdvl :
				break;
		case sLogwat :
				break;
		case sGps1 :
				break;
		case sGps2 :
				break;
		case sGpsmin :
				break;
		case sDepth :
				break;
		case sUsbl :
				break;
		case sLbl :
				break;
		case sUtc :
				break;
		case sEm :
				break;
		case sDdreck :
				break;
		case sAlgstatus :
				parseAlgStatus();
				break;
		case sSensor_hex :
				break;
		case sStatus : // Status
				parseSystemStatus();
				break;
		case sInstatus:
				break;
		default:
				break;
		}






	   return 0;}

int PhinsStandardParser::parseTime()

   {
	  baseTime = base::Time::now();
      return 0;
   }

/* calcs Orientation Matrix from  (yaw)Heading , Pitch and Roll  an
 * writes result to mRigidBodyState.Pose.orientation
 */
int PhinsStandardParser::setOrientation(){
	   //std::cout<<"********************"<<std::endl;
	   //std::cout<<"roll in degrees: "<< _roll <<std::endl; // degrees [-180; 180]
	   //std::cout<<"roll in rad: "<< _roll * M_PI /180 <<std::endl; // rad

	   //std::cout<<"pitch in degrees:: "<< _pitch <<std::endl; //degrees [-90; 90]
	   //std::cout<<"pitch in rad: "<< _pitch * M_PI /180 <<std::endl; // rad

	   //std::cout<<"heading in degrees:: "<< _heading <<std::endl; // [ 0; 360]
	  // std::cout<<"heading in rad: "<< _heading  * M_PI /180 <<std::endl; // rad


	   //std::cout<<"set Orientation"<<std::endl;
	   //std::cout<<"pitch roll heading"<<std::endl;
	   //base::Quaterniond
	   _orientation =
			   Eigen::AngleAxisd(M_PI / 180 * _roll,    Eigen::Vector3d::UnitX()) *
		       Eigen::AngleAxisd(M_PI / 180 * _pitch,   Eigen::Vector3d::UnitY()) *
		       Eigen::AngleAxisd(M_PI / 180 * _heading, Eigen::Vector3d::UnitZ());

	  // mRigidBodyState.orientation = _orientation;



	   //std::cout<<"roll div: "<< base::Angle::rad2Deg(mRigidBodyState.getRoll()) <<std::endl;
	   //std::cout<<"pitch div : "<< base::Angle::rad2Deg(mRigidBodyState.getPitch()) <<std::endl;
	   //std::cout<<"heading div: "<<base::Angle::rad2Deg( mRigidBodyState.getYaw()) <<std::endl;

/*

	   std::cout<<"********************roll pitch heading"<<std::endl;
	    _orientation =
			   Eigen::AngleAxisd(M_PI / 180 * _pitch,    Eigen::Vector3d::UnitX()) *
		       Eigen::AngleAxisd(M_PI / 180 * _roll,   Eigen::Vector3d::UnitY()) *
		       Eigen::AngleAxisd(M_PI / 180 * _heading, Eigen::Vector3d::UnitZ());

	   mRigidBodyState.orientation = _orientation;

	   std::cout<<"roll div: "<< base::Angle::rad2Deg(mRigidBodyState.getRoll()) <<std::endl;
	   std::cout<<"pitch div : "<< base::Angle::rad2Deg(mRigidBodyState.getPitch()) <<std::endl;
	   std::cout<<"heading div: "<<base::Angle::rad2Deg( mRigidBodyState.getYaw()) <<std::endl;


	   std::cout<<"********************heading roll pitch "<<std::endl;
	    _orientation =
			   Eigen::AngleAxisd(M_PI / 180 * _heading,    Eigen::Vector3d::UnitX()) *
		       Eigen::AngleAxisd(M_PI / 180 * _roll,   Eigen::Vector3d::UnitY()) *
		       Eigen::AngleAxisd(M_PI / 180 * _pitch, Eigen::Vector3d::UnitZ());

	   mRigidBodyState.orientation = _orientation;

	   std::cout<<"roll div: "<< base::Angle::rad2Deg(mRigidBodyState.getRoll()) <<std::endl;
	   std::cout<<"pitch div : "<< base::Angle::rad2Deg(mRigidBodyState.getPitch()) <<std::endl;
	   std::cout<<"heading div: "<<base::Angle::rad2Deg( mRigidBodyState.getYaw()) <<std::endl;


	   std::cout<<"********************heading  pitch  roll"<<std::endl;
	    _orientation =
			   Eigen::AngleAxisd(M_PI / 180 * _heading,    Eigen::Vector3d::UnitX()) *
		       Eigen::AngleAxisd(M_PI / 180 * _pitch,   Eigen::Vector3d::UnitY()) *
		       Eigen::AngleAxisd(M_PI / 180 * _roll, Eigen::Vector3d::UnitZ());

	   mRigidBodyState.orientation = _orientation;

	   std::cout<<"roll div: "<< base::Angle::rad2Deg(mRigidBodyState.getRoll()) <<std::endl;
	   std::cout<<"pitch div : "<< base::Angle::rad2Deg(mRigidBodyState.getPitch()) <<std::endl;
	   std::cout<<"heading div: "<<base::Angle::rad2Deg( mRigidBodyState.getYaw()) <<std::endl;


	   std::cout<<"********************pitch heading  roll"<<std::endl;
	    _orientation =
			   Eigen::AngleAxisd(M_PI / 180 * _pitch,    Eigen::Vector3d::UnitX()) *
		       Eigen::AngleAxisd(M_PI / 180 * _heading,   Eigen::Vector3d::UnitY()) *
		       Eigen::AngleAxisd(M_PI / 180 * _roll, Eigen::Vector3d::UnitZ());

	   mRigidBodyState.orientation = _orientation;

	   std::cout<<"roll div: "<< base::Angle::rad2Deg(mRigidBodyState.getRoll()) <<std::endl;
	   std::cout<<"pitch div : "<< base::Angle::rad2Deg(mRigidBodyState.getPitch()) <<std::endl;
	   std::cout<<"heading div: "<<base::Angle::rad2Deg( mRigidBodyState.getYaw()) <<std::endl;


	   std::cout<<"********************roll heading  pitch"<<std::endl;
	    _orientation =
			   Eigen::AngleAxisd(M_PI / 180 * _roll,    Eigen::Vector3d::UnitX()) *
		       Eigen::AngleAxisd(M_PI / 180 * _heading,   Eigen::Vector3d::UnitY()) *
		       Eigen::AngleAxisd(M_PI / 180 * _pitch, Eigen::Vector3d::UnitZ());

	   mRigidBodyState.orientation = _orientation;

	   std::cout<<"roll div: "<< base::Angle::rad2Deg(mRigidBodyState.getRoll()) <<std::endl;
	   std::cout<<"pitch div : "<< base::Angle::rad2Deg(mRigidBodyState.getPitch()) <<std::endl;
	   std::cout<<"heading div: "<<base::Angle::rad2Deg( mRigidBodyState.getYaw()) <<std::endl;

*/
	   return 0;
/*
 * 	 //  std::cout<< " matrix " << m<<std::endl; //  << _orientation <<std::endl;

	   Eigen::Matrix3d m;
	   m =  Eigen::AngleAxisd(M_PI / 180 * _roll,  Eigen::Vector3d::UnitX())
	     *  Eigen::AngleAxisd(M_PI / 180 * _pitch,   Eigen::Vector3d::UnitY())
	     *  Eigen::AngleAxisd(M_PI / 180 * _heading,  Eigen::Vector3d::UnitZ());
	   cout << m << endl << "is unitary: " << m.isUnitary() << endl;

	   mRigidBodyState.orientation = m;
	   std::cout<< " matrix " << m<<std::endl;


	 //  mRigidBodyState.orientation = _orientation;
	    status.orientation =
	        Eigen::AngleAxisd(M_PI / 180 * 0.01 * le16toh(msg.roll),    Eigen::Vector3d::UnitX()) *
	        Eigen::AngleAxisd(M_PI / 180 * 0.01 * le16toh(msg.pitch),   Eigen::Vector3d::UnitY()) *
	        Eigen::AngleAxisd(M_PI / 180 * 0.01 * le16toh(msg.yaw), Eigen::Vector3d::UnitZ());
*/

   }

void PhinsStandardParser::initPhinsHeaderMap()
    {
    	 phinsHeaderMap["PIXSE"] = sPixse;
    	 phinsHeaderMap["HEHDT"] = sHehdt;
    	 phinsHeaderMap["TIME_"] = sTime;
    	 phinsHeaderMap["ATITUD"] = sAtitude;
    	 phinsHeaderMap["POSITI"] = sPosition;
    	 phinsHeaderMap["SPEED_"] = sSpeed;
    	 phinsHeaderMap["UTMWGS"] = sUtmwgs;
    	 phinsHeaderMap["HEAVE_"] = sHeave;
    	 phinsHeaderMap["STDHRP"] = sStdhrp;
    	 phinsHeaderMap["STDPOS"] = sStdpos;
    	 phinsHeaderMap["STDSPD"] = sStdspd;

    	 phinsHeaderMap["LOGIN_"] = sLogin;
    	 phinsHeaderMap["LOGDVL"] = sLogdvl;
    	 phinsHeaderMap["LOGWAT"] = sLogwat;
    	 phinsHeaderMap["GPSIN"] = sGps1;
    	 phinsHeaderMap["GP2IN"] = sGps2;
    	 phinsHeaderMap["GPMIN_"] = sGpsmin;
    	 phinsHeaderMap["DEPIN_"] = sDepth;
    	 phinsHeaderMap["USBIN_"] = sUsbl;
    	 phinsHeaderMap["LBLIN_"] = sLbl;
    	 phinsHeaderMap["UTCIN_"] = sUtc;
    	 phinsHeaderMap["LMNIN_"] = sEm;
    	 phinsHeaderMap["DDRECK"] = sDdreck;
    	 phinsHeaderMap["ALGSTS"] = sAlgstatus;
    	 phinsHeaderMap["SORST"] = sSensor_hex;
    	 phinsHeaderMap["STATUS"] = sStatus;
    	 phinsHeaderMap["HT_STS"] = sInstatus;

   // cout << "s_mapStringValues contains "
   // << s_mapStringValues.size()
   // << " entries." << endl;
    }

void PhinsStandardParser::printParserMember(){

	   	std::cout<< "**** phins member *** "<<std::endl;
	   // std::cout<<"time"<<ctime(&mTime)<<std::endl;
	    std::cout<<"baseTime"<<baseTime.toString() <<std::endl;

	//	std::cout<<"mPosition\n "<< mPosition <<std::endl;

	    std::cout<<"pos x"<< _position.x() << std::endl;
	    std::cout<<"pos y"<< _position.y() << std::endl;
	    std::cout<<"pos z"<< _position.z() << std::endl;

	    std::cout<<"angular verlocity x"<< _angularVelocity.x() << std::endl;
	    std::cout<<"angular verlocity y"<< _angularVelocity.y() << std::endl;
	    std::cout<<"angular verlocity z"<< _angularVelocity.z() << std::endl;


	    std::cout<<"rbs: ori x"<< _orientation.x() << std::endl;
	    std::cout<<"rbs: ori y"<< _orientation.y() << std::endl;
	    std::cout<<"rbs: ori z"<< _orientation.z() << std::endl;



		std::cout<<"UTMWGS" <<std::endl;
		std::cout<<"latitude: "<< _utmwgs.latitudeZone <<std::endl;
		std::cout<<"longitude: "<< _utmwgs.longitudeZone <<std::endl;

		std::cout<<"eastPosition: "<< _utmwgs.eastPosition<<std::endl;
		std::cout<<"northPosition: "<< _utmwgs.northPosition <<std::endl;
		std::cout<<"altitude: "<< _utmwgs.altitude <<std::endl;


		//std::cout<<"heading: "<< mHeading <<std::endl;


   }

Eigen::Vector3d PhinsStandardParser::getPosition(){

	   return _position;
   }

Eigen::Vector3d PhinsStandardParser::getAngularVelocity(){
	   return _angularVelocity;
   }

base::Quaterniond PhinsStandardParser::getOrientation(){
	   return _orientation;
   }


Eigen::Vector3d PhinsStandardParser::getVelocity(){

	 return _velocity;

}


Utmwgs PhinsStandardParser::getUtmwgsData(){
	   return _utmwgs;
   }

/**
 * parst "PIXSE.STATUS" packet.
 * @TODO wohin soll die Message
 */
std::string  PhinsStandardParser::parseSystemStatus(){
	  std::cout<<"parse status "<<mNmeaRecord.field(1)<<std::endl;
	  const std::string& lsbStr = mNmeaRecord.field(1);
	  const std::string& msbStr = mNmeaRecord.field(2);
	  std::stringstream lsbStrs(lsbStr);
	  std::stringstream msbStrs(msbStr);

	  int nLsb,nMsb;
	  lsbStrs >> std::hex >> nLsb;
	  msbStrs >> std::hex >> nMsb;

	  std::string msg;
	  for (int i = 31; i >= 0 ; i-- ){
		  if(nLsb &  (1 << i)) { // lsb bit gesetzt
			  msg += phinsSystemStatus[i] + "\n";
		  }
		  if(nMsb &  (1 << i)) { // msbbit gesetzt
			//  phinsSystemStatus.second [i+ 32] = 1;
			  msg += phinsSystemStatus[i+32] + "\n";
		  }
	  }

	  if(msg.size()== 0){
		  msg += "nothing to report \n";
	  }

	  std::cout<<"****** system status*************\n"<<msg<<
			  "*****************************************"<<std::endl;

	 return msg;
}

/**
 * parst "PIXSE.ALG" packet.
 * @TODO wohin soll die Message
 */
std::string  PhinsStandardParser::parseAlgStatus(){
	 	 std::cout<<"parse alg status "<<mNmeaRecord.field(1)<<std::endl;
		  const std::string& lsbStr = mNmeaRecord.field(1);
		  const std::string& msbStr = mNmeaRecord.field(2);
		  std::stringstream lsbStrs(lsbStr);
		  std::stringstream msbStrs(msbStr);

		  int nLsb,nMsb;
		  lsbStrs >> std::hex >> nLsb;
		  msbStrs >> std::hex >> nMsb;

		  std::string msg;
		  for (int i = 31; i >= 0 ; i-- ){
			  if(nLsb &  (1 << i)) { // lsb bit gesetzt
				  msg += phinsAlgStatus[i] + "\n";
			  }
			  if(nMsb &  (1 << i)) { // msbbit gesetzt
				//  phinsSystemStatus.second [i+ 32] = 1;
				  msg += phinsAlgStatus[i+32] + "\n";
			  }
		  }

		  if(msg.size()== 0){
			  msg += "Phins Alg Status: nothing to report \n";
		  }

		  std::cout<<"****** system status*************\n"<<msg<<
				  "*****************************************"<<std::endl;

		 return msg;
}


