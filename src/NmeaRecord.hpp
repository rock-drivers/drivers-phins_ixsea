/**
 * @file NmeaRecord.hpp
 * @brief parses and writes nmea 0183 sentences to an array of strings
 */

#ifndef NMEARECORD_H_
#define NMEARECORD_H_

#include <vector>
#include <string>



using namespace std;


namespace phins_ixsea{

	class NmeaRecord {


public:
		static const int MaxFields;

		NmeaRecord();
		NmeaRecord(std::string s);

		virtual ~NmeaRecord();



		bool mValid;
		std::vector<std::string> mFields;
		bool mValidHeader;


	    void print();
		int setRecord(string rec);


		int size();
		string checksum(string str);

		bool isEmpty() const {  return (mFields.size() == 0);  }
		bool isValidData() const {  return mValid ;}
		bool isValidHeader() const ;
		string header() const;
		string header2() const;


//	protected:

		int clearRecord();
		string field(uint8_t i);

		//int setRecord(const char  *rec );


		// void setField(int i, int val);
		// void setField(int i, double val);
		// void setField(int i, const s &val);







	};
} // end namespace phins_ixsea


#endif /* NMEARECORD_H_ */
