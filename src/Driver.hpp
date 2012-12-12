/**
 * @file Driver.hpp
 * @brief Phins ixsea's driver class
 *
 *
 *  Created on: 12.06.2012
 *      Author: jrenken
 */

#ifndef _PHINS_IXSEA_DRIVER_HPP_
#define _PHINS_IXSEA_DRIVER_HPP_



#include <iostream>
#include <iodrivers_base/Driver.hpp>
#include "base/samples/rigid_body_state.h"

#include "Config.hpp"




namespace phins_ixsea
{

	class Parser;


	class Driver: public iodrivers_base::Driver {

	public:

		Driver(Protocol p);
		Driver(const Config& config = Config());



		void read(int timeout);
	    void open(int port);
	    void setConfiguration(std::string msg);
	    void resetPhins();

	    Utmwgs getUtmwgs();
	    base::samples::RigidBodyState getRBS();

	    Parser *mParser;

	private:
	    /** @brief utmwgs */
		Utmwgs *mUtmwgsData;
		  /** @brief Rigid Body State
		   *  filled with data from Phins Standard:
		   *  	time - <tr>
		   *  	sourceFrame <\tr>
		   *  	targetFrame <tr>
		   *  	position <tr>
		   *  	cov_position <tr>
		   *  	orinetation <tr>
		   *  	cov_orientation <tr>
		   *  	velocity <tr>
		   *  	cov_velocity <tr>
		   *  	angular_velocity <tr>
		   *  	cov_angular_velocity <tr>
		   *
		   *
		   *
		   * */
		base::samples::RigidBodyState *mRBS;
		void printMember();
		Config mconfig;

		int extractPacket (uint8_t const *buffer, size_t buffer_size) const;

	};


}

#endif
