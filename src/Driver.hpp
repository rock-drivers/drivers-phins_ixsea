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
#include <base/samples/rigid_body_state.h>


namespace phins_ixsea
{
	class Driver : public iodrivers_base::Driver
	{
	    std::vector<uint8_t> mBuffer;
	    Parser* mParser;

        base::samples::RigidBodyState   mUtmPose;
        base::samples::RigidBodyState   mGeoPose;

        uint32_t                        mUpdateFlags;

        PhinsStatus                     mPhinsStatus;
        PhinsExtStatus                  mPhinsExtStatus;

	    int extractPacket (uint8_t const *buffer, size_t buffer_size) const;


	    void updateSamples();


		public: 
	        Driver(Protocol protocol = PhinsStandard);
            virtual ~Driver();

            void setParser(Protocol protocol);

            void read();
            bool hasUpdate(uint32_t flags, bool reset = false);
            const base::samples::RigidBodyState& utmPose() const;
            const base::samples::RigidBodyState& geoPose() const;

            base::samples::RigidBodyState relativePose(const base::Position origin) const;

            PhinsStatus phinsStatus() const;
            PhinsExtStatus phinsExtStatus() const;
            NavigationMode navigationMode() const;
	};

} // end namespace phins_ixsea

#endif // _PHINS_IXSEA_DRIVER_HPP_
