/**@file
 * Config.hpp
 * @brief
 *
 *  Created on: 22/08/2012
 *      Author: fahrlich
 */

#ifndef CONFIG_HPP_
#define CONFIG_HPP_

#include "PhinsTypes.hpp"

namespace phins_ixsea
{

/** @brief
* This configuration struct contains
* port and protocol.
* Both defined in PhinsTypes.hpp
*/

struct Config
{

        int port;
        int protocol;

        Config()
            :  port(PORT_PHINS), protocol(PhinsStandard)// init values
        {
        }

};

}


#endif /* CONFIG_HPP_ */
