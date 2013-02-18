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
    };

} /* namespace phins_ixsea */
#endif /* _PHINS_IXSEA_PHINSSTANDARDPARSER_HPP_ */
