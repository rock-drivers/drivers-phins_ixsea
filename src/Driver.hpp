/*
 * Driver.hpp
 *
 *  Created on: 12.06.2012
 *      Author: jrenken
 */

#ifndef _PHINS_IXSEA_DRIVER_HPP_
#define _PHINS_IXSEA_DRIVER_HPP_

#include <iodrivers_base/Driver.hpp>
#include <phins_ixsea/Parser.hpp>
#include <phins_ixsea/PhinsTypes.hpp>
#include <phins_ixsea/PhinsRaw.hpp>

namespace phins_ixsea
{
	class Driver : public iodrivers_base::Driver
	{
	    std::vector<uint8_t> mBuffer;
	    Parser* mParser;

	    int extractPacket (uint8_t const *buffer, size_t buffer_size) const;


		public: 
            Driver(Protocol protocol = PhinsStandard);
            virtual ~Driver();

            void setParser(Protocol protocol);

            void read();
            bool hasUpdate(uint32_t flags);
            bool getData(base::samples::RigidBodyState& rbs);

	};

} // end namespace phins_ixsea

#endif // _PHINS_IXSEA_DRIVER_HPP_
