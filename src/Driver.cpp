/**  @file Driver.cpp
* @mainpage    Dokumentation  Phins
* @version 1.0
 *
 *  Created on: 01/08/2012
 *      Author: fahrlich
 */

#include <boost/lexical_cast.hpp>
#include <string>
#include <iostream>
#include <termios.h>


#include "phins_ixsea/Driver.hpp"
#include "phins_ixsea/Error.hpp"
#include "phins_ixsea/Parser.hpp"
#include "phins_ixsea/PhinsTypes.hpp"



using namespace phins_ixsea;


Driver::Driver( const Config& config):iodrivers_base::Driver(8192), mParser(0), mRBS(0){

	mParser = Parser::createParser(config.protocol);

	mRBS = new  base::samples::RigidBodyState();
	mRBS->invalidate();


	mUtmwgsData = new Utmwgs();

	mUtmwgsData->latitudeZone = 'A';
	mUtmwgsData->longitudeZone = 0;
	mUtmwgsData->eastPosition = 0;
	mUtmwgsData->northPosition = 0;
	mUtmwgsData->altitude = 0;

}



Driver::Driver(Protocol protocol):iodrivers_base::Driver(8192), mParser(0), mRBS(0){

	//std::cout<< "construct Driver.. " <<std::endl;

	mParser = Parser::createParser(protocol);

	mRBS = new  base::samples::RigidBodyState();

	mRBS->invalidate();


	mUtmwgsData = new Utmwgs();
	mUtmwgsData->latitudeZone = 'A';
	mUtmwgsData->longitudeZone = 0;
	mUtmwgsData->eastPosition = 0;
	mUtmwgsData->northPosition = 0;
	mUtmwgsData->altitude = 0;


}


/**
 *
 * @param std::string without leading '$'
 * 	e.g. "PIXSE,CONFIG,RSOUTA,57600,3,1000,0,0*"
 */
void Driver::setConfiguration(std::string msg){

	//std::string msg= "PIXSE,CONFIG,RSOUTA,57600,3,1000,0,0*";
	//std::string msg= "PIXSE,CONFIG,RSOUTA,4,3,500,0,0,1,0*"; // set Halliburton
	//std::string msg= "PIXSE,CONFIG,RSOUTA,4,1,1000,0,0,1,0*"; // phins ok
/*
	// calc checksum
	uint8_t cs = 0;
	string::iterator it;
	it = msg.begin();

	while( *it != '*'){
			cs ^= *it++; // bitwise OR
	}
	//printf("cs is %u", cs);
	char hexSum[8];
	sprintf( hexSum,"%x ", cs);
	//printf("hexString ist [%s]", hexSum);

	open(PORTX);

	clear();
	// concatenate
	std::string  config_msg= "$"+ msg + hexSum + "\r\n";

	clear();
	// WAKE UP !!
    std::string wakeup_msg="$PIXSE,CONFIG,WAKEUP*40\r\n";
	//std::cout<<" Phinsi, wake UP !!!: "<< wakeup_msg<<std::endl;
	writePacket(reinterpret_cast<const uint8_t *>( wakeup_msg.c_str()), wakeup_msg.length());
	clear();
	// write config command
	writePacket(reinterpret_cast<const uint8_t *>( config_msg.c_str()), config_msg.length());

	clear();
	// save
    std::string save_msg="$PIXSE,CONFIG,SAVE__*5C\r\n";
 	//std::cout<<" save config: "<< save_msg<<std::endl;
    writePacket(reinterpret_cast<const uint8_t *>( save_msg.c_str()), save_msg.length());


	// reset das geht irgendwie nicht, config geht verloren
	//clear();
    //std::string reset_msg="$PIXSE,CONFIG,RESET_*57\r\n";
	//std::cout<<" reset: "<< reset_msg<<std::endl;
	//writePacket(reinterpret_cast<const uint8_t *>( reset_msg.c_str()), reset_msg.length());
    close();
    */
}

/**@brief phins system reboot
 * does not work @TODO
 *
 */
