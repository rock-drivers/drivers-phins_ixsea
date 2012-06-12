/*
 * Driver.hpp
 *
 *  Created on: 12.06.2012
 *      Author: jrenken
 */

#ifndef _PHINS_IXSEA_DRIVER_HPP_
#define _PHINS_IXSEA_DRIVER_HPP_

#include <iodrivers_base/Driver.hpp>
#include "Parser.hpp"

namespace phins_ixsea
{
	class Driver : public iodrivers_base::Driver
	{
	    Parser* mParser;

	    int extractPacket (uint8_t const *buffer, size_t buffer_size) const;

		public: 
            Driver();


	};

} // end namespace phins_ixsea

#endif // _PHINS_IXSEA_DRIVER_HPP_
