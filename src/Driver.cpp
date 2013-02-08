/*
 * Driver.cpp
 *
 *  Created on: 12.06.2012
 *      Author: jrenken
 */

#include "Driver.hpp"

using namespace phins_ixsea;



Driver::Driver(Protocol protocol)
    : iodrivers_base::Driver(10000),
      mParser(0)
{
    mParser = Parser::createParser(protocol);
    mBuffer.resize(10000);
}

Driver::~Driver()
{
    delete mParser;
}

void Driver::setParser(Protocol protocol)
{
    delete mParser;
    mParser = Parser::createParser(protocol);
}

int Driver::extractPacket (uint8_t const *buffer, size_t buffer_size) const
{
    if (mParser)
        return mParser->extractPacket(buffer, buffer_size);
    return -buffer_size;
}


void Driver::read()
{
    int packet_size = readPacket(&mBuffer[0], mBuffer.size());
    if (packet_size)
        mParser->parse(&mBuffer[0], packet_size);
}

bool Driver::hasUpdate(uint32_t flags)
{
    return mParser->hasUpdate(flags);
}

bool Driver::getData(base::samples::RigidBodyState& rbs)
{
    return mParser->getData(rbs);
}
