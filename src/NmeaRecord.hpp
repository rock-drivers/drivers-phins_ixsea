/**
 * @file NmeaRecord.hpp
 * @brief parses and writes nmea 0183 sentences to an array of strings
 */

#ifndef _PHINS_IXSEA_NMEARECORD_HPP_
#define _PHINS_IXSEA_NMEARECORD_HPP_

#include <vector>
#include <string>



namespace phins_ixsea{

    class NmeaRecord {


    public:
        enum {MaxFields = 64};

        NmeaRecord();
        NmeaRecord(std::string s);
        NmeaRecord(const char *buffer, size_t size);

        int setRecord(std::string rec);

        int size();
        std::string checksum(std::string str) const;

        std::string field(int i) const;
        std::string operator[](int i) const;
        void setField(int i, const std::string& text);

        bool isEmpty() const {  return (mFields.size() == 0);  }
        bool isValid() const { return mValid ; }
        bool isValidData() const {  return mValid ;}

        std::string header() const;

        std::string sentence(bool cs = true) const;

	private:
        bool mValid;
        std::vector<std::string> mFields;

        int clearRecord();
        std::string toHex(uint64_t num, int len) const;

        // void setField(int i, int val);
        // void setField(int i, double val);
        // void setField(int i, const s &val);

    };

} // end namespace phins_ixsea


#endif /* _PHINS_IXSEA_NMEARECORD_HPP_ */
