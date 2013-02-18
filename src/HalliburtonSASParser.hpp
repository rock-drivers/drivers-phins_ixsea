/*
 * HalliburtonSASParser.hpp
 *
 *  Created on: 12.06.2012
 *      Author: jrenken
 */

#ifndef _PHINS_IXSEA_HALLIBURTONSASPARSER_HPP_
#define _PHINS_IXSEA_HALLIBURTONSASPARSER_HPP_

#include "Parser.hpp"

namespace phins_ixsea
{

    /*
     *
     */
    class HalliburtonSASParser: public phins_ixsea::NmeaParser
    {
    public:
        HalliburtonSASParser();
    };

} /* namespace phins_ixsea */
#endif /* _PHINS_IXSEA_HALLIBURTONSASPARSER_HPP_ */
