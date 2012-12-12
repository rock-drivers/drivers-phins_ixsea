/*
 * Parser.cpp
 *
 *  Created on: 12.06.2012
 *      Author: jrenken
 */
//

#include <iostream>

#include "Parser.hpp"
#include "phins_ixsea/PhinsStandardParser.hpp"

#include "phins_ixsea/HalliburtonSASParser.hpp"



namespace phins_ixsea
{

Parser::Parser()
{
	//std::cout<< "parser konstruktor"<<std::endl;
}

phins_ixsea::Parser* Parser::createParser(int protocol)
{
    switch (protocol) {
    case PhinsStandard:

        return new PhinsStandardParser();

    case HalliburtonSAS:

    	 return new HalliburtonSASParser();

    default:
        return 0;
    }
    return 0;
}


int Parser::extractPacket (uint8_t const *buffer, size_t buffer_size) const
{
    if (buffer[0] == '$') { // starts with '$'
        for (size_t i = 0; i < buffer_size; i++) {
            if (buffer[i] == '\n') {
                return i + 1;
            }
        }
        return 0; // only '$'
    } else { //
        for (size_t i = 0; i < buffer_size; i++) {
            if (buffer[i] == '$') {
                return -i;
            }
        }
    }
    return -buffer_size;
}

NmeaParser::NmeaParser()
    : Parser()
{
	std::cout<< "nmeaParser Konstruktor"<<std::endl;
}


} /* namespace phins_ixsea */
