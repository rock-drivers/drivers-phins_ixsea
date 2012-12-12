/*
 * NmeaRecord.cpp
 *
 *  Created on: 11/07/2012
 *      Author: fahrlich
 */


#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>


#include "phins_ixsea/NmeaRecord.hpp"
//#include "Error.hpp"


using namespace phins_ixsea;


NmeaRecord::NmeaRecord():
		mFields(0)
{
	// TODO Auto-generated constructor stub

}


NmeaRecord::NmeaRecord(string s) {

	setRecord(s);


}

NmeaRecord::~NmeaRecord() {
	// TODO Auto-generated destructor stub
}

/**@brief splits coma sperated nmea string and puts each word in array of strings
 * @TODO Error
 * @param nmea string
 * @return int with nmea records size
 */
int NmeaRecord::setRecord(string rec_str )
{
	mFields.clear();

	if (rec_str.size() > 0){
		// get rid of whites pace an linefeeds, etc  .. at the start and the end
		boost::trim(rec_str);


		rec_str.erase(rec_str.begin(), rec_str.begin() +1 );
		mValid = true;


		if ((rec_str.size() > 3) && (rec_str.at(rec_str.size() - 3) == '*')) {
			 std::cout<<" *** "<<std::endl;
			if( rec_str.compare(rec_str.size()- 2, 2 , checksum(rec_str))){ // returns 0 if equal
				mValid = false;
				// throw nmea error @TODO
				//  std::cout<<"throw error, aber wohin ???"<<std::endl;
				//catch(phins_error::MarError(MARSTR_CHECKSUM, MARERROR_CHECKSUM)){}
				//  throw phins_error::MarError(MARSTR_CHECKSUM, MARERROR_CHECKSUM);
				//phins_error::Warning;throw
			//	  std::cout<<phins_error::LogMessage( phins_error::Warning, MARSTR_CHECKSUM, MARERROR_CHECKSUM)<<std::endl;
			}
			// removes '*hh' from the end
			rec_str.erase(rec_str.end()-3, rec_str.end());
		}


		//split string
		boost::split( mFields , rec_str,  boost::is_any_of(","));

	}
	else {
		// throw warning
	}
    return mFields.size();
}

int NmeaRecord::clearRecord(){
	if (!NmeaRecord::mFields.empty()){
		NmeaRecord::mFields.clear();
		return 0;
	}
	return 1;

}
//calc checksum of string
string NmeaRecord::checksum(string str){

	uint8_t cs = 0;
	string::iterator it;
	it = str.begin();

	while( *it != '*'){
			cs ^= *it++; // bitwise OR
	}

	return ( boost::lexical_cast<string>(cs));

}

string NmeaRecord::header() const{

	if (mFields.size() >= 1)
	        return mFields.at(0);
	return "";


}

string NmeaRecord::field(uint8_t i){
	if (mFields.size() >= i)
	        return mFields.at(i);
	return "";
}

string NmeaRecord::header2() const{

	if (mFields.size() > 1)
	        return mFields.at(1);
	return "";


}

void NmeaRecord::print(){
	std::cout<< " mField:"  << std::endl;

	for( uint8_t i = 0; i < mFields.size(); i++){
		std::cout<< mFields.at(i) << std::endl;
	}
}


int NmeaRecord::size(){

		return mFields.size();

}

//}