void Driver::resetPhins() {
/*
	open(PORTX);
	clear();
	// WAKE UP !!
	std::string msg="$PIXSE,CONFIG,WAKEUP*40\r\n";
	writePacket(reinterpret_cast<const uint8_t *>( msg.c_str()), msg.length());
	clear();
    msg=="$PIXSE,CONFIG,RESET_*57\r\n";
	writePacket(reinterpret_cast<const uint8_t *>( msg.c_str()), msg.length());
	close();
*/
}

/**
 * opens connection to phins
 * 	tcp for PORTX (configure port)
 * 	udp else
 */
void  Driver::open(int port)
{
	char uri[32];
	switch(port){
		case PORTX:
			 sprintf(uri, "tcp://10.112.102.50:%u", port);
			 openURI(uri);
			 break;
		default:
			 sprintf(uri, "udpserver://%u", port);
			 openURI(uri);
			break;
	}
}

Utmwgs Driver::getUtmwgs(){
		return *mUtmwgsData;
}

base::samples::RigidBodyState Driver::getRBS(){

	std::cout<<"get rbs "<< std::endl;
	mRBS->time = base::Time::now();

	return *mRBS;
}

/**@brief reading and parsing a packet from filedescriptor
 *
 */
void  Driver::read(int timeout)
{

	//
	// if( task._in_port.read() != RTT:: New Data

		char buffer[MAX_PACKET_SIZE];
	 	size_t packet_size =  0;
	try {
		//char buffer[] = "$PIXSE,ALGSTS,00000045,00004000*60" ;
		packet_size =   readPacket(reinterpret_cast<uint8_t *>( buffer), 8192 , 5000, timeout);
		std::cout<<"packet size "<<  packet_size  <<std::endl;
	}
	//catch (std::runtime_error &e ) {
	catch (oro_marum::MarError &me ) {
        std::cout << "read error: " << me.what()<<std::endl;
        throw; // weiterwerfen, damit es im task ankommt
     }

	if (packet_size){
		buffer[packet_size] = 0;
		packet_size = 0;

		mParser->parseEnsemble(buffer, packet_size);
    	//std::cout<< " call get rbs "<< std::endl;

    	mParser->getRBS( mRBS );
    	mParser->getUtmwgs( mUtmwgsData );

    	printMember();



		}

}


void Driver::printMember(){



	   	std::cout<< "**** drivers member *** "<<std::endl;
	   // std::cout<<"time"<<ctime(&mTime)<<std::endl;
	 //   std::cout<<"baseTime"<<baseTime.toString() <<std::endl;

	    std::cout<<"pos x "<< mRBS->position.x() << std::endl;
	    std::cout<<"pos y "<< mRBS->position.y() << std::endl;
	    std::cout<<"pos z "<< mRBS-> position.z() << std::endl;

	    std::cout<<"angular verlocity x "<<  mRBS->angular_velocity.x() << std::endl;
	    std::cout<<"angular verlocity y "<<  mRBS->angular_velocity.y() << std::endl;
	    std::cout<<"angular verlocity z "<<  mRBS->angular_velocity.z() << std::endl;

	    std::cout<<"verlocity x "<<  mRBS->velocity.x() << std::endl;
	    std::cout<<"verlocity y "<<  mRBS->velocity.y() << std::endl;
	    std::cout<<"verlocity z "<<  mRBS->velocity.z() << std::endl;


	    std::cout<<"rbs: ori x"<< mRBS->orientation.x() << std::endl;
	    std::cout<<"rbs: ori y"<< mRBS->orientation.y() << std::endl;
	    std::cout<<"rbs: ori z"<< mRBS->orientation.z() << std::endl;

		std::cout<<"UTMWGS" <<std::endl;
		std::cout<<"latitude: "<< mUtmwgsData->latitudeZone <<std::endl;
		std::cout<<"longitude: "<< mUtmwgsData->longitudeZone <<std::endl;

		std::cout<<"eastPosition: "<< mUtmwgsData->eastPosition<<std::endl;
		std::cout<<"northPosition: "<< mUtmwgsData->northPosition <<std::endl;
		std::cout<<"altitude: "<< mUtmwgsData->altitude <<std::endl;



 }



int Driver::extractPacket (uint8_t const *buffer, size_t buffer_size) const
{
    if (mParser)
        return mParser->extractPacket(buffer, buffer_size);
    return -buffer_size;
}

