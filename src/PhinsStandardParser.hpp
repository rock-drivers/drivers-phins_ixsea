/*
 * PhinsStandardParser.hpp
 *
 *  Created on: 12.06.2012
 *      Author: jrenken
 */

#ifndef _PHINS_IXSEA_PHINSSTANDARDPARSER_HPP_
#define _PHINS_IXSEA_PHINSSTANDARDPARSER_HPP_

#include "Parser.hpp"

namespace phins_ixsea
{

    /*
     *
     */
    class PhinsStandardParser: public phins_ixsea::NmeaParser
    {
    public:
        PhinsStandardParser();

        virtual void parse(uint8_t const *buffer, size_t size);
    };

} /* namespace phins_ixsea */
#endif /* _PHINS_IXSEA_PHINSSTANDARDPARSER_HPP_ */
