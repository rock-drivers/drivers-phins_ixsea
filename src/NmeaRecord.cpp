/*
 * NmeaRecord.cpp
 *
 *  Created on: 11/07/2012
 *      Author: fahrlich
 */


#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>
#include <stdint.h>
#include <iostream>


#include "phins_ixsea/NmeaRecord.hpp"


using namespace phins_ixsea;


NmeaRecord::NmeaRecord()
    : mValid(false)
{
}


NmeaRecord::NmeaRecord(std::string s)
{
	setRecord(s);
}


/**@brief splits coma sperated nmea string and puts each word in array of strings
 * @TODO Error
 * @param nmea string
 * @return int with nmea records size
 */
int NmeaRecord::setRecord(std::string rec )
{
	mFields.clear();

	try {
        boost::trim(rec);
        if (rec.at(0) == '$') {
            mValid = true;
            int idx = rec.find('*');
            if (idx >= 0) {
                if (idx == (rec.size() - 3)) {
                    std::cout << idx << std::endl;
                    if( rec.compare(idx + 1, 2, checksum(rec))) { // returns 0 if equal
                        mValid = false;
                    }
                }
                rec.resize(idx);
            }
            boost::split( mFields , rec,  boost::is_any_of(","));
        } else
            mValid = false;
    } catch (std::exception& e) {
        mValid = false;
    }
    return mFields.size();
}


std::string NmeaRecord::checksum(std::string str)
{
	int cs = 0;
	std::string::iterator it = str.begin() + 1;

	while( (*it != '*') && (it != str.end()) ) {
 		cs ^= *it++; // bitwise OR
	}
	return ( toHex(cs, 2));
}

std::string NmeaRecord::header() const
{
	if (mFields.size() > 0)
	    return mFields.at(0);
	return "";
}

std::string NmeaRecord::field(int i) const
{
	if (mFields.size() > size_t(i))
	    return mFields.at(i);
	return "";
}

std::string NmeaRecord::operator[](int i) const
{
    return field(i);
}

void NmeaRecord::setField(int i, const std::string& text)
{
    i = std::min(i, int(MaxFields));
    if (mFields.size() <= size_t(i)) {
        mFields.resize(i + 1);
    }
    mFields[i] = text;

}

int NmeaRecord::size()
{
	return mFields.size();
}

std::string NmeaRecord::toHex(uint64_t num, int len)
{
    static const char* hex = "01234567890ABCDEF";

    len = std::min(size_t(len), sizeof(uint64_t));

    std::string s(len, '0');
    std::string::reverse_iterator it=s.rbegin();

    while (it != s.rend()) {
        *it++ = hex[num & 0x0F];
        num >>= 4;
    }
    return s;
}

std::string NmeaRecord::sentence(bool cs)
{
    if (!mFields.size())
        return std::string();

    std::string s = boost::algorithm::join(mFields, ",");
    if (cs) {
        s = s + "*" + checksum(s);
    }
    s += "\r\n";
    return s;
}
